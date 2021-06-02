//
// Created by juan.castellanos on 10/11/20.
//
#pragma once

#include "Components.h"
#include "IResource.h"
#include "Lexer.h"
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
 * 3. Implementation
 */
class HostParser;
class Lexer;
//Components lex(const std::string& uri);

/**
 *
 */
class Resource : public IResource
{
public:
  Resource()                = default;
  Resource(const Resource&) = default;
  Resource& operator=(const Resource&) = default;
  Resource(Resource&&)                 = default;
  Resource& operator=(Resource&&) = default;
  ~Resource() override            = default;

  explicit Resource(std::string uri) : m_uri(std::move(uri)) {}

  bool validate() { return validate(Host::Unknown); }

  bool validate(Host host) override
  {
    bool result = false;

    if (!m_uri.empty())
    {
      Lexer l;
      m_components = l.lex(m_uri);

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

  void set(const std::string& uri) { m_uri = uri; }

  std::string get(Component c) override
  {
    std::string result;

    switch (c)
    {
      case Component::scheme:
        result = m_components.scheme;
        break;
      case Component::path:
        result = m_components.path;
        break;
      case Component::query:
        result = m_components.query;
        break;
      case Component::fragment:
        result = m_components.fragment;
        break;
      case Component::authority:
        result = m_components.authority;
        break;
        // get host, username, port
    }

    return result;
  }

private:
  std::string                m_uri;
  std::optional<HostParser*> m_v4;
  Components                 m_components;
};

/**
 *
 */
class IParseStrategy
{
public:
  virtual void parse(std::string&){};
};

/**
 *
 */
class HostParser : public IParseStrategy
{
public:
  void parse(std::string& string) override {}
};

/**
 *
 */
class v4IP : public HostParser
{
public:
  void parse(std::string& string) override { HostParser::parse(string); }
};

/**
 *
 */
class DynamicHostParser
{
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
    m_oss.str("");
    m_oss.clear();
  }

  std::string str() const { return m_oss.str(); }

private:
  std::ostringstream              m_oss;
  std::unique_ptr<IParseStrategy> m_parse_strategy;
};

}  // namespace urii