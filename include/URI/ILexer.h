/**
 * Created by juan.castellanos on 10/11/20.
*/

#pragma once

#include <string_view>

namespace urii
{
struct Components;

class ILexer
{
public:
  ILexer()              = default;
  ~ILexer()             = default;
  ILexer(const ILexer&) = default;
  ILexer(ILexer&&)      = default;
  ILexer& operator=(const ILexer&) = default;
  ILexer& operator=(ILexer&&) = default;

private:
  virtual Components lex()                    = 0;
  virtual void       setUri(std::string_view) = 0;
};

}  // namespace urii
