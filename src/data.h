//
// Created by velocitatem on 10/9/24.
//

#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <thread>
#include <nlohmann/json.hpp>
#include <fstream>
#include <functional>
#include <chrono>
#include <regex>
#include <boost/algorithm/string.hpp>
#include <cstdlib>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
void fetchDataWithRetry(const std::string& apikey,
    bool adjusted = true,
    bool extended_hours = true,
    const std::string& month = "",
    const std::string& outputsize = "compact",
    const std::string& datatype = "json",
    int maxRetries = 3);


#endif //DATA_H
