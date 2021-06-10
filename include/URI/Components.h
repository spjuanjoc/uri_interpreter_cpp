/**
 * @brief Declaration of the components that make up a Uniform Resource Identifier.
 *
 * @author  juan.castellanos
 * @date    2021-06-02
 */

/* 1. Components */

#ifndef URII_COMPONENTS_H
#define URII_COMPONENTS_H

#include <string>

namespace urii
{

/**
 * @brief Represents the parts of the authority.
 */
struct Authority
{
  std::string host;
  std::string userinfo;
  std::string port;
};

/**
 * @brief Represents the parts of the URI.
 */
struct Components
{
  std::string scheme;
  std::string authority;
  std::string path;
  std::string query;
  std::string fragment;
  Authority   full_authority;
};

/**
 * @brief Represents the possible authority host types.
 */
enum class Host : std::uint32_t
{
  Unknown = 0, /**< 0 */
  IPv4    = 1, /**< 1 */
  IPv6    = 2, /**< 2 */
  RegName = 3  /**< 3 */
};

/**
 * @brief Represents the possible parts of the URI.
 */
enum class Component : std::uint32_t
{
  scheme    = 0, /**< 0 */
  path      = 1, /**< 1 */
  query     = 2, /**< 2 */
  fragment  = 3, /**< 3 */
  authority = 4  /**< 4 */
};

}  // namespace urii

#endif /* URII_COMPONENTS_H */
