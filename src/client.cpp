//
//  hello.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <httplib.h>
#include <iostream>
using namespace httplib;

int main(void)
{
    std::string qStr = "/hi";
    qStr.append("?user=secret&passwd=1234");
    Client cli("localhost", 8080);
    auto res = cli.Get(qStr.c_str());
    if (res && res->status == 200) {
        std::cout << res->body << std::endl;
    }

    return 0;
}
