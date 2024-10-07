#include <iostream>
#include <string>
#include <curl/curl.h>
#include <thread>
#include <nlohmann/json.hpp>  // Include nlohmann/json library
#include <fstream>  // Include fstream for file handling

// Function to handle incoming data from libcurl
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s)
{
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

// Function to fetch data from API and save it as JSON
void fetchData(const std::string& symbol, const std::string& interval, const std::string& apikey)
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=" + symbol + "&interval=" + interval + "&apikey=" + apikey;
    
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Parse and save the JSON data
            try {
                auto jsonData = nlohmann::json::parse(readBuffer);
                
                // Save JSON data to a file
                std::ofstream outFile("output.json");
                if (outFile.is_open()) {
                    outFile << jsonData.dump(4);
                    outFile.close();
                    std::cout << "JSON data saved to output.json" << std::endl;
                } else {
                    std::cerr << "Unable to open file to save JSON data" << std::endl;
                }
            } catch (nlohmann::json::parse_error& e) {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
            }
        }
        
        curl_easy_cleanup(curl);
    }
}

// Main function that uses threading to dynamically load data
int main()
{
    std::string symbol = "IBM";
    std::string interval = "5min";
    
    // Load API key from secrets.json
    std::ifstream secretsFile("secrets.json");
    nlohmann::json secretsJson;
    if (secretsFile.is_open()) {
        secretsFile >> secretsJson;
        secretsFile.close();
    } else {
        std::cerr << "Unable to open secrets.json" << std::endl;
        return 1;
    }
    std::string apikey = secretsJson["apikey"].get<std::string>();
    
    // Launch thread for fetching data
    std::thread apiThread(fetchData, symbol, interval, apikey);
    
    // Join the thread to make sure main waits for it to complete
    apiThread.join();
    
    return 0;
}