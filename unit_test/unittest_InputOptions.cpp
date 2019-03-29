// Unit tests using Gtest (Google Test)

#include <limits.h>
#include "gtest/gtest.h"
#include "../src/InputOptions.h"

InputOptions opts;

/*
InputOptions.h Tests
*/

// Method:      getHelpMenuText
// Return:      string
// Description: Check if the help menu returns the correct text
TEST(InputOptionsTest, getHelpMenuTextTest)
{
  string helpMenuText = "\nOpcoes: omdbProjectVivo -s nome\n"
                        "   ou:  omdbProjectVivo [-t type] -s nome\n\n"
                        "    -h, --help       Imprime a lista de opcoes da aplicacao.\n"
                        "    -s, --search     Busca pelo titulo da media.\n"
                        "    -t, --type       Retorna o tipo media selecionado. (movie, series ou episode).\n\n"
                        " O parametro -t (--type) nao e mandatorio. Por padrao retorna todos os tipos encontrados.\n\n";
  EXPECT_EQ(helpMenuText, opts.getHelpMenuText());
}

// Method:      checkOptionType
// Return:      string
// Description: Test the accepted options and return normalized string (or error)
TEST(InputOptionsTest, checkOptionTypeTest)
{
  string optionHelpShort = "-h";
  string optionHelpLong = "--help";
  string optionTypeShort = "-t";
  string optionTypeLong = "--type";
  string optionSearchShort = "-s";
  string optionSearchLong = "--search";
  string optionErrorShort = "-a";
  string optionErrorLong = "-anythingelse";

  ASSERT_EQ("help", opts.checkOptionType(optionHelpShort));
  ASSERT_EQ("help", opts.checkOptionType(optionHelpLong));
  ASSERT_EQ("type", opts.checkOptionType(optionTypeShort));
  ASSERT_EQ("type", opts.checkOptionType(optionTypeLong));
  ASSERT_EQ("search", opts.checkOptionType(optionSearchShort));
  ASSERT_EQ("search", opts.checkOptionType(optionSearchLong));
  ASSERT_EQ("error", opts.checkOptionType(optionErrorShort));
  ASSERT_EQ("error", opts.checkOptionType(optionErrorLong));
}

// Method:      checkValidMediaType
// Return:      boolean
// Description: Check valid media types (allows only 'movie', 'series' and 'episode')
TEST(InputOptionsTest, checkValidMediaTypeTest)
{
  string mediaType1 = "movie";
  string mediaType2 = "series";
  string mediaType3 = "episode";
  string mediaTypeInvalid = "anythingelse";

  ASSERT_TRUE(opts.checkValidMediaType(mediaType1));
  ASSERT_TRUE(opts.checkValidMediaType(mediaType2));
  ASSERT_TRUE(opts.checkValidMediaType(mediaType3));
  ASSERT_FALSE(opts.checkValidMediaType(mediaTypeInvalid));
}

// Method:      checkIfIsOption
// Return:      boolean
// Description: Test it the string is an option (starts with - or --)
TEST(InputOptionsTest, checkIfIsOptionTest)
{
  string option1 = "-t";
  string option2 = "--type";
  string option3 = "anythingelse";

  ASSERT_TRUE(opts.checkIfIsOption(option1));
  ASSERT_TRUE(opts.checkIfIsOption(option2));
  ASSERT_FALSE(opts.checkIfIsOption(option3));
}

// int main(int argc, char **argv)
// {

//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
