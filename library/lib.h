#ifndef LIB_H
#define LIB_H
#include <tgbot/tgbot.h>

std::string DownloadFileToJXSERVER(TgBot::Bot& bot, TgBot::Message::Ptr message, int type = 0);

#endif
