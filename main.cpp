#include "URIHandler.h"
#include <iostream>
#include <string>
#include <vector>

using std::boolalpha;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

int main()
{
    cout << "Inicio" << endl;
    std::vector <bool> resultado_esperado
    {
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            false,
            false,
            false,
            false,
            false,
            true,
            true,
            true,
            true,
            true,
            false
    };
    std::vector <bool> resultado_obtenido ;

    std::vector<string> vDirecciones
    {
            "http://127.0.0.1/server/directory/NAMES.ASP?Q=Fred&Q=Sally",                                       //true
            "http://127.0.0.1:80/server/directory/NAMES.ASP?Q=Fred&Q=Sally",                                    //true
            "http://BG-D-DEVICE:8080/server/directory/NAMES.ASP?Q=Fred&Q=Sally",                                //true
            "http://www.google.com:8080/server/directory/NAMES.ASP?Q=Fred&Q=Sally",                             //true
            "http://www.juan@gmail.com:8080/server/directory/NAMES.ASP?Q=Fred&Q=Sally",                         //true
            "http://[::1]/server/directory/NAMES.ASP?Q=Fred&Q=Sally ",                                          //true
            "http://[::1]:80/server/directory/NAMES.ASP?Q=Fred&Q=Sally ",                                       //true
            "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eb]/conserver/CommunicationNodeV2/AgentProfile/1",          //true
            "https://[2001:db8:a:10:c4ba:fd7c:8886:a3eb]:8080/conserver/CommunicationNodeV2/AgentProfile/1",    //true
            "http://192.168.1.190/ADM/Pages/Default.aspx#inventory/devices",                                    //true
            "https://sitechecker.pro:8080/knowledge-base/path?name=article&topic=seo#top",                      //true
            "http://[2001:db8:a:10:c4ba:fd7c:8886:a3ebg]",                                                      //false
            "http://[2001:db8:a:10:c4ba:fd7c:8886:a3ebH]:8080",                                                 //false
            "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eib%16]",                                                   //false
            "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eOb%eth0]:80",                                              //false
            "http://[2001:db8:a:10:c4ba::8886:a3ejb%eth0]:80",                                                  //false
            "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eb]",                                                       //true
            "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eb]:8080",                                                  //true
            "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eb%16]",                                                    //true
            "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eb%eth0]:80",                                               //true
            "http://[2001:db8:a:10:c4ba::8886:a3eb%eth0]:80",                                                   //true
            "http://2001:db8:a:10:c4ba:fd7c:8886:a3eb/conserver/CommunicationNodeV2/AgentProfile/1"             //false
    };
    int count = 0;
    for (auto& it : vDirecciones)
    {
        URIHandler uri {it};
        resultado_obtenido.emplace_back( uri.IsValidUri() );
        std::cout << std::boolalpha << count << ": " << uri.IsValidUri() << std::endl;
        ++count;
    }
//    for (string &it : sV)
//    {
////        cout << "URI: " << it << endl;
//        URIHandler oUri{it}; /// @see https://en.wikipedia.org/wiki/File:URI_syntax_diagram.svg
////        cout << "Scheme: \"" << oUri.GetScheme() << "\" \n";
////        cout << "Authority: \"" << oUri.GetAuthority() << "\" ";
////        cout << "Host: \"" << oUri.GetHost() << "\" ";
////        if (oUri.HasPort() == true)
////        {
////            cout << "Port: \"" << oUri.GetPort() << "\" \n";
////        }
////        cout << "Path: \"" << oUri.GetPath() << "\" \n";
////        cout << "Query: \"" << oUri.GetQuery() << "\" \n";
////        cout << "Fragment: \"" << oUri.GetFragment() << "\" \n";
//        cout << std::boolalpha << count << ": " << oUri.IsValidUri() << endl;
//        ++count;
//    }

    cout << endl;
    return 0;
}
