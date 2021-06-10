/**
 * @brief Declaration of the class that analyses grammatically the URI components.
 *
 * @author  juan.castellanos
 * @date    2021-06-02
 */

/* 4.2. Usage: Parser */

#ifndef URII_PARSER_H
#define URII_PARSER_H

#include "IParser.h"
#include <cstdio> // todo remove this when puts() removed

namespace urii
{

/**
 *
 */
class HostParser : virtual public IParseStrategy
{
public:
  void parse(const std::string& uri) override { puts(uri.c_str()); }
};

/**
 *
 */
class IpV4Parser : virtual public HostParser
{
public:
  void parse(const std::string& uri) override { HostParser::parse(uri); }
};

/**
 *
 */
class IpV6Parser : virtual public HostParser
{
public:
  void parse(const std::string& uri) override { HostParser::parse(uri); }
};

/**
 *  Registered Name
 *
 */
class NameParser : virtual public HostParser
{
public:
  void parse(const std::string& uri) override { HostParser::parse(uri); }
};

/**
 *
 */
class DynamicHostParser
{
public:
  /**
   * Creates the strategy given a host type.
   *
   * @param hostType
   */
  void setHostType(const Host& hostType)
  {
    switch (hostType)
    {
      case Host::Unknown:
        std::cout << "Unknown\n";
        break;
      case Host::IPv4:
        m_parse_strategy = std::make_unique<IpV4Parser>();
        std::cout << "IPv4\n";
        break;
      case Host::IPv6:
        std::cout << "IPv6\n";
        m_parse_strategy = std::make_unique<IpV6Parser>();
        break;
      case Host::RegName:
        std::cout << "Registered Name\n";
        m_parse_strategy = std::make_unique<NameParser>();
        break;
    }
  }

  /**
   *
   */
  void clear()
  {
    m_oss.str("");
    m_oss.clear();
  }

  /**
   *
   * @return
   */
  std::string str() const { return m_oss.str(); }

private:
  std::ostringstream              m_oss;
  std::unique_ptr<IParseStrategy> m_parse_strategy;
};

}  // namespace urii

#endif /* URII_PARSER_H */
