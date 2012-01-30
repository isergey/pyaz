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
ZScanSet::ZScanSet(ZConnection *zc, const ZQuery &zq)
{
    this->ss = 0;
    ZOOM_connection yazc = zc->_getYazConnection();
    this->ss = ZOOM_connection_scan1(yazc, zq._getYazQuery());
    int errcode;
    const char *errmsg;     // unused: carries same info as `errcode'
    const char *addinfo;
    if ((errcode = ZOOM_connection_error(yazc, &errmsg, &addinfo)) != 0) {
    	string emessage(errmsg);
    	string eaddinfo(addinfo);
    	string message = emessage + ": " + eaddinfo;
        throw ZConnectionException(message, errcode);
    }
}
ZScanSet::~ZScanSet()
{
    ZOOM_scanset_destroy(this->ss);
}
size_t ZScanSet::getSize() const
{
    return ZOOM_scanset_size(this->ss);
}

string ZScanSet::term(const size_t index)
{
    size_t len;
    size_t occur;
    const char *term;
    term = ZOOM_scanset_term (this->ss, index, &occur, &len);
    return string(term);
}

boost::python::tuple ZScanSet::displayTerm(const size_t index)
{
    size_t len;
    size_t occur;
    const char *cterm;
    boost::python::list term;
    cterm = ZOOM_scanset_display_term (this->ss, index, &occur, &len);
    return boost::python::make_tuple(string(cterm), occur);
}
boost::python::list ZScanSet::terms()
{
    size_t scanSize = ZOOM_scanset_size(this->ss);
    boost::python::list terms;
    
    for (size_t index = 0; index < scanSize; index++){
        size_t len;
        size_t occur;
        const char *cterm;
        cterm = ZOOM_scanset_term (this->ss, index, &occur, &len);
        terms.append(boost::python::make_tuple(string(cterm), occur));
    }
    return terms;
}
void ZScanSet::setOption(const string& key, const string& value)
{
    ZOOM_scanset_option_set(this->ss, key.c_str(), value.c_str());
}

string ZScanSet::getOption(const string& key)
{
    const char* value = ZOOM_scanset_option_get(this->ss, key.c_str());
    return string(value);
}
