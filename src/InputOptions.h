/*
 * InputOptions.h
 *
 *  Created on: 26 de mar de 2019
 *      Author: Daniel Araujo <ddaraujo@gmail.com>
 */

#include <string>

using namespace std;

#ifndef INPUTOPTIONS_H_
#define INPUTOPTIONS_H_

class InputOptions
{
  private:
  public:
	string getHelpMenuText();
	string checkOptionType(string argument);
	bool checkValidMediaType(string type);
	bool checkIfIsOption(string argument);
	string readMovieName(char **argsList, int movieNameStartIndex, int movieNameEndIndex, int movieNameSize);
	void printError(string errorMsg);
};

#endif /* INPUTOPTIONS_H_ */
