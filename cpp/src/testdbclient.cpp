
#include <assert.h>
#include <iostream>
#include <getopt.h>
#include "dbclient.h"

static void exit_nicely(int err)
{
    // close the connection to the database and cleanup
    dbclose();
    exit(err);
}

void usage(int panic){
    fprintf(stderr, "No password provided\n");
    fprintf(stderr, "Usage: testdbclient [ -h | --host host] -p password\n");
    if (panic){
        exit_nicely(-1);
    }
}


static struct option opts[] =
    {
        {"host", required_argument, 0, 'h'},
        {"passwd", required_argument, 0, 'p'},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0}};

static const char *host = default_dbhost;
static const char *passwd = 0;

int main(int argc, char* argv[])
{
    int rez;
    int long_index;

    if (argc < 2)
    {
        usage(1);
    }

    while (-1 != (rez = getopt_long(argc, argv, "h:p:v", opts, &long_index)))
    {
        switch (rez)
        {
            case 'h':
                host = optarg;
                break;
            case 'p':
                passwd = optarg;
                break;
            case 'v':
                printf("V1.0\n");
                exit_nicely(0);
                break;
            default:
                fprintf(stderr, "Unknown option: %c\n", rez);
                exit_nicely(-1);
        }
    }

    if (!passwd)
        usage(1);

    if( ! (dbopen( host, passwd ) == 0) ) {
        fprintf(stderr, "Cant open database\n");
        exit_nicely(-1);
    }

    std::cout << dbreport() << std::endl;
    exit_nicely(0);
    return 0;
}
