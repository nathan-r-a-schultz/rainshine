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

// the main function handles command line arguments
int main (int argc, char *argv[]) {

    // get env vars
    char *apiKey, *location;
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
        }
        else if (strcmp(argv[1], "change") == 0) {
            if (strcmp(argv[2], "key") == 0) {
                system("~/.local/bin/rainshinechangekey.sh");
            }
            else if (strcmp(argv[2], "location") == 0) {
                system("~/.local/bin/rainshinechangelocation.sh");
            }
        }
    }

    return 0;
}