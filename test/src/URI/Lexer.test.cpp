//
// Created by juan.castellanos on 10/11/20.
//

#include "URI/Lexer.h"
#include "UriExamples.h"
#include "catch2/catch.hpp"

using namespace urii;

class LexerFixture
{
public:
  Lexer lexer;
};

TEST_CASE("should create different lexer instances", "[lexer][constructor]")
{
  Lexer lexer1;
  Lexer lexer2;

  CHECK(&lexer1 != &lexer2);
}

TEST_CASE_METHOD(LexerFixture, "should lex scheme and path of type mailto", "[scheme][path][mailto]")
{
  auto result = lexer.lex(scheme_path_mailto);

  CHECK(result.scheme == "mailto");
  CHECK(result.path == "John.Doe@example.com");
}

TEST_CASE_METHOD(LexerFixture,"should lex scheme and path of type tel", "[scheme][path][tel]")
{
  auto result = lexer.lex(scheme_path_tel);

  CHECK(result.scheme == "tel");
  CHECK(result.path == "+1-816-555-1212");
}
