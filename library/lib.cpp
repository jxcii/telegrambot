#include "lib.h"
#include <curl/curl.h>
size_t WriteCallback(void* contents, size_t size, size_t nmemb, FILE* file) {
    return fwrite(contents, size, nmemb, file);
}
void DownloadFileToJXSERVER(TgBot::Bot& bot, TgBot::Message::Ptr message, int type)
{
    std::string fileName;
    CURL *curl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        // URL of the image file to download
        std::string url = "https://api.telegram.org/file/bot5310616909:AAHqrFdIoW21YPTAtnAxDRzSVJoILL4XjG4/";
        if(type == 0) {
            fileName = bot.getApi().getFile(message->document->fileId)->filePath.substr(10);
            url.append(bot.getApi().getFile(message->document->fileId)->filePath);
        }
        // std::ofstream fi(bot.getApi().getFile(message->document->fileId)->filePath.c_str(), std::ios::trunc);
        //  Open a binary file to write the downloaded data
        FILE *file = fopen(fileName.c_str(), "wb");
        if (!file)
        {
            std::cerr << "Error opening file for writing." << std::endl;
            return;
        }
        // Set the URL to download
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the callback function to write binary data to the file
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        // Perform the download
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
        {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }

        // Clean up
        fclose(file);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }
    else
    {
        std::cerr << "cURL initialization failed." << std::endl;
        return;
    }
}