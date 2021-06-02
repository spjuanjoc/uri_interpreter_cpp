#include <iostream>
#include "URI/Lexer.h"

using namespace urii;

int main() {
  std::cout << "Hello conan\n";
//  Resource uri;
  Resource uri{"mailto:John.Doe@example.com"};

  uri.validate();
  std::cout << uri.get(Component::scheme).c_str() << '\n';
  std::cout << uri.get(Component::path).c_str() << '\n';
}
