#include "interact.h"

struct memory {
  char *response;
  size_t size;
};

// code for this function provided by the documentation at https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
size_t callback(char *data, size_t size, size_t nmemb, void *clientp) {
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)clientp;
 
    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(!ptr) {
        printf("Not enough memory to provide a response.\n");
        return 0;
    }
    
 
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;
 
    return realsize;
}

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

char* apiCall(char *apiKey, char *location) {

    char url[150];
    buildUrl(apiKey, location, url);

    struct memory chunk = {0};
    CURLcode res;
    CURL *curl = curl_easy_init();

    char *response = NULL;

    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK && chunk.response) {
            response = strdup(chunk.response);
        } else {
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(res));

        }

        free(chunk.response);
        curl_easy_cleanup(curl);
    }
    else {
        printf("Failure to initialise cURL. Request aborted.");
    }

    return response;

}

void today(char* response) {
    printf("Response: %s\n", response);
}