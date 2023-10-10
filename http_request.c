#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "include/http_request.h"

int post_request(int sala_id, int ocupacion_actual) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl == NULL) {
        return 128;
    }

    char *post_fields = (char*) malloc (60*sizeof(char));
    sprintf(post_fields, "sala_id=%d&ocupacion_actual=%d", sala_id, ocupacion_actual);


    struct curl_slist *headers = NULL;
    curl_slist_append(headers, "Accept: application/x-www-form-urlencoded");
    curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    curl_slist_append(headers, "charset: utf-8");

    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/ocupacion");

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcrp/0.1");

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    free(post_fields);
    return res;
}

int main(){
    printf("%d", post_request(1, 5));
    return 0;
}