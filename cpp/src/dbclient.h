#ifndef H_DBCLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <libpq-fe.h>

#ifdef __cplusplus
}
#endif

PGconn* dbconn();
void dbclose();
int dbopen(const char* passwd);
std::string dbreport();

#endif
