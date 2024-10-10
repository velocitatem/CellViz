//
// Created by velocitatem on 10/9/24.
//
#include "data.h"
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s)
{
    size_t totalSize = size * nmemb;
    s->append(reinterpret_cast<const char*>(contents), totalSize);
    return totalSize;
}
void fetchDataWithRetry(const std::string& apikey, bool adjusted, bool extended_hours, const std::string& month, const std::string& outputsize, const std::string& datatype, int maxRetries) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=IBM&interval=5min&apikey=" + apikey;
    url += "&adjusted=" + std::string(adjusted ? "true" : "false");
    url += "&extended_hours=" + std::string(extended_hours ? "true" : "false");
    if (!month.empty()) {
        url += "&month=" + month;
    }
    url += "&outputsize=" + outputsize;
    url += "&datatype=" + datatype;
    int retries = 0;
    bool success = false;
    curl = curl_easy_init();
    if (curl != nullptr) {
        do {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
            res = curl_easy_perform(curl);
            if (res == CURLE_OK) {
                success = true;
                break;
            } else {
                std::cerr << "Attempt " << retries + 1 << " failed: " << curl_easy_strerror(res) << std::endl;
                retries++;
                if (retries < maxRetries) {
                    int delay = std::pow(2, retries) * 1000; // Exponential backoff in milliseconds
                    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                }
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
    } else {
        std::cerr << "Failed to initialize curl" << std::endl;
    }
}