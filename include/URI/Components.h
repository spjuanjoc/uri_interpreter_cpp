/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-06-02
 */

#ifndef URII_COMPONENTS_H
#define URII_COMPONENTS_H

#include <string>

namespace urii
{
/**
 * 1. Components
 */

/**
 * The parts of the authority
 */
struct Authority
{
  std::string host;
  std::string userinfo;
  std::string port;
};

/**
 * The parts of the URI
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
 * The possible authority host types
 */
enum class Host : std::uint32_t
{
  Unknown = 0, /**< 0 */
  IPv4    = 1, /**< 1 */
  IPv6    = 2, /**< 2 */
  RegName = 3  /**< 3 */
};

/**
 *
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
