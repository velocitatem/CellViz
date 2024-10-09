#include <iostream>
#include <string>
#include <curl/curl.h>
#include <thread>
#include <nlohmann/json.hpp>
#include <fstream>
#include <functional>  



size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s)
{
    size_t totalSize = size * nmemb;
    s->append(reinterpret_cast<const char*>(contents), totalSize);  
    return totalSize;
}

void fetchDataWithRetry(std::reference_wrapper<std::string> symbol, std::reference_wrapper<std::string> interval, std::reference_wrapper<std::string> apikey, int maxRetries = 3) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=" + symbol.get() + "&interval=" + interval.get() + "&apikey=" + apikey.get();

    int retries = 0;
    bool success = false;

    curl = curl_easy_init();
    if (curl) {
        do {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);

            if (res == CURLE_OK) {
                success = true;
                break;
            } else {
                std::cerr << "Attempt " << retries + 1 << " failed: " << curl_easy_strerror(res) << std::endl;
                retries++;
            }
        } while (retries < maxRetries);

        if (!success) {
            std::cerr << "All retry attempts failed." << std::endl;
        } else {
            // Parse and save the JSON data
            try {
                auto jsonData = nlohmann::json::parse(readBuffer);
                std::cout << "Metadata: " << jsonData["Meta Data"].dump(4) << std::endl;

                // Save JSON data to a file
                std::ofstream outFile("output.json");
                if (outFile.is_open()) {
                    outFile << jsonData.dump(4);  // Pretty print JSON
                    outFile.close();
                    std::cout << "JSON data saved to output.json" << std::endl;
                } else {
                    std::cerr << "Unable to open file to save JSON data" << std::endl;
                }
            } catch (nlohmann::json::exception& e) {
                std::cerr << "JSON error: " << e.what() << std::endl;
            }
        }

        curl_easy_cleanup(curl);
    }
}

// Function to read the API key from the secrets file
std::string readApiKey(const std::string& filePath)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open secrets file");
    }

    nlohmann::json secretsJson;
    try {
        inFile >> secretsJson;
    } catch (nlohmann::json::parse_error& e) {
        throw std::runtime_error("Error parsing JSON: " + std::string(e.what()));
    }
    inFile.close();

    // Check if the "apikey" field exists and is a valid string
    if (secretsJson.contains("apikey") && secretsJson["apikey"].is_string()) {
        std::string apiKey = secretsJson["apikey"].get<std::string>();

        // Optional: Validate API key (length check, pattern, etc.)
        if (apiKey.empty()) {
            throw std::runtime_error("API key is empty");
        }

        return apiKey;
    } else {
        throw std::runtime_error("API key not found or is invalid in secrets file");
    }
}

int main()
{
    // Initialize CURL globally
    curl_global_init(CURL_GLOBAL_DEFAULT);
    try {
        std::string symbol = "IBM";
        std::string interval = "5min";
        std::string apikey = readApiKey("secrets.json");  // Read API key from secrets file
        
        std::thread apiThread([&symbol, &interval, &apikey]() {
            fetchDataWithRetry(std::ref(symbol), std::ref(interval), std::ref(apikey));
        });
        
        apiThread.join();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    // Clean up CURL globally
    curl_global_cleanup();
    
    return 0;
}