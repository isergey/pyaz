#include <boost/python.hpp>
#include <boost/python/exception_translator.hpp>
#include "yaz4py.h"
#include "Python.h"
using namespace boost::python;
using namespace std;


PyObject *cppRunTimeErrorType = NULL;
PyObject *cppZQueryExceptionType = NULL;
PyObject *cppZResultSetExceptionType = NULL;
PyObject *cppZConnectionExceptionType = NULL;

//Трансляторы исключений
void translatorRunTimeError(RunTimeError const& err) {
    PyErr_SetString(PyExc_RuntimeError, err.getMessage().c_str());
}

void translatorZQueryException(ZQueryException const& err) {
    boost::python::object pythonExceptionInstance(err);
    PyErr_SetObject(cppZQueryExceptionType, pythonExceptionInstance.ptr());
}

void translatorZResultSetException(ZResultSetException const& err) {
    boost::python::object pythonExceptionInstance(err);
    PyErr_SetObject(cppZResultSetExceptionType, pythonExceptionInstance.ptr());
}

void translatorZConnectionException(ZConnectionException const& err) {
    boost::python::object pythonExceptionInstance(err);
    PyErr_SetObject(cppZConnectionExceptionType, pythonExceptionInstance.ptr());

}

BOOST_PYTHON_MODULE(_pyaz)
{


    ////////////////////////////////////////////////////////////////////////////
    class_<ZOptions>("ZOptions")
        .def("set_option", &ZOptions::setOption)
        .def("set_implementation_name", &ZOptions::setImplementationName)
        .def("set_user", &ZOptions::setUser)
        .def("set_password", &ZOptions::setPassword)
        .def("set_database", &ZOptions::setDatabase)
        .def("set_charset", &ZOptions::setCharset)
        .def("set_group", &ZOptions::setGroup)
        .def("set_syntax", &ZOptions::setSyntax)
        .def("set_elementset_name", &ZOptions::setElementSetName)
    ;

    class_<ZConnection>("ZConnection")
        .def(init<const ZOptions *>())
        .def("connect", &ZConnection::connect)
        .def("search", &ZConnection::search, return_value_policy<manage_new_object>())
        .def("scan", &ZConnection::scan, return_value_policy<manage_new_object>())
        .def("set_option", &ZConnection::setOption)
        .def("get_option", &ZConnection::getOption)
    ;

    class_<ZQuery>("ZQuery", init<const string &>())
    ;

    class_<ZRecord>("ZRecord", init<ZResultSet*, int>())
        .def("render", &ZRecord::render)
        .def("raw", &ZRecord::raw)
        .def("get", &ZRecord::get)
    ;
    
    class_<ZResultSet>("ZResultSet", init<ZConnection *, const ZQuery&>())
        .def("set_option", &ZResultSet::setOption)
        .def("get_size", &ZResultSet::getSize)
        .def("get_record", &ZResultSet::getRecord, return_value_policy<manage_new_object>())
        .def("set_set_name", &ZResultSet::setSetName)
        .def("set_schema", &ZResultSet::setSchema)
        .def("set_syntax", &ZResultSet::setSyntax)
        .def("get_records", &ZResultSet::getRecords)
    ;
    class_<ZScanSet>("ZScanSet", init<ZConnection *, const ZQuery&>())
        .def("set_option", &ZScanSet::setOption)
        .def("get_option", &ZScanSet::getOption)
        .def("get_size", &ZScanSet::getSize)
        .def("term", &ZScanSet::term)
        .def("display_term", &ZScanSet::displayTerm)
        .def("terms", &ZScanSet::terms)
    ;
    class_<ZPackage>("ZPackage", init<ZConnection *, const ZOptions &>())
        .def(init<ZConnection *>())
        .def("set_option", &ZPackage::setOption)
        .def("get_option", &ZPackage::getOption)
        .def("send", &ZPackage::send)
    ;
    
    
    
    
    
    
    //Исключения транслируемые в питон
    //есть проблема с наследованием, т.е. исключение нельзя поймать родителем
    //!надо как-то решить!

    register_exception_translator<RunTimeError>
            (&translatorRunTimeError)
    ;

    ///////////////////////////////////////////////////////////////////////////
    class_<ZQueryException>
        ZQueryExceptionClass("ZQueryException",
            init<const string&, const int>())
    ;
    ZQueryExceptionClass.add_property("message", &ZQueryException::getMessage);
    ZQueryExceptionClass.def("__str__", &ZQueryException::getMessage);
    ZQueryExceptionClass.add_property("code", &ZQueryException::getCode);

    cppZQueryExceptionType = ZQueryExceptionClass.ptr();
    register_exception_translator<ZQueryException>
            (&translatorZQueryException)
    ;
    ///////////////////////////////////////////////////////////////////////////
    class_<ZResultSetException>
        ZResultSetExceptionClass("ZResultSetException",
            init<const string&, const int>())
    ;
    ZResultSetExceptionClass.add_property("message", &ZResultSetException::getMessage);
    ZResultSetExceptionClass.def("__str__", &ZResultSetException::getMessage);
    ZResultSetExceptionClass.add_property("code", &ZResultSetException::getCode);

    cppZResultSetExceptionType = ZResultSetExceptionClass.ptr();
    register_exception_translator<ZResultSetException>
            (&translatorZResultSetException)
    ;
    ///////////////////////////////////////////////////////////////////////////
    class_<ZConnectionException>
        ZConnectionExceptionClass("ZConnectionException",
            init<const string&, const int>())
    ;
    ZConnectionExceptionClass.add_property("message", &ZConnectionException::getMessage);
    ZConnectionExceptionClass.def("__str__", &ZConnectionException::getMessage);
    ZConnectionExceptionClass.add_property("code", &ZConnectionException::getCode);

    cppZConnectionExceptionType = ZConnectionExceptionClass.ptr();
    register_exception_translator<ZConnectionException>
            (&translatorZConnectionException)
    ;
}