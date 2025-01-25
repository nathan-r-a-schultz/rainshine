#ifndef INTERACT_H
#define INTERACT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <curl/curl.h>

void buildUrl(char* apiKey, char* location, char* outputUrl);
void today(char* apiKey, char* location);

#endif
