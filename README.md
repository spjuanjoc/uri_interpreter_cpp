# URI interpreter C++

|CI|Platform|Build Status|
|---|---|---|
|Github Actions|Linux|![CMake](https://github.com/spjuanjoc/uri_parser_cpp/workflows/CMake/badge.svg)|
|Travis|MacOS|??|
|AppVeyor|Windowsx32?|??|

URI stands for Unified Resource Identifier.

This interpreter is used to lex and parse URIs in order to
identify its components, specially to distinguish whether the host is 
IPv4, IPv6, or Registered Name.

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
* googletest