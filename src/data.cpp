// Importing headers

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <curl/curl.h>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <curl/curl.h>
#include <json/json.h>


namespace
{
    std::size_t callback(
        const char* in,
        std::size_t size,
        std::size_t num,
        std::string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
    
}

int main()
{
    // URL API 
    const std::string url("http://www.omdbapi.com/?t=Game%20of%20Thrones&Season=1&apikey=52f474d7");

    CURL* curl = curl_easy_init();

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Response Info
    long httpCode(0);
    std::unique_ptr<std::string> httpData(new std::string());

    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    if (httpCode == 200) 
    
    {
        std::cout << "\nSuccessful response from " << url << std::endl;

        // Parse JSON response
        Json::Value jsonData;
        Json::Reader jsonReader;

        if (jsonReader.parse(*httpData.get(), jsonData)) 
        
        {
            std::cout << "Parsed JSON data" << std::endl;
            std::cout << "\nJSON data received:" << std::endl;
            std::cout << jsonData.toStyledString() << std::endl;

                // Extract specific fields
            std::string title = jsonData["Title"].asString();
            double rating = std::stod(jsonData["imdbRating"].asString());

            std::cout << "Title is: " << title << std::endl;
            std::cout << "Rating is: " << rating << std::endl;

        }
        else 
        
        {
            std::cerr << "Could not parse HTTP data as JSON" << std::endl;
            std::cerr << "HTTP data was:\n" << *httpData.get() << std::endl;
            return 1;

        }

    } 
    
    else 
        
    {
        std::cerr << "Couldn't GET from " << url << " - exiting" << std::endl;
        return 1;
    }

    return 0;

}


