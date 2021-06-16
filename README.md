# URI interpreter C++

|CI|Platform|Compiler|Build Status|
|---|---|---|:---:|
|Github Actions | Linux Ubuntu  | gcc     | [![linux](https://github.com/spjuanjoc/uri_interpreter_cpp/actions/workflows/linux.yml/badge.svg)](https://github.com/spjuanjoc/uri_interpreter_cpp/actions/workflows/linux.yml)   |
|Github Actions | MacOS         | clang   | [![macos](https://github.com/spjuanjoc/uri_interpreter_cpp/actions/workflows/macosx.yml/badge.svg)](https://github.com/spjuanjoc/uri_interpreter_cpp/actions/workflows/macosx.yml) |
|AppVeyor       | Windows       | MSVC    | ??|

URI stands for Uniform Resource Identifier.

This interpreter is used to perform lexical and grammatical analysis
(lex and parse) for URIs in order to identify its components, specially to
distinguish whether the host is IPv4, IPv6, or Registered Name.

---
URI components:
* Scheme
* Authority
* Path
* Query
* Fragment

Where the authority's components are:
* Userinfo
* Host
* Port

And the host can be:
* IPv6
* IPv4
* Registered Name

The minimum required components are:
* Scheme
* Host ?
* Path

---

URI generic syntax:

    URI = scheme:[//authority]path[?query][#fragment]

where the authority component divides into three subcomponents:

    authority = [userinfo@]host[:port]

![img](docs/images/1920px-URI_syntax_diagram.svg.png "URI syntax diagram")


See the Wiki for [URI](https://en.wikipedia.org/wiki/Uniform_Resource_Identifier)

## Tools 
* CMake > 3.1
* gcc-7 c++17
* conan
* Catch2
