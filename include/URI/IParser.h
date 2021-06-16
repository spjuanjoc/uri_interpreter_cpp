/**
 * @brief Declaration of the interface that analyses grammatically the URI components.
 *
 * @author  juan.castellanos
 * @date    2021-06-09
 */

/* 2.2. Interface: Parser */

#ifndef URII_IPARSER_H
#define URII_IPARSER_H

#include <string>

namespace urii
{
/**
 *
 */
class IParseStrategy
{
public:
  IParseStrategy() = default;
  virtual ~IParseStrategy() = default;

  // Rule of five for special members.
  IParseStrategy(const IParseStrategy&) = default;
  IParseStrategy(IParseStrategy&&) = default;
  IParseStrategy& operator=(const IParseStrategy&) = default;
  IParseStrategy& operator=(IParseStrategy&&) = default;

  virtual void parse(const std::string& uri) = 0;
};

}  // namespace urii

#endif /* URII_IPARSER_H */
