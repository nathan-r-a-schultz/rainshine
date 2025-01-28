#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

void current(char* jsonStr);
void forecast(char* jsonStr);

#endif