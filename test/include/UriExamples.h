/**
 * Created by juan.castellanos on 2/06/21.
*/

#pragma once


/**
 *
 * mailto:John.Doe@example.com
 * └─┬──┘ └────┬─────────────┘
 * scheme     path
 */
constexpr auto scheme_path_mailto = "mailto:John.Doe@example.com";

/**
 *
 * tel:+1-816-555-1212
 * └┬┘ └──────┬──────┘
 * scheme    path
*/
constexpr auto scheme_path_tel = "tel:+1-816-555-1212";

/**
 *
 * urn:oasis:names:specification:docbook:dtd:xml:4.1.2
 * └┬┘ └──────────────────────┬──────────────────────┘
 * scheme                    path
 */
constexpr auto scheme_path_urn = "urn:oasis:names:specification:docbook:dtd:xml:4.1.2";

/**
 *
 * news:comp.infosystems.www.servers.unix
 * └┬─┘ └─────────────┬─────────────────┘
 * scheme            path
*/
constexpr auto scheme_path_news = "news:comp.infosystems.www.servers.unix";

/**
 *
 * telnet://192.0.2.16:80/
 * └─┬──┘   └─────┬─────┘│
 * scheme     authority  path
*/
constexpr auto scheme_authorityIPv4 = "telnet://192.0.2.16:80/";
constexpr auto scheme_authorityIPv4_path = "telnet://192.0.2.17:80/path";

/**
 *
 * ldap://[2001:db8::7]/c=GB?objectClass?one
 * └┬─┘   └─────┬─────┘└─┬─┘ └──────┬──────┘
 * scheme   authority   path      query
*/
constexpr auto scheme_authorityIPv6_path_query = "ldap://[2001:db8::7]/c=GB?objectClass?one";

/**
 *
 *
 *           userinfo       host      port
 *          ┌──┴───┐ ┌──────┴──────┐ ┌┴┐
 *  https://john.doe@www.example.com:123/forum/questions/?tag=networking&order=newest#top
 *  └─┬─┘   └───────────┬──────────────┘└───────┬───────┘ └───────────┬─────────────┘ └┬┘
 *  scheme          authority                  path                 query           fragment
 */
constexpr auto name_path_query_fragment
  = "https://john.doe@example.com:123/forum/questions/?tag=networking&order=newest#top";
constexpr auto name_path_query_fragment_2
  = "https://sitechecker.pro:8080/knowledge-base/path?name=article&topic=seo#top";

/**
 *
 *            registered name
 *          ┌───────┴──────────┐
 *  https://spjuanjoc.github.io/avanzado/fechas-formato-estandar/#usando-la-biblioteca-fmt
 *  └─┬─┘   └────────┬─────────┘└────────────┬──────────────────┘└───────────┬───────────┘
 *  scheme       authority                  path                           fragment
 */
constexpr auto name_path_fragment
  = "https://spjuanjoc.github.io/avanzado/fechas-formato-estandar/#usando-la-biblioteca-fmt";
