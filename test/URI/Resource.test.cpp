//
// Created by juan.castellanos on 3/10/20.
//

#include "URI/Resource.h"
#include <gtest/gtest.h>

using namespace urii;

class MockIParser : public IParseStrategy
{
};

class URIFixture : public testing::Test
{
};

/**
 *
 * mailto:John.Doe@example.com
 * └─┬──┘ └────┬─────────────┘
 * scheme     path
 */
constexpr auto uri2SchemePath = "mailto:John.Doe@example.com";

/**
 *
 * tel:+1-816-555-1212
 * └┬┘ └──────┬──────┘
 * scheme    path
*/
constexpr auto uri2SchemePath2 = "tel:+1-816-555-1212";

/**
 *
 * urn:oasis:names:specification:docbook:dtd:xml:4.1.2
 * └┬┘ └──────────────────────┬──────────────────────┘
 * scheme                    path
 */
constexpr auto uri2SchemePath3 = "urn:oasis:names:specification:docbook:dtd:xml:4.1.2";

/**
 *
 * news:comp.infosystems.www.servers.unix
 * └┬─┘ └─────────────┬─────────────────┘
 * scheme            path
*/
constexpr auto uri2SchemePath4 = "news:comp.infosystems.www.servers.unix";

/**
 *
 * telnet://192.0.2.16:80/
 * └─┬──┘   └─────┬─────┘│
 * scheme     authority  path
*/
constexpr auto uri3SchemeAuthV4     = "telnet://192.0.2.16:80/";
constexpr auto uri3SchemeAuthV4Path = "telnet://192.0.2.16:80/path";

/**
 *
 * ldap://[2001:db8::7]/c=GB?objectClass?one
 * └┬─┘   └─────┬─────┘└─┬─┘ └──────┬──────┘
 * scheme   authority   path      query
*/
constexpr auto uri4SchemeAuthV6PathQuery = "ldap://[2001:db8::7]/c=GB?objectClass?one";

/**
 *
 *           userinfo       host      port
 *          ┌──┴───┐ ┌──────┴──────┐ ┌┴┐
 *  https://john.doe@www.example.com:123/forum/questions/?tag=networking&order=newest#top
 *  └─┬─┘   └───────────┬──────────────┘└───────┬───────┘ └───────────┬─────────────┘ └┬┘
 *  scheme          authority                  path                 query           fragment
 */
constexpr auto uri5SchemeAuthRNPathQueryFrag{
  "https://john.doe@example.com:123/forum/questions/?tag=networking&order=newest#top"};
constexpr auto uri5SchemeAuthRNPathQueryFrag2{
  "https://sitechecker.pro:8080/knowledge-base/path?name=article&topic=seo#top"};

//
//TEST_F(URIFixture, lexSchemeAndPathOnly)
//{
//  auto tokens = lex(uri2SchemePath);
//}
//
///**
// * The happy path with IPv4
// */
//TEST_F(URIFixture, lexSchemeAuthorityAndPath_IPv4)
//{
//  auto tokens = lex(uri3SchemeAuthV4Path2);
//}

// ---

TEST_F(URIFixture, Case1ValidSchemeAndPath)
{
  Resource uri{uri2SchemePath};

  EXPECT_TRUE(uri.validate());
  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "mailto");
  EXPECT_STREQ(uri.get(Component::path).c_str(), "John.Doe@example.com");
}

TEST_F(URIFixture, Case1ValidSchemeAndPath2)
{
  Resource uri{uri2SchemePath2};

  EXPECT_TRUE(uri.validate());
  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "tel");
  EXPECT_STREQ(uri.get(Component::path).c_str(), "+1-816-555-1212");
}

TEST_F(URIFixture, Case1ValidSchemeAndPath3)
{
  Resource uri{uri2SchemePath3};

  EXPECT_TRUE(uri.validate());
  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "urn");
  EXPECT_STREQ(uri.get(Component::path).c_str(), "oasis:names:specification:docbook:dtd:xml:4.1.2");
}

TEST_F(URIFixture, Case1ValidSchemeAndPath4)
{
  Resource uri{uri2SchemePath4};

  EXPECT_TRUE(uri.validate());
  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "news");
  EXPECT_STREQ(uri.get(Component::path).c_str(), "comp.infosystems.www.servers.unix");
}

TEST_F(URIFixture, Case2ValidSchemeAndAuthorityV4)
{
  Resource uri{uri3SchemeAuthV4};

  EXPECT_TRUE(uri.validate());
  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "telnet");
  EXPECT_STREQ(uri.get(Component::authority).c_str(), "192.0.2.16:80");
}

TEST_F(URIFixture, Case3ValidSchemeAuthV4Path)
{
  Resource uri{uri3SchemeAuthV4Path};

  EXPECT_TRUE(uri.validate());
  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "telnet");
  EXPECT_STREQ(uri.get(Component::authority).c_str(), "192.0.2.16:80");
  EXPECT_STREQ(uri.get(Component::path).c_str(), "path");
}

TEST_F(URIFixture, Case3ValidSchemeAuthV6PathQuery)
{
  Resource uri{uri4SchemeAuthV6PathQuery};

  EXPECT_TRUE(uri.validate());
  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "ldap");
  EXPECT_STREQ(uri.get(Component::authority).c_str(), "[2001:db8::7]");
  EXPECT_STREQ(uri.get(Component::path).c_str(), "c=GB?objectClass?one");
}

TEST_F(URIFixture, Case4Valid5CompsHostRN)
{
  Resource uri{uri5SchemeAuthRNPathQueryFrag};

  EXPECT_TRUE(uri.validate(Host::RegName));
  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "https");
  EXPECT_STREQ(uri.get(Component::authority).c_str(), "john.doe@example.com:123");
  EXPECT_STREQ(uri.get(Component::path).c_str(), "/forum/questions/?tag=networking&order=newest#top");
}

TEST_F(URIFixture, LazyCase4Valid5CompsHostRN)
{
  Resource uri;

  uri.set(uri5SchemeAuthRNPathQueryFrag);

  EXPECT_TRUE(uri.validate(Host::Unknown));
  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "https");
  EXPECT_STREQ(uri.get(Component::authority).c_str(), "john.doe@example.com:123");
  EXPECT_STREQ(uri.get(Component::path).c_str(), "/forum/questions/?tag=networking&order=newest#top");
}
