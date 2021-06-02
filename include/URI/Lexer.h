//
// Created by juan.castellanos on 10/11/20.
//
#pragma once

#include "Components.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace urii
{
/**
 * 4. Usage - lex
 */
class Lexer
{
public:
  Lexer() = default;

  /**
   * Performs the tokenization of a resource with '/' as separator
   *
   * @param uri The resource.
   * @return The tokens into a Components struct.
   */
  Components lex(const std::string& uri)
  {
    Components  result;
    std::string space_separated_uri{uri};

    std::replace_if(
      std::begin(space_separated_uri),
      std::end(space_separated_uri),
      [](const char c) { return c == '/'; },
      ' ');

    std::istringstream       iss{space_separated_uri};
    std::vector<std::string> components{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

    switch (components.size())
    {
      case 1:
        std::cout << "case 1: scheme + path \n";
        result = case1(components.at(0));
        break;
      case 2:
        std::cout << "case 2: scheme + authority\n";
        result = case2(components);
        break;
      case 3:
        std::cout << "case 3: single path\n";
        result = case3(components);
        break;
      default:
        std::cout << "case 4+: multi path\n";
        result = case4(components);
        break;
    }

    return result;
  }

private:
  /**
   * Processes the case when URI contains only scheme and path, it does not contain //
   * @param scheme_and_path
   * @return
   */
  Components case1(const std::string& scheme_and_path)
  {
    Components result{};

    const auto pos = scheme_and_path.find(':');

    if (pos != std::string::npos)
    {
      result.scheme = scheme_and_path.substr(0, pos);
      result.path   = scheme_and_path.substr(pos + 1);
    }

    // now they can be parsed
    std::cout << "lex completed\n";
    return result;
  }

  /**
   * Processes the case when URI contains at least scheme and authority
   * scheme .at(0)
   * authority .at(1)
   * @param uri
   * @return
   */
  Components case2(const std::vector<std::string>& uri)
  {
    Components result{};
    result.scheme    = uri.at(0);
    result.authority = uri.at(1);

    result.scheme.erase(std::remove_if(std::begin(result.scheme),
                                       std::end(result.scheme),
                                       [](char c) { return c == ':'; }),
                        std::end(result.scheme));

    // now they can be parsed
    std::cout << "Scheme: " << result.scheme << '\n';
    std::cout << "Authority: " << result.authority << '\n';
    std::cout << "lex completed\n";

    return result;
  }

  /**
   * Process the case when URI contains scheme + authority, and at least path with a single level
   *
   * scheme .at(0)
   * authority .at(1)
   * path?query#fragment .at(2) where path does not have more than one /
   * @param uri
   * @return
   */
  Components case3(const std::vector<std::string>& uri)
  {
    Components result{};

    result.scheme    = uri.at(0);
    result.authority = uri.at(1);
    result.path      = uri.at(2);

    result.scheme.erase(std::remove_if(std::begin(result.scheme),
                                       std::end(result.scheme),
                                       [](char c) { return c == ':'; }),
                        std::end(result.scheme));

    // now they can be parsed
    std::cout << "Scheme: " << result.scheme << '\n';
    std::cout << "Authority: " << result.authority << '\n';
    std::cout << "Path+: " << result.path << '\n';
    std::cout << "lex completed\n";

    return result;
  }

  /**
   * Processes the case when URI contains scheme + authority, and at least path with a multi level
   *
   * more than 3 means it has/multi/path/
   * take first 2, and join from 3+
   *
   * scheme .at(0)
   * authority .at(1)
   * path?query#fragment .at(2)
   *
   * @param uri
   * @return
   */
  Components case4(const std::vector<std::string>& uri)
  {
    Components result;

    result.scheme    = uri.at(0);
    result.authority = uri.at(1);
    result.path      = rejoin({std::begin(uri) + 2, std::end(uri)});

    result.scheme.erase(std::remove_if(std::begin(result.scheme),
                                       std::end(result.scheme),
                                       [](char c) { return c == ':'; }),
                        std::end(result.scheme));

    // now they can be parsed
    std::cout << "Scheme: " << result.scheme << '\n';
    std::cout << "Authority: " << result.authority << '\n';
    std::cout << "Path+: " << result.path << '\n';
    std::cout << "lex completed\n";

    return result;
  }

  std::string rejoin(std::vector<std::string>&& uri)
  {
    std::string result;

    for (const auto& it : uri)
    {
      result.append("/");
      result.append(it);
    }

    return result;
  }
};

}  // namespace urii
