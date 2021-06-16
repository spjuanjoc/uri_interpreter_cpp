/**
 * @brief Declaration of the interface for separation of components by tokens.
 *
 * @author  juan.castellanos
 * @date    2020-11-10
 */

/* 2.1. Interface: Lexer */

#ifndef URII_ILEXER_H
#define URII_ILEXER_H

#include <string_view>

namespace urii
{
// Forward declarations
struct Components;

/**
 * @brief Interface that represents the means of separation by tokens.
 */
class ILexer
{
public:
  ILexer()              = default;
  virtual ~ILexer()     = default;

  // Rule of five for special members.
  ILexer(const ILexer&) = default;
  ILexer(ILexer&&)      = default;
  ILexer& operator=(const ILexer&) = default;
  ILexer& operator=(ILexer&&) = default;

private:
  virtual Components lex()                    = 0;
  virtual void       setUri(std::string_view) = 0;
};

}  // namespace urii

#endif /* URII_ILEXER_H */
