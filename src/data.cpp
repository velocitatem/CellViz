// Importing headers
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <curl/curl.h>
#include <json/json.h>

// Callback function to handle the data response
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

// Function to fetch data from the API and return it as a JSON object
Json::Value fetchData(const std::string& url)
{
    CURL* curl = curl_easy_init();

    // Set remote URL
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Response Info
    long httpCode(0);
    std::unique_ptr<std::string> httpData(new std::string());

    // Hook up data handling function
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    // Perform the request and get response code
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    // Check if the request was successful
    if (httpCode == 200) 
    {
        std::cout << "\nSuccessful response from " << url << std::endl;

        // Parse JSON response
        Json::Value jsonData;
        Json::Reader jsonReader;

        if (jsonReader.parse(*httpData.get(), jsonData)) 
        {
            std::cout << "Parsed JSON data" << std::endl;
            return jsonData;  // Return parsed JSON data
        } 
        else 
        {
            std::cerr << "Could not parse HTTP data as JSON" << std::endl;
            std::cerr << "HTTP data was:\n" << *httpData.get() << std::endl;
            return Json::nullValue;  // Return null value on parse error
        }
    } 
    else 
    {
        std::cerr << "Couldn't GET from " << url << " - exiting" << std::endl;
        return Json::nullValue;  // Return null value on HTTP error
    }
}

// Function that someone else can call to get the specific data
void getMovieData()
{
    const std::string url("http://www.omdbapi.com/?t=Game%20of%20Thrones&Season=1&apikey=52f474d7");

    // Fetch data from API
    Json::Value jsonData = fetchData(url);

    // If the data is valid, extract specific fields
    if (!jsonData.isNull()) 
    {
        std::string title = jsonData["Title"].asString();
        double rating = std::stod(jsonData["imdbRating"].asString());

        std::cout << "Title: " << title << std::endl;
        std::cout << "Rating: " << rating << std::endl;
    }
    else
    {
        std::cerr << "Failed to fetch or parse the movie data." << std::endl;
    }
}

int main()
{
    // Call the function to get movie data
    getMovieData();

    return 0;
}

