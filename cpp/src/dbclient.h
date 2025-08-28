#ifndef H_DBCLIENT_H

#define H_DBCLIENT_H
#define INDENT "    "
#ifdef __cplusplus
extern "C" {
#endif

typedef struct pg_conn PGconn;

#ifdef __cplusplus
}
#endif

#define default_dbhost "localhost";
PGconn* dbconn();
void dbclose();
int dbopen(const char* host, const char* passwd);
std::string dbreport();

#endif
