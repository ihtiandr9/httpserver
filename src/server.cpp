
#include <httplib.h>
#include <iostream>
using namespace httplib;

std::string stylesheet()
{
    std::string styles = ""
        "<style>\n"
        "  .pagetopheader:hover{\n"
        "      text-decoration: underline;\n"
        "  }\n"
        "  .pagetopheader {\n"
        "      text-align: center;\n"
        "      background-color: tomato;\n"
        "      color: white;\n"
        "      border: 4px solid black;\n"
        "      margin: 40px;\n"
        "      padding: 20px;\n"
        "      font-size:46px;\n"
        "  }</style>";
    return styles;
}

std::string greetingPage(std::string params)
{
    std::string page = "<html><head>\n";
    page += stylesheet();
    page += "</head>\n";
    page += "<body>\n";
    page += "<div class=\"pagetopheader\">Hello World!</div>\n";
    page += "<img src=\"/logoimg\" alt=\"logo image\">\n";
    page += "<p>" + params +"</p>";
    page += "</body></html>";
    return page;
}

int main(void)
{
    Server svr;

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
    std::cout << "unrecognized command to root\n";  //FIXME debug
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
    svr.listen("0.0.0.0", 8080); //  listen port 8080

}
