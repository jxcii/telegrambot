#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include "lib.h"
int main() {
    TgBot::Bot bot("5310616909:AAHqrFdIoW21YPTAtnAxDRzSVJoILL4XjG4");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if(1){
            printf("User wrote %s\n", message->text.c_str());
            if (StringTools::startsWith(message->text, "/start")) {
                return;
            }
            if (message->document != nullptr)
            { 
                bot.getApi().sendDocument(message->chat->id, TgBot::InputFile::fromFile(DownloadFileToJXSERVER(bot, message), message->document->mimeType));
            }
        }
    });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}
