#include "yaz4py.h"
#include <boost/python.hpp>
#include <string>
using namespace std;
/**
 *
 * @param zc
 * @param zq
 * @throw ZConnectionException
 */
ZPackage::ZPackage(ZConnection *zc)
{
    this->zc = zc;
    this->package =  ZOOM_connection_package(zc->_getYazConnection(), 0);
}
ZPackage::ZPackage(ZConnection *zc, const ZOptions &zo)
{
    this->zc = zc;
    this->package =  ZOOM_connection_package(zc->_getYazConnection(), zo._getYazOptions());
}
ZPackage::~ZPackage()
{
    ZOOM_package_destroy(this->package);
}

void ZPackage::send(const string& type)
{
    ZOOM_package_send(this->package, type.c_str());
    int errcode;
    const char *errmsg;     // unused: carries same info as `errcode'
    const char *addinfo;
    if ((errcode = ZOOM_connection_error(this->zc->_getYazConnection(), &errmsg, &addinfo)) != 0) {
    	string emessage(errmsg);
    	string eaddinfo(addinfo);
    	string message = emessage + ": " + eaddinfo;
        throw ZConnectionException(message, errcode);
    }
}

void ZPackage::setOption(const string& key, const string& value)
{
    ZOOM_package_option_set(this->package, key.c_str(), value.c_str());
}

string ZPackage::getOption(const string& key)
{
    const char* value = ZOOM_package_option_get(this->package, key.c_str());
    return string(value);
}