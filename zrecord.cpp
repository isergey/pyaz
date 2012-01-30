#include "yaz4py.h"
#include <string>
using namespace std;

/**
 *
 * @param zrs
 * @param index
 * @throw ZResultSetException
 */
ZRecord::ZRecord(ZResultSet* zrs, int index)
{
    this->zrs = zrs;
    if (index > (this->zrs->getSize()-1) || index < 0)
        throw ZResultSetException("Wrong record range");
    this->zr = ZOOM_resultset_record (this->zrs->_getYazResultSet(), index);
    
    const char *msg;
    const char *addinfo;
    const char *diagset;
    if (ZOOM_record_error(this->zr , &msg, &addinfo, &diagset) != 0){
        string emessage(msg);
    	string eaddinfo(addinfo);
    	string message = emessage + " " + eaddinfo;
        throw ZResultSetException(message);
    }
}

ZRecord::~ZRecord()
{
    //ZOOM_record_destroy(this->zr);
}

string ZRecord::render() const
{
    int len;
    const char* data = ZOOM_record_get(this->zr, "render", &len);
    return string(data, len);
}

string ZRecord::raw() const
{
    int len;
    const char* data = ZOOM_record_get(this->zr, "raw", &len);
    return string(data, len);
}

string ZRecord::get(const string& param)
{
    int len;
    const char* data = ZOOM_record_get(this->zr, param.c_str(), &len);
    return string(data, len);
}
