//
// Created by juan.castellanos on 10/11/20.
//
#pragma once

#include "Resource.h"

namespace urii
{
/**
 * 4. Usage - lex
 */
Components case1(const std::string& schemeAndPath);
Components case2(const std::vector<std::string>& uri);
Components case3(const std::vector<std::string>& uri);
Components case4(const std::vector<std::string>& uri);

Components lex(const std::string& input)
{
  Components  result;
  std::string slashLex{input};

  std::replace_if(
    std::begin(slashLex),
    std::end(slashLex),
    [](const char c) { return c == '/'; },
    ' ');

  std::istringstream       iss{slashLex};
  std::vector<std::string> components{std::istream_iterator<std::string>{iss},
                                      std::istream_iterator<std::string>{}};

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

/*
 * URI contains only scheme and path, it does not contain //
 */
Components case1(const std::string& schemeAndPath)
{
  Components result{};

  const auto pos = schemeAndPath.find(':');

  if (pos != std::string::npos)
  {
    result.scheme = schemeAndPath.substr(0, pos);
    result.path   = schemeAndPath.substr(pos + 1);
  }

  // now they can be parsed
  std::cout << "lex completed\n";
  return result;
}

/*
 * URI contains at least scheme and authority
 *
 * scheme .at(0)
 * authority .at(1)
 */
Components case2(const std::vector<std::string>& uri)
{
  Components result{};
  result.scheme        = uri.at(0);
  result.fullAuthority = uri.at(1);

  result.scheme.erase(std::remove_if(std::begin(result.scheme),
                                     std::end(result.scheme),
                                     [](char c) { return c == ':'; }),
                      std::end(result.scheme));

  // now they can be parsed
  std::cout << "Scheme: " << result.scheme << '\n';
  std::cout << "Authority: " << result.fullAuthority << '\n';
  std::cout << "lex completed\n";

  return result;
}

/*
 * URI contains scheme + authority, and at least path with a single level
 *
 * scheme .at(0)
 * authority .at(1)
 * path?query#fragment .at(2) where path does not have more than one /
 */
Components case3(const std::vector<std::string>& uri)
{
  Components result{};

  result.scheme        = uri.at(0);
  result.fullAuthority = uri.at(1);
  result.path          = uri.at(2);

  result.scheme.erase(std::remove_if(std::begin(result.scheme),
                                     std::end(result.scheme),
                                     [](char c) { return c == ':'; }),
                      std::end(result.scheme));

  // now they can be parsed
  std::cout << "Scheme: " << result.scheme << '\n';
  std::cout << "Authority: " << result.fullAuthority << '\n';
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

/*
 * URI contains scheme + authority, and at least path with a multi level
 *
 * more than 3 means it has/multi/path/
 * take first 2, and join from 3+
 *
 * scheme .at(0)
 * authority .at(1)
 * path?query#fragment .at(2)
 */
Components case4(const std::vector<std::string>& uri)
{
  Components result;

  result.scheme        = uri.at(0);
  result.fullAuthority = uri.at(1);
  result.path          = rejoin({std::begin(uri) + 2, std::end(uri)});

  result.scheme.erase(std::remove_if(std::begin(result.scheme),
                                     std::end(result.scheme),
                                     [](char c) { return c == ':'; }),
                      std::end(result.scheme));

  // now they can be parsed
  std::cout << "Scheme: " << result.scheme << '\n';
  std::cout << "Authority: " << result.fullAuthority << '\n';
  std::cout << "Path+: " << result.path << '\n';
  std::cout << "lex completed\n";

  return result;
}

/**
 * 4. Usage - parser
 */
//...

}

/**
Plan:

 1. Components
  scheme      mandatory
  path        mandatory
  authority
    host
    userinfo
    port
  query
  fragment

 2. Interface
    IResource
       Validate(host type: v4, v6, RN)
        - validate mandatory components
        - validate host sub component
        - then validate the rest
       GetComponent(component)

 3. Implementation
    Resource
      validate -> Dynamic Strategy
          Dynamic host parser
            Interface IParser
              IPv6Parser
              IPv4Parser
              RNParser
      get

 4. Usage
    lexer
    parser
      The dynamic strategy usage class

 5. resolver?
    what to do with the parsed data
    auto parsed = parse("URI");
    parsed->validate(Host::IPv6);
    parsed->Get(Component::scheme)

 */

