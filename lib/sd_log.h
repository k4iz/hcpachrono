#ifndef SD_LOG_H
#define SD_LOG_H

bool initSDCard(int pinCS);

bool writeDatalogSDCard(String filename, String datalogLine);

#endif
