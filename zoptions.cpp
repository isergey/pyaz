#include "yaz4py.h"
#include <string>
using namespace std;

ZOptions::ZOptions()
{
    this->zo = ZOOM_options_create ();
    this->setCharset("UTF-8");
}
ZOptions::~ZOptions()
{
    ZOOM_options_destroy(this->zo);
}

void ZOptions::setOption(const string& key, const string& value)
{
    if (key == "async") return; //not async realization
    ZOOM_options_set (this->zo, key.c_str(), value.c_str());
}

void ZOptions::setImplementationName(const string& param)
{
    this->setOption("implementationName", param);
}
void ZOptions::setUser(const string& param)
{
    this->setOption("user", param);
}
void ZOptions::setPassword(const string& param)
{
    this->setOption("password", param);
}
void ZOptions::setDatabase(const string& param)
{
    this->setOption("databaseName", param);
}
void ZOptions::setCharset(const string& param)
{
    this->setOption("charset", param);
}
void ZOptions::setGroup(const string& param)
{
    this->setOption("group", param);
}
void ZOptions::setSyntax(const string& param)
{
    this->setOption("preferredRecordSyntax", param);
}
void ZOptions::setElementSetName(const string& param)
{
    this->setOption("elementSetName", param);
}