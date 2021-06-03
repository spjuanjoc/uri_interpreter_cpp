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
      Lexer lexer;
      m_components = lexer.lex(m_uri);

      switch (host)
      {
        case Host::IPv4:
          //        components_.authority.host is IPv4?
          result = true;
          //       1. lex();
          //       2. parse();
          break;
        case Host::IPv6:
          // IPv6
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

  std::string get(Component component) override
  {
    std::string result;

    switch (component)
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

}  // namespace urii