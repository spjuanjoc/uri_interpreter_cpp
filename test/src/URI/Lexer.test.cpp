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

TEST_CASE_METHOD(LexerFixture,"should lex scheme and path of type urn", "[scheme][path][urn]")
{
  auto result = lexer.lex(scheme_path_urn);

  CHECK(result.scheme == "urn");
  CHECK(result.path == "oasis:names:specification:docbook:dtd:xml:4.1.2");
}

TEST_CASE_METHOD(LexerFixture, "should lex scheme and path of type news", "[scheme][path][news]")
{
  auto result = lexer.lex(scheme_path_news);

  CHECK(result.scheme == "news");
  CHECK(result.path == "comp.infosystems.www.servers.unix");
}

TEST_CASE_METHOD(LexerFixture, "should lex authority IPv4", "[IPv4]")
{
  auto result = lexer.lex(scheme_authorityIPv4);

  CHECK(result.scheme == "telnet");
  CHECK(result.authority == "192.0.2.16:80");
}

TEST_CASE_METHOD(LexerFixture, "should lex authority IPv4 and path", "[IPv4][path]")
{
  auto result = lexer.lex(scheme_authorityIPv4_path);

  CHECK(result.scheme == "telnet");
  CHECK(result.authority == "192.0.2.17:80");
  CHECK(result.path == "path");
}

TEST_CASE_METHOD(LexerFixture, "should lex authority IPv6, path, and query", "[IPv6][path][query]")
{
  auto result = lexer.lex(scheme_authorityIPv6_path_query);

  CHECK(result.scheme == "ldap");
  CHECK(result.authority == "[2001:db8::7]");
  CHECK(result.path == "c=GB?objectClass?one");
}

TEST_CASE_METHOD(LexerFixture, "should lex path, query, and fragment", "[RN][path][query][fragment]")
{
  auto result = lexer.lex(registeredname_path_query_fragment);

  CHECK(result.scheme == "https");
  CHECK(result.authority == "john.doe@example.com:123");
  CHECK(result.path == "/forum/questions/?tag=networking&order=newest#top");
}
