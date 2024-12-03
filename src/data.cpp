#include "data.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

void fetchDataWithRetry(const std::string& apikey, bool adjusted, bool extended_hours, const std::string& month, const std::string& outputsize, const std::string& datatype, int maxRetries, const std::string& symbol) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    int retries = 0;
    bool success = false;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=" + symbol + "&interval=1min&apikey=" + apikey + "&datatype=" + datatype + "&outputsize=" + outputsize;
        if (adjusted) {
            url += "&adjusted=true";
        }
        if (extended_hours) {
            url += "&extended_hours=true";
        }
        if (!month.empty()) {
            url += "&month=" + month;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        do {
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                retries++;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            } else {
                success = true;
            }
        } while (!success && retries < maxRetries);

        if (success) {
            std::ofstream outFile("output.json");
            outFile << readBuffer;
            outFile.close();
        }

        curl_easy_cleanup(curl);
    }
}