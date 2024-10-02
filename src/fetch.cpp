
// Importing headers
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include <fstream>
#include <sstream>
#include <iomanip>

std::string urlEncode(const std::string& str)
{
    std::ostringstream oss;
    for (char c : str)
    {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
            oss << c;
        else
            oss << '%' << std::uppercase << std::hex << static_cast<int>(static_cast<unsigned char>(c));
    }
    return oss.str();
}

namespace
{
    std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}

int main()
{
    // Show Title
    std::string showTitle;
    std::cout << "Enter the show title: ";
    std::getline(std::cin, showTitle);

    
    showTitle = urlEncode(showTitle);

    
    std::string apiKey = "52f474d7";  
    std::string urlBase = "http://www.omdbapi.com/?t=" + showTitle + "&Season=";


    Json::Value showData;

    std::ofstream file("show_data.json");

    for (int season = 1; season <= 10; ++season)
    {
        std::string url = urlBase + std::to_string(season) + "&apikey=" + apiKey;
        std::cout << "Fetching data for season " << season << " from URL: " << url << std::endl;

        CURL* curl = curl_easy_init();
        if (curl)
        {
            // Set the URL and curl options
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            // Response info
            long httpCode(0);
            std::unique_ptr<std::string> httpData(new std::string());

            // Hook up data handling function
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

            // Perform the request
            curl_easy_perform(curl);
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
            curl_easy_cleanup(curl);

            if (httpCode == 200)
            {
                std::cout << "Successfully fetched data for season " << season << std::endl;

                // Parse JSON response
                Json::Value seasonData;
                Json::Reader jsonReader;

                if (jsonReader.parse(*httpData.get(), seasonData))
                {
                    std::cout << "Parsed JSON data for season " << season << std::endl;

                    // Check if the season data exists (if the show doesn't have that many seasons, break the loop)
                    if (!seasonData.isMember("Episodes"))
                    {
                        std::cout << "No more seasons found. Exiting loop." << std::endl;
                        break;
                    }

                    // Add season data to the main show data
                    showData["Seasons"][std::to_string(season)] = seasonData;
                }
                else
                {
                    std::cerr << "Failed to parse HTTP data for season " << season << " as JSON" << std::endl;
                }
            }
            else
            {
                std::cerr << "Failed to fetch data from " << url << std::endl;
                break;
            }
        }
        else
        {
            std::cerr << "CURL initialization failed!" << std::endl;
            return 1;
        }
    }

    // Write the show data to the JSON file
    if (file.is_open())
    {
        file << showData.toStyledString();  // Write the JSON data to the file
        file.close();
        std::cout << "All show data has been saved to show_data.json" << std::endl;
    }

    return 0;
}
