//
// Created by juan.castellanos on 10/11/20.
//
#pragma once

#include "IResource.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <sstream>
#include <utility>
#include <vector>

namespace urii
{
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
  std::string fullAuthority;
  std::string path;
  std::string query;
  std::string fragment;
  Authority   authority;
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
 * 3. Implementation
 */
class HostParser;
Components lex(const std::string& input);

class Resource : public IResource
{
private:
  std::string                uri_;
  std::optional<HostParser*> v4;
  Components                 components_;

public:
  Resource()                = default;
  Resource(const Resource&) = default;
  Resource& operator=(const Resource&) = default;
  Resource(Resource&&)                 = default;
  Resource& operator=(Resource&&) = default;
  ~Resource() override            = default;

  explicit Resource(std::string uri) : uri_(std::move(uri)) {}

  bool validate() { return validate(Host::Unknown); }

  bool validate(Host host) override
  {
    bool result = false;

    if (!uri_.empty())
    {
      components_ = lex(uri_);

      switch (host)
      {
        case Host::IPv4:
          //        components_.authority.host is IPv4?
          result = true;
          //       1. lex();
          //       2. parse();
          break;
        case Host::IPv6:
          break;
        case Host::RegName:
          result = true;
          break;
        case Host::Unknown:
        default:
          result = true;
          //parse all?
          break;
      }
    }
    return result;
  }

  void set(const std::string& uri) { uri_ = uri; }

  std::string get(Component c) override
  {
    std::string result;

    switch (c)
    {
      case Component::scheme:
        result = components_.scheme;
        break;
      case Component::path:
        result = components_.path;
        break;
      case Component::query:
        result = components_.query;
        break;
      case Component::fragment:
        result = components_.fragment;
        break;
      case Component::authority:
        result = components_.fullAuthority;
        break;
        // get host, username, port
    }

    return result;
  }
};

class IParseStrategy
{
public:
  virtual void parse(std::string&){};
};

class HostParser : public IParseStrategy
{
public:
  void parse(std::string& string) override {}
};

class v4IP : public HostParser
{
public:
  void parse(std::string& string) override { HostParser::parse(string); }
};

class DynamicHostParser
{
private:
  std::ostringstream              oss;
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

}