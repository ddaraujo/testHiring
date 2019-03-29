// Unit tests using Gtest (Google Test)

#include <limits.h>
#include "gtest/gtest.h"
#include "../src/OmdbSearch.h"

/*
OmdbSearch.h Tests
*/

// Test Getter and Setter for SearchType
TEST(OmdbSearchTest, SearchTypeTest)
{
  OmdbSearch search;
  string searchType = "movie";
  search.setSearchType(searchType);
  ASSERT_EQ("movie", search.getSearchType());
}

// Test Getter and Setter for searchText
TEST(OmdbSearchTest, SearchTextTest)
{
  OmdbSearch search;
  string searchText = "Titanic";
  search.setSearchText(searchText);
  ASSERT_EQ("Titanic", search.getSearchText());
}

// Test the json request ans response
TEST(OmdbSearchTest, doMediaSearch)
{
  OmdbSearch search;
  string searchText = "Click";
  string searchType = "movie";
  search.setSearchType(searchType);
  search.setSearchText(searchText);
  string responseMovieSearch = "Title - Click\n"
                               "Year - 2006\n"
                               "Rated - PG-13\n"
                               "Released - 23 Jun 2006\n"
                               "Runtime - 107 min\n"
                               "Genre - Comedy, Drama, Fantasy, Romance\n"
                               "Director - Frank Coraci\n"
                               "Writer - Steve Koren, Mark O'Keefe\n"
                               "Actors - Adam Sandler, Kate Beckinsale, Christopher Walken, David Hasselhoff\n"
                               "Plot - A workaholic architect finds a universal remote that allows him to fast-forward and rewind to different parts of his life. Complications arise when the remote starts to overrule his choices.\n"
                               "Language - English, Portuguese, Japanese\n"
                               "Country - USA\n"
                               "Awards - Nominated for 1 Oscar. Another 3 wins & 11 nominations.\n"
                               "Poster - https://m.media-amazon.com/images/M/MV5BMTA1MTUxNDY4NzReQTJeQWpwZ15BbWU2MDE3ODAxNw@@._V1_SX300.jpg\n"
                               "Ratings:\n"
                               "Internet Movie Database: 6.4/10\n"
                               "Rotten Tomatoes: 33%\n"
                               "Metacritic: 45/100\n"
                               "Metascore - 45\n"
                               "Type - movie\n"
                               "DVD - 10 Oct 2006\n"
                               "BoxOffice - $137,340,146\n"
                               "Production - Sony Pictures Releasing\n"
                               "Website - http://www.sonypictures.com/movies/click/\n";
  EXPECT_EQ(responseMovieSearch, std::string(search.doMediaSearch()));
}
