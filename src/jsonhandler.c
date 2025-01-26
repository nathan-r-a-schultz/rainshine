#include "jsonhandler.h"

void today(char* jsonStr) {

    //printf("JSON: %s\n", jsonStr);

    cJSON *json = cJSON_Parse(jsonStr);

    if (json == NULL) {
        printf("Error parsing JSON\n");
        return;
    }

    cJSON *temperature = cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "current"), "temp_c");

    if (cJSON_IsNumber(temperature)) {
        printf("Temperature: %.1f°C\n", temperature->valuedouble);
    } else {
        printf("Error: 'temp_c' not found or not a number.\n");
    }

    // Clean up memory
    cJSON_Delete(json);
}