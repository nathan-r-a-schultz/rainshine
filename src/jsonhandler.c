#include "jsonhandler.h"

// basic template for future outputs
void current(char* jsonStr) {

    // parse the string into json
    cJSON *json = cJSON_Parse(jsonStr);

    // handle json parsing related errors
    if (json == NULL) {
        printf("Error parsing JSON\n");
        return;
    }

    // get the appropriate json key
    cJSON *current = cJSON_GetObjectItemCaseSensitive(json, "current");
    if (!current) {
        printf("Error: 'current' object not found\n");
        cJSON_Delete(json);
        return;
    }

    // get relevant weather info
    cJSON *temperature = cJSON_GetObjectItemCaseSensitive(current, "temp_c");
    cJSON *feelsLike = cJSON_GetObjectItemCaseSensitive(current, "feelslike_c");
    cJSON *precipitation = cJSON_GetObjectItemCaseSensitive(current, "precip_mm");
    cJSON *uv = cJSON_GetObjectItemCaseSensitive(current, "uv");
    cJSON *condition = cJSON_GetObjectItemCaseSensitive(current, "condition");
    cJSON *skyConditions = condition ? cJSON_GetObjectItemCaseSensitive(condition, "text") : NULL;

    // check if the extraction of the weather info is valid
    if (cJSON_IsNumber(temperature) &&
        cJSON_IsNumber(feelsLike) &&
        cJSON_IsNumber(precipitation) &&
        cJSON_IsNumber(uv) &&
        cJSON_IsString(skyConditions)) {
        
        // print info
        printf("Current weather conditions:\n");
        printf("Sky conditions: %s\n", skyConditions->valuestring);
        printf("Temperature: %.1f°C\n", temperature->valuedouble);
        printf("Feels like: %.1f°C\n", feelsLike->valuedouble);
        printf("Precipitation: %.1fmm\n", precipitation->valuedouble);
        printf("UV: %.1f\n", uv->valuedouble);
    } else {
        printf("Error: one or more JSON key/value could not be parsed.\n");
    }

    // writing this here so I don't forget it: [TODO] add support for imperial units
    // probably easiest to ask the user if they prefer metric or imperial during the setup script...
    // ...and instead of having to have different cases for parsing JSON based on metric or imperial...
    // ...I can instead just always parse metric and only convert to imperial if the user has set their preference to imperial

    // Clean up memory
    cJSON_Delete(json);
}

void forecast(char* jsonStr) {
    /* 
       NOTE: i think i've already decided to somewhat scrap the outline below but i'm keeping it in the code for now in case i change my mind and decide to use it

       the forecast command will be executed as outlined below:

       using "rainshine forecast 2" will give the forecast two days from now
       using "rainshine forecast 2 -d" will give the forecast two days from now
       using "rainshine forecast 2 -h" will give the forecast two hours from now

       using "rainshine forecast 2:4" will give the forecast for two and three days from now, but not four
       using "rainshine forecast 2:4 -d" will give the forecast for two and three days from now, but not four
       using "rainshine forecast 2:4 -h" will give the forecast for two and three hours from now, but not four

       the -d flag will be the default, which technically means the -d flag is redundant... but i'm going to keep it anyway. viewing hours will require -h.

    */

    // parse the string into json
    cJSON *json = cJSON_Parse(jsonStr);

    // handle json parsing related errors
    if (json == NULL) {
        printf("Error parsing JSON\n");
        return;
    }

    // get the appropriate json key
    cJSON *forecast = cJSON_GetObjectItemCaseSensitive(json, "forecast");
    if (!cJSON_IsObject(forecast)) {
        printf("Error: 'forecast' object not found\n");
        cJSON_Delete(json);
        return;
    }

    cJSON *forecastday = cJSON_GetObjectItemCaseSensitive(forecast, "forecastday");
    if (!cJSON_IsArray(forecastday)) {
        printf("No forecast day array found.\n");
        cJSON_Delete(json);
        return;
    }

    // get day and create an array for each day
    cJSON *day;
    cJSON_ArrayForEach(day, forecastday) {

        // create a date object and print it
        cJSON *date = cJSON_GetObjectItemCaseSensitive(day, "date");
        printf("\nDate: %s\n", date->valuestring);

        // make an array for the hours
        cJSON *hour_array = cJSON_GetObjectItemCaseSensitive(day, "hour");
        if (!cJSON_IsArray(hour_array)) {
            printf("No hourly forecast data available.\n");
            continue;
        }

        // create each hour in the array
        cJSON *hour;
        cJSON_ArrayForEach(hour, hour_array) {

            // get info for that hour
            cJSON *time = cJSON_GetObjectItemCaseSensitive(hour, "time");
            cJSON *temp_c = cJSON_GetObjectItemCaseSensitive(hour, "temp_c");
            cJSON *condition = cJSON_GetObjectItemCaseSensitive(hour, "condition");
            cJSON *condition_text = condition ? cJSON_GetObjectItemCaseSensitive(condition, "text") : NULL;

            // print the info out
            printf("Time: %s, Temperature: %.1f°C, Condition: %s\n",
                   time ? time->valuestring : "Unknown",
                   temp_c ? temp_c->valuedouble : 0.0,
                   condition_text ? condition_text->valuestring : "Unknown");
        }
    }

    cJSON_Delete(json);

}