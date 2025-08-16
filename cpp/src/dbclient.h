#ifndef H_DBCLIENT_H
#include <libpq-fe.h>

PGconn* dbconn();
void dbclose();
int dbopen(char* passwd);
#endif
