#include "yaz4py.h"
#include <string>
#include <string.h>
using namespace std;

/**
 *
 * @param zo
 */
ZConnection::ZConnection(const ZOptions* zo)
{
    this->zc = ZOOM_connection_create(zo->_getYazOptions());
    if(this->zc == NULL){
        throw RunTimeError("Connection object not created");
    }
}
ZConnection::~ZConnection()
{
    ZOOM_connection_destroy(this->zc);
}
/**
 * @param hostname
 * @param portnum
 * @throw ZConnectionException
 */
void ZConnection::connect(const string &hostname, int portnum)
{

    ZOOM_connection_connect(this->zc, hostname.c_str(), portnum);
    int errcode;
    const char *errmsg;     // unused: carries same info as `errcode'
    const char *addinfo;
    if ((errcode = ZOOM_connection_error(this->zc, &errmsg, &addinfo)) != 0) {
    	string emessage(errmsg);
    	string eaddinfo(addinfo);
    	string message = emessage + ": " + eaddinfo;
        throw ZConnectionException(message, errcode);
    }
}
/**
 * 
 * @param zq
 * @return
 */
const ZResultSet* ZConnection::search(const ZQuery &zq)
{
    ZResultSet *rs = new ZResultSet(this, zq);
    if(rs == NULL){
        throw RunTimeError("Result set object not created");
    }
    return rs;
}

const ZScanSet* ZConnection::scan(const ZQuery &zq)
{
    ZScanSet *zss = new ZScanSet(this, zq);
    if(zss == NULL){
        throw RunTimeError("Scan set object not created");
    }
    return zss;
}

void ZConnection::setOption(const string& key, const string& value)
{
	ZOOM_connection_option_set(this->zc, key.c_str(), value.c_str());
}

string ZConnection::getOption(const string& key)
{
    const char* value = ZOOM_connection_option_get(this->zc, key.c_str());
    return string(value);
}