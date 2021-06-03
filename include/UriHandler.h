#pragma once

#include <string>


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


// interface

// implementation
//uri validator strategies
// st1 IPv4
// st2 IPv6
// st2 RegName

// usage

namespace urii
{

/**
 * Host types: IPv4, IPv6, Registered Name.
 */
enum class HostType : std::uint32_t
{
  Unknown = 0, /**< 0 */
  IPv4    = 1, /**< 1 */
  IPv6    = 2, /**< 2 */
  RegName = 3  /**< 3 */
};

/**
 *
 */
class UriHandler
{
public:
  UriHandler() = default;
  /**
   * Parses the URI with scheme and authority as mandatory
   * @param uri
   */
  explicit UriHandler(std::string uri);

  bool        hasPort() const;
  bool        isValidUri() const;
  std::string getAuthority() const;
  std::string getFragment() const;
  std::string getHost() const;
  std::string getPath() const;
  std::string getPort() const;
  std::string getQuery() const;
  std::string getScheme() const;
  std::string getUserInfo() const;

private:
  /**
   * Analyses the grammar of the URI's authority
   *
   * @param authority string with <userinfo@>host<:port>
   */
  void parseAuthority(const std::string& authority);

  /**
   * Analyses the grammar of the complete URI by dividing it into
   *         scheme, authority, path (optional), query, and fragment.
   *
   * @param uri The resource information.
   * @throws logic_error if the URI is not at least scheme://authority
   */
  void parseUri(const std::string& uri);

  // Optional
  static bool        isValidHextet(const std::string& hextet);
  static bool        isValidIPv4(const std::string& host);
  static bool        isValidIPv6(const std::string& host);
  static bool        isValidRegName(const std::string& host);
  static std::string cropIPv6(const std::string& ip);
  void               parsePort(const std::string& port, const unsigned& position);
  void               parseUserInfo();
  void               parsePath();


  bool m_has_port{false};
  bool m_is_valid_uri{false};

  std::string m_uri;
  std::string m_scheme;
  std::string m_authority;
  std::string m_path;
  std::string m_query;
  std::string m_fragment;

  struct authority
  {
    std::string m_user_info;
    std::string m_host;  // @remark IPv4 must be in dot-decimal notation, IPv6 must be enclosed in brackets [].
    std::string m_port;
  } m_full_authority;

  HostType m_host_type{HostType::Unknown};
};

}  // namespace urii
