#include <iostream>
#include <string>
#include <curl/curl.h>
#include <thread>
#include <nlohmann/json.hpp> 
#include <fstream>  

// Function which handles incoming data from libcurl
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
                std::cout << jsonData.dump(4) << std::endl;
                
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

// Function to read the API key from secrets file
std::string readApiKey(const std::string& filePath)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open secrets file");
    }
    
    nlohmann::json secretsJson;
    inFile >> secretsJson;
    inFile.close();
    
    return secretsJson["apikey"].get<std::string>();
}

int main()
{
    try {
        std::string symbol = "IBM";
        std::string interval = "5min";
        std::string apikey = readApiKey("secrets.json");  // Read API key from secrets file
        
        // Create a thread for fetching data
        std::thread apiThread(fetchData, symbol, interval, apikey);
        
        // Wait for the thread to complete
        apiThread.join();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}