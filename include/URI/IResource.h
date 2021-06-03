/**
 * Created by juan.castellanos on 3/10/20.
*/

#pragma once

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