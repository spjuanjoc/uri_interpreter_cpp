/**
 * Created by juan.castellanos on 2/06/21.
*/

#include "URI/Lexer.h"

#include "UriExamples.h"
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

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

TEST_CASE_METHOD(LexerFixture, "should lex and empty URI", "[empty]")
{
  lexer.setUri("");
  auto result = lexer.lex();

  CHECK(result.scheme.empty());
  CHECK(result.authority.empty());
  CHECK(result.path.empty());
  CHECK(result.query.empty());
  CHECK(result.fragment.empty());
}

TEST_CASE_METHOD(LexerFixture, "should lex scheme and path of type mailto", "[scheme][path][mailto]")
{
  lexer.setUri(scheme_path_mailto);
  auto result = lexer.lex();

  CHECK(result.scheme == "mailto");
  CHECK(result.path == "John.Doe@example.com");
}

TEST_CASE_METHOD(LexerFixture, "should lex scheme and path of type tel", "[scheme][path][tel]")
{
  lexer.setUri(scheme_path_tel);
  auto result = lexer.lex();

  CHECK(result.scheme == "tel");
  CHECK(result.path == "+1-816-555-1212");
}

TEST_CASE_METHOD(LexerFixture, "should lex scheme and path of type urn", "[scheme][path][urn]")
{
  lexer.setUri(scheme_path_urn);
  auto result = lexer.lex();

  CHECK(result.scheme == "urn");
  CHECK(result.path == "oasis:names:specification:docbook:dtd:xml:4.1.2");
}

TEST_CASE_METHOD(LexerFixture, "should lex scheme and path of type news", "[scheme][path][news]")
{
  lexer.setUri(scheme_path_news);
  auto result = lexer.lex();

  CHECK(result.scheme == "news");
  CHECK(result.path == "comp.infosystems.www.servers.unix");
}

TEST_CASE_METHOD(LexerFixture, "should lex authority IPv4", "[IPv4]")
{
  lexer.setUri(scheme_authorityIPv4);
  auto result = lexer.lex();

  CHECK(result.scheme == "telnet");
  CHECK(result.authority == "192.0.2.16:80");
}

TEST_CASE_METHOD(LexerFixture, "should lex authority IPv4 and path", "[IPv4][path]")
{
  lexer.setUri(scheme_authorityIPv4_path);
  auto result = lexer.lex();

  CHECK(result.scheme == "telnet");
  CHECK(result.authority == "192.0.2.17:80");
  CHECK(result.path == "path");
}

TEST_CASE_METHOD(LexerFixture, "should lex authority IPv6, path, and multi query", "[IPv6][path][query]")
{
  lexer.setUri(scheme_authorityIPv6_path_query);
  auto result = lexer.lex();

  CHECK(result.scheme == "ldap");
  CHECK(result.authority == "[2001:db8::7]");
  CHECK(result.path == "c=GB");
  CHECK(result.query == "objectClass?one");
}

TEST_CASE_METHOD(LexerFixture, "should lex path, query, and fragment", "[RN][path][query][fragment]")
{
  lexer.setUri(name_path_query_fragment);
  auto result = lexer.lex();

  CHECK(result.scheme == "https");
  CHECK(result.authority == "john.doe@example.com:123");
  CHECK(result.path == "/forum/questions/");
  CHECK(result.query == "tag=networking&order=newest");
  CHECK(result.fragment == "top");
}

TEST_CASE_METHOD(LexerFixture, "should lex name, path, and fragment", "[RN][path][fragment]")
{
  lexer.setUri(name_path_fragment);
  auto result = lexer.lex();

  CHECK(result.scheme == "https");
  CHECK(result.authority == "spjuanjoc.github.io");
  CHECK(result.path == "/avanzado/fechas-formato-estandar/");
  CHECK(result.fragment == "usando-la-biblioteca-fmt");
}

TEST_CASE("should benchmark the lexer", "[lex][benchmark]")
{
  BENCHMARK("lexer construction and lex")
  {
    Lexer lexer{name_path_query_fragment};
    lexer.lex();
  };
}

TEST_CASE("should lex as static", "[lex][static]")
{
  auto result = Lexer::lex(name_path_fragment);

  CHECK(result.scheme == "https");
  CHECK(result.authority == "spjuanjoc.github.io");
  CHECK(result.path == "/avanzado/fechas-formato-estandar/");
  CHECK(result.fragment == "usando-la-biblioteca-fmt");
}
