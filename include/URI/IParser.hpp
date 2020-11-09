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

/**
 * 1. Components
 */
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

/**
 * 2. Interface
 */
class IResource
{
public:
  virtual ~IResource() = default;

  virtual bool validate(Host) = 0;
  virtual std::string getComponent(Component) = 0;
};


/**
 * 3. Implementation
 */
class HostParser;
Components lex(const std::string& input);

class Resource : public IResource
{
public:
  std::string             uri_;
  HostParser* v4;
  Components components_;

public:
  explicit Resource(std::string  uri) : uri_(std::move(uri))
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
        components_ = lex(uri_);
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

  std::string getComponent(Component c) override
  {
    std::string result;

    switch (c)
    {
      case Component::scheme:
        result = components_.scheme;
        break;
      case Component::path:
        break;
      case Component::query:
        break;
      case Component::fragment:
        break;
      case Component::authority:
        break;
    }

    return result;
  }
};

class IParseStrategy
{
public:
  virtual void parse(std::string& ) {};
};

class HostParser : public IParseStrategy
{
public:
  void parse(std::string& string) override
  {

  }
};

class v4IP : public HostParser
{
public:
  void parse(std::string& string) override
  {
    HostParser::parse(string);
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

/**
 * 4. Usage - lex
 */
Components case1(const std::string& uri);
void case2(const std::vector<std::string>& uri);
void case3(const std::vector<std::string>& uri);
Components case4(const std::vector<std::string>& uri);

Components lex(const std::string& input)
{
  Components result;
  std::string slashLex{input};

  std::replace_if(
    std::begin(slashLex),
    std::end(slashLex),
    [](const char c) { return c == '/'; },
    ' ');

  std::istringstream iss{slashLex};
  std::vector<std::string> components{std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>{}};

  switch (components.size()) {
    case 1:
      std::cout << "case 1\n";
      result = case1(components.at(0));
      break;
    case 2:
      std::cout << "case 2\n";
      case2(components);
      break;
    case 3:
      std::cout << "case 3\n";
      case3(components);
      break;
    default:
      std::cout << "case 4+\n";
      result = case4(components);
      break;
  }

  for (const auto& it: components)
  {
    std::cout << it << ' ';
  }

  return result;
}

/*
 * seek first ':'
 * scheme + path = minimal URI
 */
Components case1(const std::string& uri)
{
  Components result{};
  auto schemeAndPath{uri};

  std::replace_if(
    std::begin(schemeAndPath),
    std::end(schemeAndPath),
    [](const char c) { return c == ':'; },
    ' ');

  std::istringstream iss{schemeAndPath};
  std::vector<std::string> components{std::istream_iterator<std::string>{iss},
                                      std::istream_iterator<std::string>{}};

  switch (components.size()) {
    case 1:
      std::cout << "only scheme\n";
      result.scheme = components.at(0);
      break;
    case 2:
    default:
      std::cout << "scheme and authority\n";
      result.scheme = components.at(0);
      result.authority.host = components.at(1);
      break;
  }

  // now they can be parsed
  std::cout << "lex completed\n";
  return result;
}

/*
 * scheme .at(0)
 * authority .at(1)
 */
void case2(const std::vector<std::string>& uri)
{
  auto scheme = uri.at(0);
  auto authority = uri.at(1);
  // now they can be parsed
  std::cout << "Scheme: " << scheme << '\n';
  std::cout << "Authority: " << authority << '\n';
  std::cout << "lex completed\n";
}

/*
 * scheme .at(0)
 * authority .at(1)
 * path?query#fragment .at(2)
 */
void case3(const std::vector<std::string>& uri)
{
  auto scheme = uri.at(0);
  auto authority = uri.at(1);
  auto path      = uri.at(2);
  // now they can be parsed
  std::cout << "Scheme: " << scheme << '\n';
  std::cout << "Authority: " << authority << '\n';
  std::cout << "Path+: " << path << '\n';
  std::cout << "lex completed\n";
}

/*
 *
 * more than 3 means it has/multi/path/
 * take first 2, and join from 3+
 *
 * scheme .at(0)
 * authority .at(1)
 * path?query#fragment .at(2)
 */
Components case4(const std::vector<std::string>& uri)
{
  Components result;

  result.scheme         = uri.at(0);
  result.authority.host = uri.at(1);
  result.path           = uri.at(2);  // concat from 2+

  result.scheme.erase(std::remove_if(std::begin(result.scheme),
                              std::end(result.scheme),
                              [](char c) { return c == ':'; }),
               std::end(result.scheme));

  // now they can be parsed
  std::cout << "Scheme: " << result.scheme << '\n';
  std::cout << "Authority: " << result.authority.host << '\n';
  std::cout << "Path+: " << result.path << '\n';
  std::cout << "lex completed\n";

  return result;
}

/**
 * 4. Usage - parser
 */
//...

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
