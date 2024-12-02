#include "data.h"
using json = nlohmann::json;
using namespace std;

int main(int argc, char* argv[])
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    try {
        if (argc > 6) {
            std::cerr << "Usage: " << argv[0] << "[stonk] [adjusted] [extended_hours] [month] [outputsize] [datatype]" << std::endl;
            return 1;
        }

        const char* apikey = std::getenv("API_KEY");
        if (apikey == nullptr) {
            throw std::runtime_error("API key not found in environment variables.");
        }

        const char *stonk = (argc > 1) ? argv[1] : "AAPL";
        bool adjusted = (argc > 2) ? (std::string(argv[2]) == "true") : true;
        bool extended_hours = (argc > 3) ? (std::string(argv[3]) == "true") : true;
        std::string month = (argc > 4) ? argv[4] : "";
        std::string outputsize = (argc > 5) ? argv[5] : "compact";
        std::string datatype = (argc > 6) ? argv[6] : "json";

        // Use a lambda to start the thread
        std::thread apiThread([=]() { fetchDataWithRetry(apikey, adjusted, extended_hours, month, outputsize, datatype, 3, stonk); });
        
        apiThread.join();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    // Clean up CURL
    curl_global_cleanup();


    // Read JSON file

    return 0;
}