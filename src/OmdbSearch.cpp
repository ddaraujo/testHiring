/*
 * OmdbSearch.cpp
 *
 *  Created on: 26 de mar de 2019
 *      Author: Daniel Araujo <ddaraujo@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <json/json.h>

#include "OmdbSearch.h"

using namespace std;

// OMDB data (ORL AND API KEY)
#define OMDBURL "http://www.omdbapi.com/"
#define APIKEY "e2a41a29"

#define URL_SZ 512
#define BUF_SZ 10 * 1024

long written = 0;

// Set search type
void OmdbSearch::setSearchType(string searchType)
{
    this->searchType = searchType;
}

// get search type
string OmdbSearch::getSearchType()
{
    return this->searchType;
}

// set search text
void OmdbSearch::setSearchText(string searchText)
{
    this->searchText = searchText;
}

// get search text
string OmdbSearch::getSearchText()
{
    return this->searchText;
}

// Save the received data into a memory buffer (Used by Curl)
int OmdbSearch::receive(void *buffer, size_t length, size_t size, void *data)
{
    size_t l = length * size;

    if (l > 0)
    {
        if (written + l >= BUF_SZ)
        {
            fprintf(stderr, "Buffer size exceeded.\n");
            return 0;
        }
        memcpy(&((char *)data)[written], buffer, l);
        written += l;
    }
    return l;
}

// Parse JSON arrays
void OmdbSearch::parse_json_array(json_object *j, char *key)
{
    enum json_type type;

    json_object *a = j;
    if (key)
    {
        a = json_object_object_get(j, key);
    }

    int l = json_object_array_length(a);
    int i;
    json_object *v;
    for (i = 0; i < l; i++)
    {
        v = json_object_array_get_idx(a, i);
        type = json_object_get_type(v);
        if (type == json_type_array)
        {
            parse_json_array(v, NULL);
        }
        else
        {
            parse_json(v);
        }
    }
}

// Parse the json received from OMDBs search
string OmdbSearch::parse_json(json_object *j)
{
    enum json_type type;

    json_object_object_foreach(j, key, v)
    {
        type = json_object_get_type(v);
        switch (type)
        {
        case json_type_boolean:
        case json_type_double:
        case json_type_int:
        case json_type_string:
            // Specific format for "ratings"
            if (strcmp(key, "Source") == 0)
            {

                this->parsedJson += std::string(json_object_get_string(v)) + ": ";
            }
            else if (strcmp(key, "Value") == 0)
            {
                this->parsedJson += std::string(json_object_get_string(v)) + "\n";
            }
            // Remove the response data
            else if (strcmp(key, "Response") == 0)
            {
                continue;
            }
            // Remove the imdbXXXX data
            else if (strncmp(key, "imdb", 4) == 0)
            {
                continue;
            }
            else
            {
                this->parsedJson += std::string(key) + " - " + std::string(json_object_get_string(v)) + "\n";
            }
            break;

        case json_type_array:
            if (strcmp(key, "Ratings") != 0)
            {
                continue;
            }
            this->parsedJson += "Ratings: \n";
            parse_json_array(j, key);
            break;
        }
    }

    return this->parsedJson;
}

// Search for the media
string OmdbSearch::doMediaSearch()
{
    int r = -1;
    char url[URL_SZ];
    char data[BUF_SZ];

    memset(url, 0, sizeof(url));
    memset(data, 0, BUF_SZ);
    written = 0;

    // Fill the search parameters
    if (!this->searchType.empty())
    {
        sprintf(url, "%s?t=%s&type=%s&apikey=%s", OMDBURL, const_cast<char *>(this->searchText.c_str()), const_cast<char *>(this->searchType.c_str()), APIKEY);
    }
    else
    {
        sprintf(url, "%s?t=%s&apikey=%s", OMDBURL, const_cast<char *>(this->searchText.c_str()), APIKEY);
    }

    // Get the JSon using CURL
    CURL *c = curl_easy_init();
    curl_easy_setopt(c, CURLOPT_URL, url);
    curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, receive);
    curl_easy_setopt(c, CURLOPT_NOPROGRESS, 1);
    curl_easy_setopt(c, CURLOPT_FAILONERROR, 1);
    curl_easy_setopt(c, CURLOPT_WRITEDATA, data);
    curl_easy_setopt(c, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(c, CURLOPT_TIMEOUT, 10);

    r = curl_easy_perform(c);
    curl_easy_cleanup(c);
    if (r != 0)
    {
        fprintf(stderr, "Curl Error: %d\n", r);
    }

    // Parse the JSON data
    json_object *j = json_tokener_parse(data);
    return parse_json(j);
}