/**
 * src/dbclient.cpp
 *
 *      Test the C module for save connection to
 *      PostgreSQL database frontend library.
 */

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "dbclient.h"

static PGconn     *conn;
static char conninfo[128];

void dbclose()
{
    // Проверяем, существует ли соединение перед его закрытием
    if (conn != NULL) {
        PQfinish(conn);
        conn = NULL;  // Обнуляем указатель после закрытия
    }
}



int
dbopen(const char* passwd)
{

    sprintf(conninfo,"host=192.168.1.3 dbname=mycomps user=postgres password=%s connect_timeout=10",
        passwd
    );

    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);

    /* Check to see that the backend connection was successfully made */
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s",
                PQerrorMessage(conn));
        return 1;
    }
    return 0;
}

std::string dbreport()
{
    PGresult   *res;
    int         nFields;
    int         i,
                j;
    std::string result = "<table class=\"computers\">";                

    if (conn == NULL) 
    {
        fprintf(stderr, "Database not opened");
        return "";
    }

    if (PQstatus(conn) == CONNECTION_BAD)
    {
        fprintf(stderr, "Connection to database lost: %s",
                PQerrorMessage(conn));
        return "";
    }
    /* Set always-secure search path, so malicious users can't take control. */
    res = PQexec(conn,
                 "SELECT pg_catalog.set_config('search_path', 'public', false)");

    /* Return empty string if cant configure */
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return "";
    }

    /*
     * Should PQclear PGresult whenever it is no longer needed to avoid memory
     * leaks
     */
    PQclear(res);

    /* Start a transaction block */
    res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return "";
    }
    PQclear(res);

    res = PQexec(conn,	"SELECT * from computers as computers"
			" LEFT JOIN comp_configs as comp_configs"
			" ON computers.code = comp_configs.comp_code");
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return "";
    }

    /* first, print out the attribute names */
    nFields = PQnfields(res);
    result += "<tr>";
    for (i = 0; i < nFields; i++)
        result += "<th>" + std::string(PQfname(res, i)) + "</th>";
    result += "</tr>";

    /* next, print out the rows */
    for (i = 0; i < PQntuples(res); i++)
    {
        for (j = 0; j < nFields; j++)
            if (PQgetisnull(res, i, j))
                result += "<td></td>";
            else
                result += "<td>" + std::string(PQgetvalue(res, i, j)) + "</td>";
        result += "</tr>";
    }

    PQclear(res);

    /* end the transaction */
    res = PQexec(conn, "END");
    PQclear(res);

    return result;
}

