
#include <httplib.h>
#include <iostream>
#include "server.h"
#include "dbclient.h"

static void exit_nicely(int err)
{
    // close the connection to the database and cleanup
    dbclose();
    exit(err);
}

using namespace httplib;

std::string stylesheet()
{
    std::string styles = ""
        "<style>\n"
        "  .pagetopheader:hover{\n"
        "      text-decoration: underline;\n"
        "  }\n"
        "  .pagetopheader {\n"
        "      display: flex;\n"
        "      align-items: center;\n"
        "      justify-content: flex-start;\n"
        "      text-align: center;\n"
        "      background-color: tomato;\n"
        "      color: white;\n"
        "      border: 4px solid black;\n"
        "      margin: 40px;\n"
        "      padding: 20px;\n"
        "      font-size:46px;\n"
        "  }\n"
        "  .computers {\n"
        "      width: 100%;\n"
        "      border-collapse: collapse;\n"
        "      margin: 20px 0;\n"
        "  }\n"
        "  .computers th, .computers td {\n"
        "      border: 1px solid #333;\n"
        "      padding: 8px 12px;\n"
        "      text-align: left;\n"
        "  }\n"
        "  .computers th {\n"
        "      background-color: #f2b7ef;\n"
        "      font-weight: bold;\n"
        "  }\n"
        "  .computers tr:nth-child(even) {\n"
        "      background-color: #f9f9f9;\n"
        "  }\n"
        "  .computers tr:hover {\n"
        "      background-color: #529ab0;\n"
        "  }\n"
        "  .centered-text {\n"
        "      flex: 1;                /* Занимает оставшееся пространство */\n"
        "      text-align: center;     /* Центрирует текст */\n"
        "  }\n"
        // {{ конец новой таблицы }}
        "</style>";
    return styles;
}


std::string greetingPage(std::string params)
{
    std::string page = "<html><head>\n";
    page += stylesheet();
    page += "</head>\n";
    page += "<body>\n";
    page += "<div class=\"pagetopheader\">";
    page += "<img class=\"logo\" src=\"/logoimg\" alt=\"logo image\">";
    page += "<div class=\"centered-text\">Hello World!</div></div>\n";
    page += "<p>" + params + "</p>";
    page += "<p>" + dbreport() + "</p>";
    page += "</body></html>";
    return page;
}

int main(int argc, char* argv[])
{
    Server svr;

    if (argc < 2)
    {
        fprintf(stderr, "No password provided\n");
        fprintf(stderr, "Usage: %s password\n", argv[0]);
        exit_nicely(-1);
    }

    if (!(dbopen(argv[1]) == 0)) {
        fprintf(stderr, "Cant open database\n");
        exit_nicely(-1);
    }

    svr.Get("/hi", [](const Request &req, Response &res)
    {
        // По запросу к адресу "/hi" Вернуть текст как страницу
        std::cout << "Get /hi root subcommand\n"; //FIXME debug
        std::string s = "";

        for (auto p : req.params)
        {
            std::cout<<p.first<<":"<<p.second<<std::endl;
            s+= p.first + ":" + p.second + "\n";
        }
        res.set_content(greetingPage(s), "text/html");
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
        std::cout<<"Path: "<<req.path<<std::endl;       //FIXME debug
        std::cout<<"Method: "<<req.method<<std::endl;   //FIXME debug
        std::cout<<"Target: "<<req.target<<std::endl;   //FIXME debug
    });

    //Команда запускает цикл так что в реальных проектах в отдельный процесс её
    printf("Starting on %s: %d\n", ourip, port);
    svr.listen(ourip, port); //  listen port 8080

    exit_nicely(0);
    return 0;
}
