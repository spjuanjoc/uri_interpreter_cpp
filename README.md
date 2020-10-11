# URI parser C++
Identify, process, and distinguish IPv4, IPv6, and RegName for URI.

|CI|Platform|Build Status|
|---|---|---|
|Github Actions|Linux|![CMake](https://github.com/spjuanjoc/uri_parser_cpp/workflows/CMake/badge.svg)|

---
Analyse the URI to distinguish:
* IPv6
* IPv4
* Registered Name
* Port

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