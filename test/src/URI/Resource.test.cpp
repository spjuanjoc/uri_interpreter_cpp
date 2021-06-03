//
// Created by juan.castellanos on 3/10/20.
//

#include "URI/Resource.h"
#include "URI/Parser.h"
#include "UriExamples.h"
//#include "uri_examples.h"
//#include <gtest/gtest.h>
#include "catch2/catch.hpp"
#include "fmt/core.h"

using namespace urii;

//class MockIParser : public IParseStrategy
//{
//};

//class URIFixture : public testing::Test
//{
//};

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

TEST_CASE("should validate scheme and path ", "[case1]")
{
  Resource uri{scheme_path_mailto};

  CHECK(uri.validate() == true);
  CHECK(uri.get(Component::scheme) == "mailto");
  CHECK(uri.get(Component::path) == "John.Doe@example.com");
}

TEST_CASE("should validate scheme and path 2", "[case1]")
{
  Resource uri{scheme_path_tel};

  CHECK(uri.validate());
  CHECK(uri.get(Component::scheme) == "tel");
  CHECK(uri.get(Component::path) == "+1-816-555-1212");
}
//
//TEST_F(URIFixture, Case1ValidSchemeAndPath3)
//{
//  Resource uri{uri2SchemePath3};
//
//  EXPECT_TRUE(uri.validate());
//  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "urn");
//  EXPECT_STREQ(uri.get(Component::path).c_str(), "oasis:names:specification:docbook:dtd:xml:4.1.2");
//}
//
//TEST_F(URIFixture, Case1ValidSchemeAndPath4)
//{
//  Resource uri{uri2SchemePath4};
//
//  EXPECT_TRUE(uri.validate());
//  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "news");
//  EXPECT_STREQ(uri.get(Component::path).c_str(), "comp.infosystems.www.servers.unix");
//}
//
//TEST_F(URIFixture, Case2ValidSchemeAndAuthorityV4)
//{
//  Resource uri{uri3SchemeAuthV4};
//
//  EXPECT_TRUE(uri.validate());
//  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "telnet");
//  EXPECT_STREQ(uri.get(Component::authority).c_str(), "192.0.2.16:80");
//}
//
//TEST_F(URIFixture, Case3ValidSchemeAuthV4Path)
//{
//  Resource uri{uri3SchemeAuthV4Path};
//
//  EXPECT_TRUE(uri.validate());
//  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "telnet");
//  EXPECT_STREQ(uri.get(Component::authority).c_str(), "192.0.2.16:80");
//  EXPECT_STREQ(uri.get(Component::path).c_str(), "path");
//}
//
//TEST_F(URIFixture, Case3ValidSchemeAuthV6PathQuery)
//{
//  Resource uri{uri4SchemeAuthV6PathQuery};
//
//  EXPECT_TRUE(uri.validate());
//  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "ldap");
//  EXPECT_STREQ(uri.get(Component::authority).c_str(), "[2001:db8::7]");
//  EXPECT_STREQ(uri.get(Component::path).c_str(), "c=GB?objectClass?one");
//}
//
//TEST_F(URIFixture, Case4Valid5CompsHostRN)
//{
//  Resource uri{uri5SchemeAuthRNPathQueryFrag};
//
//  EXPECT_TRUE(uri.validate(Host::RegName));
//  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "https");
//  EXPECT_STREQ(uri.get(Component::authority).c_str(), "john.doe@example.com:123");
//  EXPECT_STREQ(uri.get(Component::path).c_str(), "/forum/questions/?tag=networking&order=newest#top");
//}
//
//TEST_F(URIFixture, LazyCase4Valid5CompsHostRN)
//{
//  Resource uri;
//
//  uri.set(uri5SchemeAuthRNPathQueryFrag);
//
//  EXPECT_TRUE(uri.validate(Host::Unknown));
//  EXPECT_STREQ(uri.get(Component::scheme).c_str(), "https");
//  EXPECT_STREQ(uri.get(Component::authority).c_str(), "john.doe@example.com:123");
//  EXPECT_STREQ(uri.get(Component::path).c_str(), "/forum/questions/?tag=networking&order=newest#top");
//}
