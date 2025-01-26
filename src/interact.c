#include "interact.h"

// create memory object
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

// build the url to make the api call
void buildUrl(char *apiKey, char *location, char *outputUrl) {

    // empty the buffer
    outputUrl[0] = '\0';

    // concatenate the url together
    strcat(outputUrl, "http://api.weatherapi.com/v1/current.json?key=");
    strcat(outputUrl, apiKey);
    strcat(outputUrl, "&q=");
    strcat(outputUrl, location);
    strcat(outputUrl, "&aqi=no");

}

// perform a call to weatherapi.com
char* apiCall(char *apiKey, char *location) {

    // create and build url
    char url[150];
    buildUrl(apiKey, location, url);

    // create a memory chunk and init curl
    struct memory chunk = {0};
    CURLcode res;
    CURL *curl = curl_easy_init();
    char *response = NULL;

    if (curl) {

        // set up the curl calls
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        // perform the curl call
        res = curl_easy_perform(curl);

        // check if the response is okay
        if (res == CURLE_OK && chunk.response) {
            response = strdup(chunk.response);
        } else {
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(res));

        }

        // free up the allocated memory and clean up curl
        free(chunk.response);
        curl_easy_cleanup(curl);
    }
    else {
        printf("Failure to initialise cURL. Request aborted.");
    }

    return response;

}