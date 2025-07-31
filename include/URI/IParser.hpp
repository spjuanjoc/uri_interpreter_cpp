/**
 * @brief Declaration of the interface that analyses grammatically the URI components.
 *
 * @author  spjuanjoc
 * @date    2021-06-09
 */

/* 2.2. Interface: Parser */

#ifndef UIN_IPARSER_H
#define UIN_IPARSER_H

#include <string>

namespace uin
{

/**
 *
 */
class IParseStrategy
{
public:
  IParseStrategy()          = default;
  virtual ~IParseStrategy() = default;

  IParseStrategy(const IParseStrategy&)            = default;
  IParseStrategy(IParseStrategy&&)                 = default;
  IParseStrategy& operator=(const IParseStrategy&) = default;
  IParseStrategy& operator=(IParseStrategy&&)      = default;

  virtual void parse(const std::string& uri) = 0;
};

}  // namespace uin

#endif /* UIN_IPARSER_H */
