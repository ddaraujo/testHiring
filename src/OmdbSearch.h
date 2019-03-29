/*
 * OmdbSearch.h
 *  
 *  Created on: 26 de mar de 2019
 *      Author: Daniel Araujo <ddaraujo@gmail.com>
 */

#include <string>
#include <json/json.h>

using namespace std;

#ifndef OMDBSEARCH_H_
#define OMDBSEARCH_H_

class OmdbSearch
{
private:
  string searchType;
  string searchText;
  string parsedJson;
  string parse_json(json_object *j);
  void parse_json_array(json_object *j, char *key);
  static int receive(void *buffer, size_t length, size_t size, void *data);

public:
  void setSearchType(string searchType);
  void setSearchText(string searchText);
  string getSearchType();
  string getSearchText();
  string doMediaSearch();
};

#endif /* OMDBSEARCH_H_ */