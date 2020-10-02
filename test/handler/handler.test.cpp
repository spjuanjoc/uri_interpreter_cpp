//
// Created by juan.castellanos on 2/10/20.
//

#include "URIHandler.h"
#include <gtest/gtest.h>

struct HandlerFixture : public testing::Test
{
};

TEST_F(HandlerFixture, IsValidUri)
{
  std::vector<bool> expected{
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
    true,
    true,
    true,
    true,
    true,
  };

  std::vector<string> validAddresses{
    "http://127.0.0.1/server/directory/NAMES.ASP?Q=Fred&Q=Sally",                   // true
    "http://127.0.0.1:80/server/directory/NAMES.ASP?Q=Fred&Q=Sally",                // true
    "http://BG-D-DEVICE:8080/server/directory/NAMES.ASP?Q=Fred&Q=Sally",            // true
    "http://www.google.com:8080/server/directory/NAMES.ASP?Q=Fred&Q=Sally",         // true
    "http://www.user@gmail.com:8080/server/directory/NAMES.ASP?Q=Fred&Q=Sally",     // true
    "http://[::1]/server/directory/NAMES.ASP?Q=Fred&Q=Sally ",                      // true
    "http://[::1]:80/server/directory/NAMES.ASP?Q=Fred&Q=Sally ",                   // true
    "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eb]/server/node/profile/1",             // true
    "https://[2001:db8:a:10:c4ba:fd7c:8886:a3eb]:8080/server/node/profile/1",       // true
    "http://192.168.1.190/ADM/Pages/Default.aspx#inventory/devices",                // true
    "https://sitechecker.pro:8080/knowledge-base/path?name=article&topic=seo#top",  // true
    "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eb]",                                   // true
    "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eb]:8080",                              // true
    "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eb%16]",                                // true
    "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eb%eth0]:80",                           // true
    "http://[2001:db8:a:10:c4ba::8886:a3eb%eth0]:80",                               // true
  };

  std::vector<bool> actual;
  for (auto& it : validAddresses)
  {
    URIHandler uri{it};
    actual.emplace_back(uri.IsValidUri());
  }

  EXPECT_EQ(expected, actual);
}

TEST_F(HandlerFixture, IsInValidUri)
{
  std::vector<bool> expected{false, false, false, false, false, false};

  std::vector<string> invalidAddresses{
    "http://[2001:db8:a:10:c4ba:fd7c:8886:a3ebg]",                    // false
    "http://[2001:db8:a:10:c4ba:fd7c:8886:a3ebH]:8080",               // false
    "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eib%16]",                 // false
    "http://[2001:db8:a:10:c4ba:fd7c:8886:a3eOb%eth0]:80",            // false
    "http://[2001:db8:a:10:c4ba::8886:a3ejb%eth0]:80",                // false
    "http://2001:db8:a:10:c4ba:fd7c:8886:a3eb/server/node/profile/1"  // false
  };

  std::vector<bool> actual;
  for (auto& it : invalidAddresses)
  {
    URIHandler uri{it};
    actual.emplace_back(uri.IsValidUri());
  }

  EXPECT_EQ(expected, actual);
}
