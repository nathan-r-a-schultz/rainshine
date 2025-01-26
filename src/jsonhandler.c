#include "jsonhandler.h"

// basic template for future outputs
void today(char* jsonStr) {

    // parse the string into json
    cJSON *json = cJSON_Parse(jsonStr);

    // handle json parsing related errors
    if (json == NULL) {
        printf("Error parsing JSON\n");
        return;
    }

    // get the temperature parameter
    cJSON *temperature = cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "current"), "temp_c");

    // print out the temperature
    if (cJSON_IsNumber(temperature)) {
        printf("Temperature: %.1f°C\n", temperature->valuedouble);
    } else {
        printf("Error: 'temp_c' not found or not a number.\n");
    }

    // Clean up memory
    cJSON_Delete(json);
}