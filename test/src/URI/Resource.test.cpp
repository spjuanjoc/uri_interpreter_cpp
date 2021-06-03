#include "URI/Resource.h"
#include "catch2/catch.hpp"
#include "URI/Parser.h"
#include "UriExamples.h"

using namespace urii;

class ResourceFixture
{
public:
  Resource uri;
};

TEST_CASE_METHOD(ResourceFixture,"should validate scheme and path ", "[case1]")
{
  uri.set(scheme_path_mailto);

  CHECK(uri.validate() == true);
  CHECK(uri.get(Component::scheme) == "mailto");
  CHECK(uri.get(Component::path) == "John.Doe@example.com");
}

TEST_CASE_METHOD(ResourceFixture, "should validate scheme and path 2", "[case1]")
{
  uri.set(scheme_path_tel);

  CHECK(uri.validate());
  CHECK(uri.get(Component::scheme) == "tel");
  CHECK(uri.get(Component::path) == "+1-816-555-1212");
}

TEST_CASE_METHOD(ResourceFixture, "should validate scheme and path 3", "[case1]")
{
  uri.set(scheme_path_urn);

  CHECK(uri.validate());
  CHECK(uri.get(Component::scheme) == "urn");
  CHECK(uri.get(Component::path) == "oasis:names:specification:docbook:dtd:xml:4.1.2");
}

TEST_CASE_METHOD(ResourceFixture, "should validate scheme and path 4", "[case1]")
{
  uri.set(scheme_path_news);

  CHECK(uri.validate());
  CHECK(uri.get(Component::scheme) == "news");
  CHECK(uri.get(Component::path) == "comp.infosystems.www.servers.unix");
}

TEST_CASE_METHOD(ResourceFixture, "should validate authority IPv4", "[case2]")
{
  uri.set(scheme_authorityIPv4);

  CHECK(uri.validate());
  CHECK(uri.get(Component::scheme) == "telnet");
  CHECK(uri.get(Component::authority) == "192.0.2.16:80");
}

TEST_CASE_METHOD(ResourceFixture, "should validate authority IPv4, and path", "[case3]")
{
  uri.set(scheme_authorityIPv4_path);

  CHECK(uri.validate());
  CHECK(uri.get(Component::scheme) == "telnet");
  CHECK(uri.get(Component::authority) == "192.0.2.17:80");
  CHECK(uri.get(Component::path) == "path");
}

TEST_CASE_METHOD(ResourceFixture, "should validate authority IPv6, path, and query", "[case3]")
{
  uri.set(scheme_authorityIPv6_path_query);

  CHECK(uri.validate());
  CHECK(uri.get(Component::scheme) == "ldap");
  CHECK(uri.get(Component::authority) == "[2001:db8::7]");
  CHECK(uri.get(Component::path) == "c=GB?objectClass?one");
}

TEST_CASE_METHOD(ResourceFixture, "should validate full URI", "[case4]")
{
  uri.set(registeredname_path_query_fragment);

  CHECK(uri.validate(Host::RegName));
  CHECK(uri.get(Component::scheme) == "https");
  CHECK(uri.get(Component::authority) == "john.doe@example.com:123");
  CHECK(uri.get(Component::path) == "/forum/questions/?tag=networking&order=newest#top");
}

TEST_CASE("should validate full URI from constructor", "[case4]")
{
  Resource uri{registeredname_path_query_fragment_2};

  CHECK(uri.validate(Host::Unknown));
  CHECK(uri.get(Component::scheme) == "https");
  CHECK(uri.get(Component::authority) == "sitechecker.pro:8080");
  CHECK(uri.get(Component::path) == "/knowledge-base/path?name=article&topic=seo#top");
}
