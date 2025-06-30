
#include <httplib.h>
#include <assert.h>
#include <iostream>
using namespace httplib;

int main(void)
{
    std::string qStr = "/hi";
    qStr.append("?user=secret&passwd=1234");
    Client cli("localhost", 8080);
    auto res = cli.Get(qStr.c_str());
    if (res )
    {
        switch(res->status)
        {
        case 200:
            std::cout << res->body << std::endl;
            break;
        default:
            std::cout << "Unexpected response status" << res->status <<std::endl;
            assert(false);
        }
    }
    else
        std::cout<< "Server unreachable"<<std::endl;

    return 0;
}
