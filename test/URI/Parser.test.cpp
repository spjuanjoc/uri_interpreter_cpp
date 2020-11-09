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
auto uri2SchemePath = "mailto:John.Doe@example.com";

/*
tel:+1-816-555-1212
└┬┘ └──────┬──────┘
scheme    path
*/
auto uri2SchemePath2 = "tel:+1-816-555-1212";

/*
urn:oasis:names:specification:docbook:dtd:xml:4.1.2
└┬┘ └──────────────────────┬──────────────────────┘
scheme                    path
 */
auto uri2SchemePath3 = "urn:oasis:names:specification:docbook:dtd:xml:4.1.2";

/*
news:comp.infosystems.www.servers.unix
└┬─┘ └─────────────┬─────────────────┘
scheme            path
*/
auto uri2SchemePath4 = "news:comp.infosystems.www.servers.unix";

/*
telnet://192.0.2.16:80/
└─┬──┘   └─────┬─────┘│
scheme     authority  path
*/
auto uri3SchemeAuthV4Path = "telnet://192.0.2.16:80/";
auto uri3SchemeAuthV4Path2 = "telnet://192.0.2.16:80/path";

/*
ldap://[2001:db8::7]/c=GB?objectClass?one
└┬─┘   └─────┬─────┘└─┬─┘ └──────┬──────┘
scheme   authority   path      query
*/
auto uri4SchemeAuthV6PathQuery = "ldap://[2001:db8::7]/c=GB?objectClass?one";

/*
          userinfo       host      port
          ┌──┴───┐ ┌──────┴──────┐ ┌┴┐
  https://john.doe@www.example.com:123/forum/questions/?tag=networking&order=newest#top
  └─┬─┘   └───────────┬──────────────┘└───────┬───────┘ └───────────┬─────────────┘ └┬┘
  scheme          authority                  path                 query           fragment
 */
auto uri5SchemeAuthRNPathQueryFrag{"https://john.doe@example.com:123/forum/questions/?tag=networking&order=newest#top"};
auto uri5SchemeAuthRNPathQueryFrag2{"https://sitechecker.pro:8080/knowledge-base/path?name=article&topic=seo#top"};

TEST_F(URIFixture, lexSchemeAndPathOnly)
{
  auto tokens = lex(uri2SchemePath);
}

/**
 * The happy path with IPv4
 */
TEST_F(URIFixture, lexSchemeAuthorityAndPath_IPv4)
{
  auto tokens = lex(uri3SchemeAuthV4Path2);
}

TEST_F(URIFixture, validate5CompsHostv4)
{
  Resource uri{uri5SchemeAuthRNPathQueryFrag};

  EXPECT_TRUE(uri.validate(Host::IPv4));
  EXPECT_STREQ(uri.getComponent(Component::scheme).c_str(), "https");
}

TEST_F(URIFixture, validSchemeAndPath)
{
  std::string schemeAndPath{"mailto:John.Doe@example.com"};
  Resource uri{schemeAndPath};

  EXPECT_TRUE(uri.validate(Host::IPv4));
  EXPECT_STREQ(uri.getComponent(Component::scheme).c_str(), "mailto");
}