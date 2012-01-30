#include "yaz4py.h"
#include <string>
using namespace std;
/**
 *
 * @param query
 * @throw ZQueryException
 */
ZQuery::ZQuery(const string& query):q(ZOOM_query_create()){
    if (ZOOM_query_prefix(this->q, query.c_str())){
        string message("Wrong query: ");
        message += query;
        ZOOM_query_destroy(this->q);
        throw ZQueryException(message);
    }
}
ZQuery::~ZQuery(){
    ZOOM_query_destroy(this->q);
}