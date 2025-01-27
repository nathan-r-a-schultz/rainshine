#include "jsonhandler.h"

// basic template for future outputs
void now(char* jsonStr) {

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