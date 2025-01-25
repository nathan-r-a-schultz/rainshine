#include "rainshine.h"

void fetchKeyAndLocation(char** apiKey, char** location) {
    
    *apiKey = getenv("RAINSHINE_API_KEY");
    *location = getenv("RAINSHINE_LOCATION");

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

int main (int argc, char *argv[]) {

    char *apiKey, *location;

    fetchKeyAndLocation(&apiKey, &location);

    if (argc > 1) {
        if (strcmp(argv[1], "today") == 0) {
            today(apiKey, location);
        }
        if (strcmp(argv[1], "envinfo") == 0) {
            printf("API key: %s\n", apiKey);
            printf("Location: %s\n", location);
        }
    }

    return 0;
}