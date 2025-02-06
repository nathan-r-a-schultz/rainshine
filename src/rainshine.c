#include "rainshine.h"

// gets the key and location from the environments
void fetchKeyAndLocation(char** apiKey, char** location) {
    
    // get env vars
    *apiKey = getenv("RAINSHINE_API_KEY");
    *location = getenv("RAINSHINE_LOCATION");

    // perform error checking
    if (*apiKey == NULL) {
        fprintf(stderr, "Missing API key.");
        exit(1);
    }
    else if (*location == NULL) {
        fprintf(stderr, "Missing location.");
        exit(1);
    }
    else if (*apiKey == NULL && *location == NULL) {
        fprintf(stderr, "Missing API key and location.");
        exit(1);
    }

}

// gets metric/imperial units
bool fetchUnits(void) {
    char units = getenv("RAINSHINE_UNITS");

    if ((strcmp(units, "M") == 0) || (strcmp(units, "m") == 0)) {
        return true; // true represents metric
    }
    else if ((strcmp(units, "I") == 0) || (strcmp(units, "i") == 0)) {
        return false; // false represents imperial
    }
}

// the main function handles command line arguments
int main (int argc, char *argv[]) {

    // get env vars
    char *apiKey, *location;
    bool units = fetchUnits();
    fetchKeyAndLocation(&apiKey, &location);

    // this if statement will be super long eventually. gotta find a way to handle it more efficiently
    if (argc > 1) {
        if (strcmp(argv[1], "current") == 0) {
            char* response = apiCall(apiKey, location, 1, 0);
            current(response);
        }
        else if (strcmp(argv[1], "forecast") == 0) {
            char* response = apiCall(apiKey, location, 2, atoi(argv[2]));
            forecast(response);
        }
        else if (strcmp(argv[1], "envinfo") == 0) {
            printf("API key: %s\n", apiKey);
            printf("Location: %s\n", location);
            if (units == true) {
                printf("Units: metric");
            }
            else {
                printf("Units: imperial");
            }
        }
        else if (strcmp(argv[1], "change") == 0) {
            if (strcmp(argv[2], "key") == 0) {
                system("~/.local/bin/rainshinechangekey.sh");
            }
            else if (strcmp(argv[2], "location") == 0) {
                system("~/.local/bin/rainshinechangelocation.sh");
            }
            else {
                printf("Improper usage of 'rainshine change'. To change your location, use 'rainshine change location.'. To change your API key, use 'rainshine change key.");
            }
        }
        else if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "h") == 0 || strcmp(argv[1], "-h") == 0) {
            printf("List of commands:\n");
            printf("current: Gets current weather conditions\n");
            printf("forecast [int]: Retrieves the forecast for the next number of days specified\n");
            printf("envinfo: Retrieves your API key and location\n");
            printf("change [string]: Allows the user to change either their location or their API key, specified by the using the string \"location\" or \"key\"\n");
            printf("help: Prints out all available commands\n");
        }
    }

    return 0;
}