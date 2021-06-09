/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2020-11-10
 */

#ifndef URII_ILEXER_H
#define URII_ILEXER_H

#include <string_view>

namespace urii
{
struct Components;

class ILexer
{
public:
  ILexer()              = default;
  virtual ~ILexer()     = default;
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
