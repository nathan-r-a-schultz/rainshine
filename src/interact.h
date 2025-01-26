#ifndef INTERACT_H
#define INTERACT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

size_t callback(char *data, size_t size, size_t nmemb, void *clientp);
void buildUrl(char* apiKey, char* location, char* outputUrl);
char* apiCall(char* apiKey, char* location);
void today(char* response);

#endif
