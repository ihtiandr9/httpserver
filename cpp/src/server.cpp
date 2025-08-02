
#include <httplib.h>
#include <iostream>
#include "server.h"

using namespace httplib;

std::string greetingPage()
{
    std::string page = "<html><body><div style=\"font-size: 50;\">Hello World!</div><img src=\"/logoimg\"></body></html>";
    return page;
}

int main(void)
{
    Server svr;

    svr.Get("/hi", [](const Request &req, Response &res)
    {
        // По запросу к адресу "/hi" Вернуть текст как страницу
        std::cout << "Get /hi root subcommand\n"; //FIXME debug
        std::string s;
        s = greetingPage();
        for (auto p : req.params)
        {
            std::cout<<p.first<<":"<<p.second<<std::endl;
            s+= p.first + ":" + p.second + "\n";
        }
        res.set_content(s, "text/html");
    });

    svr.Get("/", [](const Request &req, Response &res)
    {
        // По запросу к адресу "/" Вернуть текст как страницу
        std::cout << "Get root of site req\n";     //FIXME debug
        res.set_content("Main Pages!", "text/plain"); //Текст для возврата и формат
        for (auto p : req.params)
        {
            std::cout<<p.first<<":"<<p.second<<std::endl;
        }
    });
    ////////////////////////////////////////////////////////
    svr.Get("/[a-z]+", [](const Request &req, Response &res)
    {
    std::cout << "unrecognized command to root page\n";  //FIXME debug
        // Other unrecognized commands to root
        res.set_content("Unrecognized command to root Page!", "text/plain"); //Текст для возврата и формат
        for (auto p : req.params)
        {
            std::cout<<p.first<<":"<<p.second<<std::endl;
        }
        std::cout<<"Path: "<<req.path<<std::endl;
        std::cout<<"Method: "<<req.method<<std::endl;
        std::cout<<"Target: "<<req.target<<std::endl;
    });

    //Команда запускает цикл так что в реальных проектах в отдельный процесс её
    printf("Starting on %s: %d\n", ourip, port);
    svr.listen(ourip, port); //  listen port 8080

}
