//
// Created by spjuanjoc on 3/10/20.
//
#pragma once

#include <optional>
namespace URI
{
class IParser;
class IValidator;

struct Interpreter
{
  std::optional<IParser*> parser;
  IValidator* validator;
};
}
