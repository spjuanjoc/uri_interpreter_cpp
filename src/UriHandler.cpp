#include "UriHandler.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

using std::stringstream;
using std::uint32_t;
using std::vector;

const uint32_t MIN_PORT{0};
const uint32_t MAX_PORT{65535};

UriHandler::UriHandler(std::string uri) : m_uri{std::move(uri)}
{
  parseUri(m_uri);
}
bool UriHandler::HasPort() const
{
  return m_has_port;
}

bool UriHandler::IsValidUri() const
{
  return m_is_valid_URI;
}
bool UriHandler::isValidIPv4(const std::string& host)
{
  std::string sIP{host};
  std::replace_if(
    sIP.begin(),
    sIP.end(),
    [](const char c) { return c == '.'; },
    ' ');
  std::stringstream ss;
  ss << sIP;
  bool allDigits = true;
  while (!ss.eof())
  {
    std::string tmp;
    ss >> tmp;
    for (unsigned char c : tmp)
    {
      allDigits &= (isdigit(c) != 0);
    }
  }
  return allDigits;
}
bool UriHandler::isValidHexet(const std::string& hextet)
{
  std::stringstream ss;
  int               outHex = 0x0;
  ss << hextet;
  ss >> std::hex >> outHex;
  ss.str("");
  ss.clear();
  ss << outHex;
  return (ss.str() == hextet);
}
bool UriHandler::isValidIPv6(const std::string& host)
{
  const uint32_t MAX_NUM_OF_HEXETS = 8;
  bool           valid             = true;
  std::string         result            = cropIPv6(host);
  std::string         section{result};
  std::replace_if(
    section.begin(),
    section.end(),
    [](char c) { return c == ':'; },
    ' ');
  std::stringstream ss;
  ss << section;
  uint32_t counter = 0;

  while (!ss.eof())
  {
    std::string hexet;
    ss >> hexet;
    valid &= isValidHexet(hexet);
    ++counter;
  }

  if (counter > MAX_NUM_OF_HEXETS)
  {
    valid = false;
  }

  return valid;
}
bool UriHandler::isValidRegName(const std::string& host)
{
  return true;  /// \todo implement
}
std::string UriHandler::cropIPv6(const std::string& ip)
{
  std::string result{ip};
  auto   pos1 = result.find(']');

  if (pos1 != std::string::npos)
  {
    result = result.substr(0, pos1 + 1);
  }

  result.erase(std::remove_if(result.begin(),
                              result.end(),
                              [](char c) { return (c == '[' || c == ']'); }),
               result.end());
  auto pos = result.find('%');

  if (pos != std::string::npos)
  {
    result = result.substr(0, pos);
  }

  return result;
}
std::string UriHandler::GetAuthority() const
{
  return m_authority;
}
std::string UriHandler::GetFragment() const
{
  return m_fragment;
}
std::string UriHandler::GetHost() const
{
  return m_full_authority.m_host;
}
std::string UriHandler::GetPath() const
{
  return m_path;
}
std::string UriHandler::GetPort() const
{
  return m_full_authority.m_port;
}
std::string UriHandler::GetQuery() const
{
  return m_query;
}
std::string UriHandler::GetScheme() const
{
  return m_scheme;
}
std::string UriHandler::GetUserInfo() const
{
  return m_full_authority.m_user_info;
}
void UriHandler::parseAuthority(const std::string& authority)
{
  const auto& itIpVersion = authority.find(']');
  if (itIpVersion != std::string::npos)
  {
    std::string      port   = authority.substr(itIpVersion);
    const auto& itPort = port.find(':');
    if (itPort != std::string::npos)
    {
      m_has_port = true;
      parsePort(port, itPort);
    }
    if (isValidIPv6(authority))
    {
      m_host_type      = HostType::IPv6;
      m_is_valid_URI  = true;
      m_full_authority.m_host = authority.substr(0, itIpVersion + 1);
    }
    else
    {
      m_is_valid_URI = false;
      m_host_type    = HostType::Unknown;
    }
  }
  else
  {
    std::string      host   = authority;
    const auto& itPort = authority.find(':');

    if (itPort != std::string::npos)
    {
      std::string tempPort     = authority;
      tempPort            = tempPort.substr(itPort + 1);
      const auto& itValid = tempPort.find(':');
      if (itValid != std::string::npos)
      {
        m_is_valid_URI = false;
        return;
        //ipv6 with no []
      }
      m_has_port = true;
      host     = host.substr(0, itPort);
      parsePort(authority, itPort);
    }
    if (isValidIPv4(host))
    {
      m_host_type      = HostType::IPv4;
      m_is_valid_URI  = true;
      m_full_authority.m_host = host;
    }
    else if (isValidRegName(host))
    {
      m_host_type      = HostType::RegName;
      m_is_valid_URI  = true;
      m_full_authority.m_host = host;
    }
    else
    {
      m_is_valid_URI = false;
      m_host_type    = HostType::Unknown;
    }
  }
  parseUserInfo();
}
void UriHandler::parsePort(const std::string& port, const unsigned& position)
{
  m_full_authority.m_port = port.substr(position);
  m_full_authority.m_port.erase(std::remove_if(m_full_authority.m_port.begin(),
                                               m_full_authority.m_port.end(),
                                       [](unsigned char c) { return !isdigit(c); }),
                                m_full_authority.m_port.end());
  auto uPort = std::stoi(m_full_authority.m_port);

  // port range: 0 to 65535
  if (uPort < MIN_PORT || uPort > MAX_PORT)
  {
    m_full_authority.m_port = "";
    m_is_valid_URI  = false;
  }
}
void UriHandler::parseUserInfo()
{
  auto it = m_full_authority.m_host.find('@');
  if (it != std::string::npos)
  {
    m_full_authority.m_user_info = m_full_authority.m_host.substr(0, it);
    m_full_authority.m_host     = m_full_authority.m_host.substr(it + 1);
  }
}
void UriHandler::parseUri(const std::string& uri)
{
  std::string sUri{uri};
  std::replace_if(
    sUri.begin(),
    sUri.end(),
    [](const char c) { return c == '/'; },
    ' ');
  std::stringstream ss;
  ss << sUri;
  vector<std::string> uriVec;
  while (!ss.eof())
  {
    std::string tmp;
    ss >> tmp;
    uriVec.emplace_back(tmp);
  }
  size_t vecSize = uriVec.size();
  if (vecSize >= 2)
  {
    m_scheme = uriVec.at(0);
    m_scheme.erase(std::remove_if(m_scheme.begin(), m_scheme.end(),
                                 [](unsigned char c) { return !isalpha(c); }),
                   m_scheme.end());
    m_authority = uriVec.at(1);
    parseAuthority(m_authority);
  }
  if (vecSize >= 3)
  {
    auto itPath = uriVec.begin();
    std::advance(itPath, 2);
    for (auto it = itPath; it < uriVec.end(); ++it)
    {
      m_path.append("/");
      m_path.append(*it);
    }
    parsePath();
  }

  if (vecSize < 2)
  {
    m_is_valid_URI = false;
  }
}
void UriHandler::parsePath()
{
  std::string tmp = m_path;
  auto   it  = tmp.find('#');
  if (it != std::string::npos)
  {
    m_fragment = tmp.substr(it + 1);
    m_path    = tmp.substr(0, it);
  }
  auto it2 = m_path.find('?');
  if (it2 != std::string::npos)
  {
    m_query = m_path.substr(it2 + 1);
    m_path = tmp.substr(0, it2);
  }
}
