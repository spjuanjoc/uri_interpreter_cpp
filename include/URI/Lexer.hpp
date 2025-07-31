/**
 * @brief Declaration of the class that performs lexical analysis,
 *        dividing a given string into components separated by a token.
 *
 * @author  spjuanjoc
 * @date    2020-11-10
 */

/* 4.1. Usage: Lexer */

#ifndef UIN_LEXER_H
#define UIN_LEXER_H

#include "Components.hpp"
#include "ILexer.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace uin
{
/**
 * @brief Implementation of the URI lexer.
 */
class Lexer : virtual public ILexer
{
public:
  Lexer() = default;

  explicit Lexer(std::string_view uri)
  : m_uri(uri)
  {
  }

  ~Lexer() override = default;

  Lexer(const Lexer&)            = default;
  Lexer(Lexer&&)                 = default;
  Lexer& operator=(const Lexer&) = default;
  Lexer& operator=(Lexer&&)      = default;

  /**
   * Delegates the tokenization of an already set URI.
   *
   * @return The tokenized URI into a Components struct.
   */
  Components lex() override { return lex(m_uri); }

  /**
   * Assigns the URI.
   *
   * @param uri
   */
  void setUri(std::string_view uri) override { m_uri = uri; }

  /**
   * Performs the tokenization of a resource with '/' as separator
   *
   * @param uri The resource.
   * @return The tokenized URI into a Components struct.
   */
  static Components lex(const std::string& uri)
  {
    Components  result;
    std::string space_separated_uri { uri };

    std::replace_if(
      std::begin(space_separated_uri),
      std::end(space_separated_uri),
      [](const char c)
      {
        return c == '/';
      },
      ' ');

    std::istringstream       iss { space_separated_uri };
    std::vector<std::string> components { std::istream_iterator<std::string> { iss },
                                          std::istream_iterator<std::string> {} };

    switch (components.size())
    {
      case 0:
        break;
      case 1:
        //        std::cout << "case 1: scheme + path \n";
        result = case1(components.at(0));
        break;
      case 2:
        //        std::cout << "case 2: scheme + authority\n";
        result = case2(components);
        break;
      case 3:
        //        std::cout << "case 3: single path\n";
        result = case3(components);
        break;
      default:
        //        std::cout << "case 4+: multi path\n";
        result = case4(components);
        break;
    }

    return result;
  }

protected:
  /**
   * Processes the case when URI contains only scheme and path, it does not contain //
   *
   * @param scheme_and_path
   * @return
   */
  static Components case1(const std::string& scheme_and_path)
  {
    Components result {};

    const auto pos = scheme_and_path.find(':');

    if (pos != std::string::npos)
    {
      result.scheme = scheme_and_path.substr(0, pos);
      result.path   = scheme_and_path.substr(pos + 1);
    }

    return result;
  }

  /**
   * Processes the case when URI contains at least scheme and authority
   *  scheme .at(0)
   *  authority .at(1)
   *
   * @param uri
   * @return
   */
  static Components case2(const std::vector<std::string>& uri)
  {
    Components result {};
    result.scheme    = uri.at(0);
    result.authority = uri.at(1);

    result.scheme.erase(
      std::remove_if(
        std::begin(result.scheme),
        std::end(result.scheme),
        [](char c)
        {
          return c == ':';
        }),
      std::end(result.scheme));

    return result;
  }

  /**
   * Process the case when URI contains scheme + authority, and at least path with a single level
   *  scheme .at(0)
   *  authority .at(1)
   *  path?query#fragment .at(2) where path does not have more than one /
   *
   * @param uri
   * @return
   */
  static Components case3(const std::vector<std::string>& uri)
  {
    Components result {};

    result.scheme    = uri.at(0);
    result.authority = uri.at(1);
    result.path      = uri.at(2);

    result.scheme.erase(
      std::remove_if(
        std::begin(result.scheme),
        std::end(result.scheme),
        [](char c)
        {
          return c == ':';
        }),
      std::end(result.scheme));

    const auto [path, query, fragment] = separatePath(result.path);

    result.path     = path;
    result.query    = query;
    result.fragment = fragment;

    return result;
  }

  /**
   * Processes the case when URI contains scheme + authority, and at least path with a multi level
   *  more than 3 means it has/multi/path/
   *  take first 2, and join from 3+
   *  scheme .at(0)
   *  authority .at(1)
   *  path?query#fragment .at(2)
   *
   * @param uri
   * @return
   */
  static Components case4(const std::vector<std::string>& uri)
  {
    Components result;

    result.scheme    = uri.at(0);
    result.authority = uri.at(1);
    result.path      = rejoinPath({ std::begin(uri) + 2, std::end(uri) });

    result.scheme.erase(
      std::remove_if(
        std::begin(result.scheme),
        std::end(result.scheme),
        [](char c)
        {
          return c == ':';
        }),
      std::end(result.scheme));

    const auto [path, query, fragment] = separatePath(result.path);

    result.path     = path;
    result.query    = query;
    result.fragment = fragment;

    return result;
  }

  /**
   * Merges components of multiple level path.
   *
   * @param multi_path The space separated path with multiple levels.
   * @return The merged multi path
   */
  static std::string rejoinPath(std::vector<std::string>&& multi_path)
  {
    std::string result;

    for (const auto& it : multi_path)
    {
      result.append("/");
      result.append(it);
    }

    return result;
  }

  /**
   * Divides query and fragment from path.
   *
   * @param path_to_end The URI components from path onwards.
   * @return The query, fragment, and path.
   */
  static std::tuple<std::string, std::string, std::string> separatePath(const std::string& path_to_end)
  {
    std::string path_only { path_to_end };
    std::string query;
    std::string fragment;

    const auto query_position = path_to_end.find('?');

    if (query_position != std::string::npos)
    {
      path_only                    = path_to_end.substr(0, query_position);
      query                        = path_to_end.substr(query_position + 1);
      const auto fragment_position = query.find('#');

      if (fragment_position != std::string::npos)
      {
        fragment = query.substr(fragment_position + 1);
        query    = query.substr(0, fragment_position);
      }
    }
    else
    {
      const auto fragment_position = path_to_end.find('#');

      if (fragment_position != std::string::npos)
      {
        path_only = path_to_end.substr(0, fragment_position);
        fragment  = path_to_end.substr(fragment_position + 1);
      }
    }

    return { path_only, query, fragment };
  }

private:
  std::string m_uri;
};

}  // namespace uin

#endif /* UIN_LEXER_H*/
