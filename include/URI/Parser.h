/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-06-02
 */

#ifndef URII_PARSER_H
#define URII_PARSER_H

#include <cstdio>

namespace urii
{
/**
 *
 */
class IParseStrategy
{
public:
  virtual void parse(const std::string& uri) = 0;
  virtual ~IParseStrategy() = default;
};

/**
 *
 */
class HostParser : public IParseStrategy
{
public:
  void parse(const std::string& uri) override { puts(uri.c_str()); }
};

/**
 *
 */
class v4IP : public HostParser
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

#endif /* URII_PARSER_H*/
