#include "data.h"

int main(int argc, char* argv[])
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    try {
        if (argc > 5) {
            std::cerr << "Usage: " << argv[0] << " [adjusted] [extended_hours] [month] [outputsize] [datatype]" << std::endl;
            return 1;
        }

        const char* apikey = std::getenv("API_KEY");
        if (apikey == nullptr) {
            throw std::runtime_error("API key not found in environment variables.");
        }

        bool adjusted = (argc > 1) ? (std::string(argv[1]) == "true") : true;
        bool extended_hours = (argc > 2) ? (std::string(argv[2]) == "true") : true;
        std::string month = (argc > 3) ? argv[3] : "";
        std::string outputsize = (argc > 4) ? argv[4] : "compact";
        std::string datatype = (argc > 5) ? argv[5] : "json";
        
        // Use a lambda to start the thread
        std::thread apiThread([=]() { fetchDataWithRetry(apikey, adjusted, extended_hours, month, outputsize, datatype); });
        
        apiThread.join();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    // Clean up CURL
    curl_global_cleanup();
    
    return 0;
}