//
// Created by juan.castellanos on 3/10/20.
//
#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
//
//namespace URI
//{
//
//class IParser
//{
//  virtual std::string authority() = 0;
//  virtual std::string minimal() = 0;
//  virtual std::string port() = 0;
//  virtual std::string user() = 0;
//  virtual std::string path() = 0;
//
//};
//}

struct Authority
{
  std::string host;
  std::string userinfo;
  std::string port;
};

struct Components
{
  std::string scheme;
  std::string path;
  std::string query;
  std::string fragment;
  Authority authority;
};

enum class Host : std::uint32_t
{
  Unknown = 0, /**< 0 */
  IPv4    = 1, /**< 1 */
  IPv6    = 2, /**< 2 */
  RegName = 3  /**< 3 */
};

enum class Component : std::uint32_t
{
  scheme    = 0, /**< 0 */
  path      = 1, /**< 1 */
  query     = 2, /**< 2 */
  fragment  = 3, /**< 3 */
  authority = 4  /**< 4 */
};

class IResource
{
public:
  virtual ~IResource() = default;

  virtual bool validate(Host) = 0;
  virtual std::string getComponent(Component) = 0;
};

class IPv4Parser;

class Resource : public IResource
{
public:
  std::string uri;
  IPv4Parser* v4;

public:
  explicit Resource(std::string  uri) : uri(std::move(uri))
  {
  }

  ~Resource() override = default;

  bool validate(Host host) override
  {
    bool result = false;

    switch (host)
    {
      case Host::Unknown:
        break;
      case Host::IPv4:
        result = true;
//        lex();
//        parse();
        break;
      case Host::IPv6:
        break;
      case Host::RegName:
        break;
    }

    return result;
  }

  std::string getComponent(Component) override
  {
    return std::__cxx11::string();
  }
};

class IParseStrategy
{
public:
  virtual void parse(std::string& ) ;
};

class IPv4Parser : IParseStrategy
{
  void parse(std::string& string) override
  {

  }
};

class DynamicHostParser
{
private:
  std::ostringstream oss;
  std::unique_ptr<IParseStrategy> parseStrategy;

public:
  void setHostType(const Host& hostType)
  {
    switch (hostType)
    {
      case Host::Unknown:
        std::cout << "Unknown\n";
        break;
      case Host::IPv4:
//        parseStrategy = std::make_unique<IPv4Parser>();
        std::cout << "IPv4\n";
        break;
      case Host::IPv6:
        std::cout << "IPv6\n";
        break;
      case Host::RegName:
        std::cout << "Registered Name\n";
        break;
    }
  }

  void clear()
  {
    oss.str("");
    oss.clear();
  }

  std::string str() const { return oss.str(); }
};

std::vector<Components> lex(const std::string& input)
{
  std::string prepare{input};
  std::replace_if(
    std::begin(prepare),
    std::end(prepare),[](const char c) { return c == '/'; }, ' ');

  std::istringstream iss{prepare};
  std::vector<std::string> components{std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>{}};

  switch (components.size()) {
    case 1:
      break;
    // scheme .at(0)
    // path ? .at(1)
    // authority .at(0)
  }
  for (const auto& it: components)
  {
    std::cout << it << ' ';
  }

  return {};
}
/**
Plan:

 1. Components
  scheme      mandatory
  path        mandatory
  authority
    host
    userinfo
    port
  query
  fragment

 2. Interface
    IResource
       Validate(host type: v4, v6, RN)
        - validate mandatory components
        - validate host sub component
        - then validate the rest
       GetComponent(component)

 3. Implementation
    Resource
      validate -> Dynamic Strategy
          Dynamic host parser
            Interface IParser
              IPv6Parser
              IPv4Parser
              RNParser
      get

 4. Usage
    lexer
    parser
      The dynamic strategy usage class

 5. resolver?
    what to do with the parsed data
    auto parsed = parse("URI");
    parsed->validate(Host::IPv6);
    parsed->Get(Component::scheme)

 */
