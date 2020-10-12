//
// Created by juan.castellanos on 3/10/20.
//
#include "URI/IParser.hpp"
//#include "URI/IValidator.hpp"
//#include "URI/URI.hpp"
#include <gtest/gtest.h>

//using namespace URI;

class MockIParser : public IParseStrategy
{

};

class URIFixture : public testing::Test
{};

/*
mailto:John.Doe@example.com
└─┬──┘ └────┬─────────────┘
scheme     path
*/
auto uri2CompsNoHost = "mailto:John.Doe@example.com";

/*
tel:+1-816-555-1212
└┬┘ └──────┬──────┘
scheme    path
*/
auto uri2CompsNoHost2 = "tel:+1-816-555-1212";

/*
  urn:oasis:names:specification:docbook:dtd:xml:4.1.2
└┬┘ └──────────────────────┬──────────────────────┘
scheme                    path
 */
auto uri2CompsNoHost3 = "urn:oasis:names:specification:docbook:dtd:xml:4.1.2";

/*
news:comp.infosystems.www.servers.unix
└┬─┘ └─────────────┬─────────────────┘
scheme            path
*/
auto uri2CompsHostRegName = "news:comp.infosystems.www.servers.unix";

/*
telnet://192.0.2.16:80/
└─┬──┘   └─────┬─────┘│
scheme     authority  path
*/
auto uri3CompsV4 = "telnet://192.0.2.16:80/";

/*
  ldap://[2001:db8::7]/c=GB?objectClass?one
└┬─┘   └─────┬─────┘└─┬─┘ └──────┬──────┘
scheme   authority   path      query
*/
auto uri4compsV6 = "ldap://[2001:db8::7]/c=GB?objectClass?one";

/*
userinfo       host      port
┌──┴───┐ ┌──────┴──────┐ ┌┴┐
https://john.doe@www.example.com:123/forum/questions/?tag=networking&order=newest#top
└─┬─┘   └───────────┬──────────────┘└───────┬───────┘ └───────────┬─────────────┘ └┬┘
scheme          authority                  path                 query           fragment
*/
auto uri5compsRegName = "https://john.doe@www.example.com:123/forum/questions/?tag=networking&order=newest#top";

TEST_F(URIFixture, TwoComponentsNohost)
{

}

TEST_F(URIFixture, IParserTest)
{
  std::string fullValidUri{"https://sitechecker.pro:8080/knowledge-base/path?name=article&topic=seo#top"};
  std::string schemeAndPath{"mailto:John.Doe@example.com"};
  Resource uri{fullValidUri};

  EXPECT_STREQ(uri.uri.c_str(), fullValidUri.c_str());

  auto tokens = lex(fullValidUri);
//  validate is v4?
  EXPECT_TRUE(uri.validate(Host::IPv4));
  EXPECT_STREQ(uri.getComponent(Component::scheme).c_str(), "https");
}