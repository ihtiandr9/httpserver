
#include <assert.h>
#include <iostream>
#include "dbclient.h"

static void exit_nicely(int err)
{
    // close the connection to the database and cleanup
    dbclose();
    exit(err);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "No password provided\n");
        fprintf(stderr, "Usage: %s password\n", argv[0]);
        exit_nicely(-1);
    }
    
    if( ! (dbopen( argv[1] ) == 0) ) { //FIXME
        fprintf(stderr, "Cant open database\n");
        exit_nicely(-1);
    }

    std::cout << dbreport() << std::endl;
    exit_nicely(0);
    return 0;
}
