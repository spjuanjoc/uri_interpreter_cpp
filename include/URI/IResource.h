/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2020-10-03
 */

#ifndef URII_IRESOURCE_H
#define URII_IRESOURCE_H

#include <string>

namespace urii
{
/**
 * 1. Components
 */
struct Authority;
struct Components;
enum class Host : std::uint32_t;
enum class Component : std::uint32_t;

/**
 * 2. Interface
 */
class IResource
{
public:
  IResource()                 = default;
  virtual ~IResource()        = default;
  IResource(const IResource&) = default;
  IResource(IResource&&)      = default;
  IResource& operator=(const IResource&) = default;
  IResource& operator=(IResource&&) = default;

  virtual bool        validate(Host) = 0;
  virtual std::string get(Component) = 0;
};

}  // namespace urii

#endif /* URII_IRESOURCE_H */
