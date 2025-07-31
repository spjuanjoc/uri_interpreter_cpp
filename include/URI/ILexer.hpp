/**
 * @brief Declaration of the interface for separation of components by tokens.
 *
 * @author  spjuanjoc
 * @date    2020-11-10
 */

/* 2.1. Interface: Lexer */

#ifndef UIN_ILEXER_H
#define UIN_ILEXER_H

#include <string_view>

namespace uin
{

struct Components;

/**
 * @brief Interface that represents the means of separation by tokens.
 */
class ILexer
{
public:
  ILexer()          = default;
  virtual ~ILexer() = default;

  ILexer(const ILexer&)            = default;
  ILexer(ILexer&&)                 = default;
  ILexer& operator=(const ILexer&) = default;
  ILexer& operator=(ILexer&&)      = default;

private:
  virtual Components lex()                    = 0;
  virtual void       setUri(std::string_view) = 0;
};

}  // namespace uin

#endif /* UIN_ILEXER_H */
