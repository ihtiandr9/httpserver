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
    Server svr;

    svr.Get("/hi", [](const Request &req, Response &res)
    {
        // По запросу к адресу "/hi" Вернуть текст как страницу
        std::string s;
        s = "Hello World!\n";
        for (auto p : req.params)
        {
            std::cout<<p.first<<":"<<p.second<<std::endl;
            s+= p.first + ":" + p.second + "\n";
        }

        res.set_content(s, "text/plain");
    });

    svr.Get("/", [](const Request &req, Response &res)
    {
        // По запросу к адресу "/" Вернуть текст как страницу
        res.set_content("Main Pages!", "text/plain"); //Текст для возврата и формат
    });

    //Команда запускает цикл так что в реальных проектах в отдельный процесс её
    svr.listen("0.0.0.0", 8080); //  listen port 8080

    //Проверок не делаем , по этому если программа просто завершала роботу то нужно использовать правильный ип
    //список можно получить командой в консоли ipconfig берем ип lan иле wlan
}
