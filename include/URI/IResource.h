/**
 * @brief Declaration of the interface that stores a URI.
 *
 * @author  juan.castellanos
 * @date    2020-10-03
 */

/* 2. Interface */

#ifndef URII_IRESOURCE_H
#define URII_IRESOURCE_H

#include <string>

namespace urii
{
// Forward declarations
struct Authority;
struct Components;
enum class Host : std::uint32_t;
enum class Component : std::uint32_t;

/**
 * @brief Interface that represents the methods for processing a URI.
 */
class IResource  // TODO maybe rename to IInterpreter
{
public:
  IResource()          = default;
  virtual ~IResource() = default;

  // Rule of five for special members.
  IResource(const IResource&) = default;
  IResource(IResource&&)      = default;
  IResource& operator=(const IResource&) = default;
  IResource& operator=(IResource&&) = default;

  virtual bool        validate(Host) = 0;
  virtual std::string get(Component) = 0;
};

}  // namespace urii

#endif /* URII_IRESOURCE_H */
