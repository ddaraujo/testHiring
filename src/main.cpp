//============================================================================
// Name        : main.cpp
// Author      : Daniel Araujo
// Version     : 1.00
// Description : OMDB Movie Search - Paytv Hiring Test
//============================================================================

#include <iostream>
#include <string>
#include "InputOptions.h"
#include "OmdbSearch.h"

using namespace std;

InputOptions opt;
OmdbSearch search;

int main(int argc, char *argv[])
{
	// Local Variables
	int movieNameStartIndex;
	int movieNameEndIndex = argc;
	int movieNameSize;

	// Check if any argument was provided
	if (argc <= 1)
	{
		opt.printError("Nenhum parametro informado.");
		return 1;
	}

	// Check if user ask for help
	if (!opt.checkOptionType(argv[1]).compare("help"))
	{
		cout << opt.getHelpMenuText() << endl;
		return 0;
	}

	// Check if the first argument is a type option
	if (!opt.checkOptionType(argv[1]).compare("type"))
	{
		try
		{
			if (opt.checkValidMediaType(argv[2]))
			{
				search.setSearchType(argv[2]);

				// Check if the movie name was informed
				if (!opt.checkOptionType(argv[3]).compare("search"))
				{
					movieNameStartIndex = 4;
					movieNameSize = argc - movieNameStartIndex;
					string movieName = opt.readMovieName(argv, movieNameStartIndex, movieNameEndIndex, movieNameSize);
					search.setSearchText(movieName);
				}
				else
				{
					opt.printError("Nome do filme nao informado ou invalido.");
					return 1;
				}
			}
			else
			{
				opt.printError("Tipo de midia nao informado ou invalido");
				return 1;
			}
		}
		catch (exception &e)
		{
			opt.printError("Parametro invalido ou fora de contexto.");
			return 1;
		}
	}
	// Check if the first argument is a search option
	else if (!opt.checkOptionType(argv[1]).compare("search"))
	{
		movieNameStartIndex = 2;
		movieNameSize = argc - movieNameStartIndex;
		string movieName = opt.readMovieName(argv, movieNameStartIndex, movieNameEndIndex, movieNameSize);
		if (!movieName.empty())
		{
			search.setSearchText(movieName);
		}
		else
		{
			opt.printError("Nome do filme nao informado ou invalido...");
		}
	}
	else
	{
		opt.printError("Parametro invalido ou fora de contexto.");
		return 1;
	}

	//Start the movie search
	string searchResponse = search.doMediaSearch();

	// Print the response
	cout << searchResponse << endl;

	return 0;
}