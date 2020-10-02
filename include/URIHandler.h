#ifndef URIHANDLER_H
#define URIHANDLER_H

#include <string>

using std::string;

/** \defgroup HostType
 * \ingroup enums */
///@{
/// @brief Tipos de host: IPv4, IPv6, RegisteredName
enum class HostType : std::uint32_t
{
    Unknown = 0, /**< 0 */
    IPv4    = 1, /**< 1 */
    IPv6    = 2, /**< 2 */
    RegName = 3  /**< 3 */
};
///@}
class URIHandler
{
        private:
        string _uri;
        string _scheme;
        string _authority;
        struct authority
        {
            string _userInfo;
            string _host;  /// @remark IPv4 in dot-decimal notation, IPv6 enclosed in brackets [].
            string _port;
        } authority;
        string   _path;
        string   _query;
        string   _fragment;
        HostType _hostType{ HostType::Unknown };
        bool     _hasPort{ false };
        bool     _isValidURI{ false };

        // Mandatory
        /// ParseAuth
        /// \brief Parse Authority: <userinfo@>host<:port>
        /// \param Authority string
        void ParseAuth( const std::string& Authority );

        /// ParseURI
        /// \brief Parse URI processes URI and divides it by
        ///        scheme, authority, and (optional) path, query, and fragment
        /// \param string URI address
        /// \throws logic_error if URI isn't at least scheme://authority
        void ParseURI( const std::string& uri );

        // Optional
        static bool        IsValidHexet( const std::string& hexet );
        static bool        ValidIPv4( const std::string& host );
        static bool        ValidIPv6( const std::string& host );
        static bool        ValidRegName( const std::string& host );
        static std::string CropIPv6( const std::string& ip );
        void        ParsePort( const std::string& port, const unsigned& pos );
        void        ParseUserInfo();
        void        ParsePath();

        public:
        /// URIHandler
        /// \brief ctor parses URI, with scheme and authority as mandatory
        /// \param uri
        explicit URIHandler( std::string uri );
        URIHandler() = default;

        bool   HasPort() const;
        bool   IsValidUri() const;
        string GetAuthority() const;
        string GetFragment() const;
        string GetHost() const;
        string GetPath() const;
        string GetPort() const;
        string GetQuery() const;
        string GetScheme() const;
        string GetUserInfo() const;
};

#endif  // URIHANDLER_H
