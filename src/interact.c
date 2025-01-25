#include "interact.h"

void buildUrl(char *apiKey, char *location, char *outputUrl) {

    // Empty the buffer
    outputUrl[0] = '\0';

    // Concatenate the url together
    strcat(outputUrl, "http://api.weatherapi.com/v1/current.json?key=");
    strcat(outputUrl, apiKey);
    strcat(outputUrl, "&q=");
    strcat(outputUrl, location);
    strcat(outputUrl, "&aqi=no");

}

void today(char *apiKey, char *location) {

    char url[150];
    buildUrl(apiKey, location, url);
    
    CURL *curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

}