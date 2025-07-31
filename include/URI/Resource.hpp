/**
 * @brief Declaration of the class that analyses grammatically the URI components.
 *
 * @author  spjuanjoc
 * @date    2020-11-10
 */

/* 3. Implementation */

#ifndef UIN_RESOURCE_H
#define UIN_RESOURCE_H

#include "Components.hpp"
#include "IResource.hpp"
#include "Lexer.hpp"

#include <algorithm>
// #include <iostream>
// #include <iterator>
#include <memory>
#include <optional>
// #include <sstream>
#include <utility>
// #include <vector>

namespace uin
{
// Forward declarations
class HostParser;
class Lexer;

/**
 *
 */
class Resource : virtual public IResource
{
public:
  Resource()           = default;
  ~Resource() override = default;

  // Rule of five for special members.
  Resource(const Resource&)            = default;
  Resource(Resource&&)                 = default;
  Resource& operator=(const Resource&) = default;
  Resource& operator=(Resource&&)      = default;

  /**
   * Constructs the resource with a string URI.
   *
   * @param uri The Uniform Resource Information.
   */
  explicit Resource(std::string uri)
  : m_uri(std::move(uri))
  {
  }

  /**
   * Assigns the URI.
   *
   * @param uri The Uniform Resource Information.
   */
  void set(const std::string& uri) { m_uri = uri; }

  /**
   * Retrieves a single component.
   *
   * @param component The name of the component to retrieve.
   * @return The resource component.
   */
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

  /**
   * Delegates an empty validation try.
   *
   * @return
   */
  bool validate() { return validate(Host::Unknown); }

  /**
   * Lexes and parses a host.
   *
   * @param host The type of host to validate
   * @return
   */
  bool validate(Host host) override
  {
    bool result = false;

    if (!m_uri.empty())
    {
      m_components = Lexer::lex(m_uri);

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
          // parse all?
          break;
      }
    }
    return result;
  }

private:
  std::string                m_uri;
  std::optional<HostParser*> m_v4;
  Components                 m_components;
};

}  // namespace uin

#endif /* UIN_RESOURCE_H */
