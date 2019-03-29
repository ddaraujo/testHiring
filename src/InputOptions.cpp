/*
 * InputOptions.cpp
 *
 *  Created on: 26 de mar de 2019
 *      Author: Daniel Araujo <ddaraujo@gmail.com>
 */

#include <string>
#include <set>
#include <iostream>
#include "InputOptions.h"

using namespace std;

// Get help menu text
string InputOptions::getHelpMenuText(){
	return "\nOpcoes: omdbProjectVivo -s nome\n"
			"   ou:  omdbProjectVivo [-t type] -s nome\n\n"
			"    -h, --help       Imprime a lista de opcoes da aplicacao.\n"
			"    -s, --search     Busca pelo titulo da media.\n"
			"    -t, --type       Retorna o tipo media selecionado. (movie, series ou episode).\n\n"
			" O parametro -t (--type) nao e mandatorio. Por padrao retorna todos os tipos encontrados.\n\n";
}

// Check if the media type is valid
bool InputOptions::checkValidMediaType(string type){
	std::set<string> mediaTypes;
	mediaTypes.insert("movie");
	mediaTypes.insert("series");
	mediaTypes.insert("episode");

	return mediaTypes.find(type) != mediaTypes.end() ? true : false;
}

// Check if argument is an option switch
bool InputOptions::checkIfIsOption(string argument){
	return  argument.rfind("-",0) == 0 ? true : false;
}

// Check if the option is valid
string InputOptions::checkOptionType(string argument){
	std::set<string> optionHelp;
	optionHelp.insert("-h");
	optionHelp.insert("--help");

	std::set<string> optionSearch;
	optionSearch.insert("-s");
	optionSearch.insert("--search");

	std::set<string> optionType;
	optionType.insert("-t");
	optionType.insert("--type");

	if (optionHelp.find(argument) != optionHelp.end()) {
		return "help";
	} else if (optionSearch.find(argument) != optionSearch.end()) {
		return "search";
	} else if (optionType.find(argument) != optionType.end()) {
		return "type";
	} else {
		return "error";
	}
}

// Read the movie name from options
string InputOptions::readMovieName(char **argsList, int movieNameStartIndex, int movieNameEndIndex, int movieNameSize)
{
	string response = "";

	// Check if the movie name was typed
	if (movieNameSize == 0)
	{
		//response = "Erro: Nome do filme nao informado ou invalido...";
		response = "";
	}
	else
	{
		// build the media name from last arguments
		for (int i = movieNameStartIndex; i < movieNameEndIndex; ++i)
		{
			// Check if another parameter was found after the movie name
			if (checkIfIsOption(argsList[i]))
			{
				//response = "Erro: Parametro invalido ou fora de contexto.";
				response = "";
			}
			else
			{
				// Put + signal into movie name text
				if (i == movieNameStartIndex)
				{
					response = argsList[i];
				}
				else
				{
					response += '+';
					response += argsList[i];
				}
			}
		}
		return response;
	}
}

// Print error message with menu
void InputOptions::printError(string errorMsg)
{
	cout << getHelpMenuText() << endl;
	cout << "Erro: " << errorMsg << endl;
}
