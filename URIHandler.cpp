#include "URIHandler.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

using std::stringstream;
using std::uint32_t;
using std::vector;

const uint32_t MIN_PORT{ 0 };
const uint32_t MAX_PORT{ 65535 };

URIHandler::URIHandler( std::string  uri ) : _uri{std::move( uri )}
{
    ParseURI( _uri );
}
bool URIHandler::HasPort() const
{
    return _hasPort;
}

bool URIHandler::IsValidUri() const
{
    return _isValidURI;
}
bool URIHandler::ValidIPv4( const std::string& host )
{
    string sIP{ host };
    std::replace_if(
            sIP.begin(), sIP.end(), []( const char c ) { return c == '.'; }, ' ' );
    stringstream ss;
    ss << sIP;
    bool allDigits = true;
    while ( !ss.eof() )
    {
        string tmp;
        ss >> tmp;
        for ( unsigned char c : tmp )
        {
            allDigits &= (isdigit( c ) != 0);
        }
    }
    return allDigits;
}
bool URIHandler::IsValidHexet( const string& hexet )
{
    std::stringstream ss;
    int               outHex = 0x0;
    ss << hexet;
    ss >> std::hex >> outHex;
    ss.str( "" );
    ss.clear();
    ss << outHex;
    return ( ss.str() == hexet );
}
bool URIHandler::ValidIPv6( const std::string& host )
{
    const uint32_t MAX_NUM_OF_HEXETS = 8;
    bool   valid  = true;
    string result = CropIPv6( host );
    string section{ result };
    std::replace_if(
            section.begin(), section.end(), []( char c ) { return c == ':'; }, ' ' );
    stringstream ss;
    ss << section;
    uint32_t counter = 0;

    while ( !ss.eof() )
    {
        string hexet;
        ss >> hexet;
        valid &= IsValidHexet( hexet );
        ++counter;
    }

    if ( counter > MAX_NUM_OF_HEXETS )
    {
        valid = false;
    }

    return valid;
}
bool URIHandler::ValidRegName( const std::string& host )
{
    return true;/// \todo implement
}
string URIHandler::CropIPv6( const string& ip )
{
    string result{ ip };
    auto   pos1 = result.find( ']' );

    if ( pos1 != std::string::npos )
    {
        result = result.substr( 0, pos1 + 1 );
    }

    result.erase( std::remove_if( result.begin(), result.end(), []( char c ) { return ( c == '[' || c == ']' ); } ),
                  result.end() );
    auto pos = result.find( '%' );

    if ( pos != std::string::npos )
    {
        result = result.substr( 0, pos );
    }

    return result;
}
std::string URIHandler::GetAuthority() const
{
    return _authority;
}
std::string URIHandler::GetFragment() const
{
    return _fragment;
}
std::string URIHandler::GetHost() const
{
    return authority._host;
}
std::string URIHandler::GetPath() const
{
    return _path;
}
std::string URIHandler::GetPort() const
{
    return authority._port;
}
std::string URIHandler::GetQuery() const
{
    return _query;
}
std::string URIHandler::GetScheme() const
{
    return _scheme;
}
std::string URIHandler::GetUserInfo() const
{
    return authority._userInfo;
}
void URIHandler::ParseAuth( const std::string& sAuthority )
{
    const auto& itIpVersion = sAuthority.find( ']' );
    if ( itIpVersion != std::string::npos )
    {
        string      port   = sAuthority.substr( itIpVersion );
        const auto& itPort = port.find( ':' );
        if ( itPort != std::string::npos )
        {
            _hasPort = true;
            ParsePort( port, itPort );
        }
        if ( ValidIPv6( sAuthority ) ) 
		{
            _hostType = HostType::IPv6;
            _isValidURI = true;
            authority._host = sAuthority.substr(0, itIpVersion + 1);
        } 
		else 
		{
            _isValidURI = false;
            _hostType = HostType::Unknown;
        }
    }
    else
    {
        string      host   = sAuthority;
        const auto& itPort = sAuthority.find( ':' );

        if ( itPort != std::string::npos )
        {
            string tempPort = sAuthority;
            tempPort = tempPort.substr(itPort+1);
            const auto& itValid = tempPort.find( ':' );
            if ( itValid != std::string::npos )
            {
                _isValidURI = false;
                return;
                //ipv6 with no []
            }
            _hasPort = true;
            host     = host.substr( 0, itPort );
            ParsePort( sAuthority, itPort );
        }
        if (ValidIPv4(host))
        {
            _hostType       = HostType::IPv4;
            _isValidURI     = true;
            authority._host = host;
        }
        else if (ValidRegName(host))
        {
            _hostType       = HostType::RegName;
            _isValidURI     = true;
            authority._host = host;
        }
        else
        {
            _isValidURI = false;
            _hostType   = HostType::Unknown;
        }
    }
    ParseUserInfo();
}
void URIHandler::ParsePort( const std::string& sPort, const unsigned& pos )
{
    authority._port = sPort.substr( pos );
    authority._port.erase( std::remove_if( authority._port.begin(),
                                           authority._port.end(),
                                           []( unsigned char c ) { return !isdigit( c ); } ),
                           authority._port.end() );
    auto uPort = std::stoi( authority._port );
    
    // port range: 0 to 65535
    if ( uPort < MIN_PORT || uPort > MAX_PORT )
    {
        authority._port = "";
        _isValidURI     = false;
    }
}
void URIHandler::ParseUserInfo()
{
    auto it = authority._host.find( '@' );
    if ( it != std::string::npos )
    {
        authority._userInfo = authority._host.substr( 0, it );
        authority._host     = authority._host.substr( it + 1 );
    }
}
void URIHandler::ParseURI( const std::string& uri )
{
    string sUri{ uri };
    std::replace_if(
            sUri.begin(), sUri.end(), []( const char c ) { return c == '/'; }, ' ' );
    stringstream ss;
    ss << sUri;
    vector<string> uriVec;
    while ( !ss.eof() )
    {
        string tmp;
        ss >> tmp;
        uriVec.emplace_back( tmp );
    }
    size_t vecSize = uriVec.size();
    if ( vecSize >= 2 )
    {
        _scheme = uriVec.at( 0 );
        _scheme.erase(
                std::remove_if( _scheme.begin(), _scheme.end(), []( unsigned char c ) { return !isalpha( c ); } ),
                _scheme.end() );
        _authority = uriVec.at( 1 );
        ParseAuth( _authority );
    }
    if ( vecSize >= 3 )
    {
        auto itPath = uriVec.begin();
        std::advance( itPath, 2 );
        for ( auto it = itPath; it < uriVec.end(); ++it )
        {
            _path.append( "/" );
            _path.append( *it );
        }
        ParsePath();
    }

    if ( vecSize < 2 )
    {
        _isValidURI = false;
    }
}
void URIHandler::ParsePath()
{
    string tmp = _path;
    auto   it  = tmp.find( '#' );
    if ( it != std::string::npos )
    {
        _fragment = tmp.substr( it + 1 );
        _path     = tmp.substr( 0, it );
    }
    auto it2 = _path.find( '?' );
    if ( it2 != std::string::npos )
    {
        _query = _path.substr( it2 + 1 );
        _path  = tmp.substr( 0, it2 );
    }
}
