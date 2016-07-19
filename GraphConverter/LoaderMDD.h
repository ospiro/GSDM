#pragma once
#include "TCloader.h"
#include <tuple>

class LoaderMDD
    :public TCLoader
{
    static std::string filePrefix;
public:
    virtual std::vector<Subject> loadValidList(const std::string& fn, const int nSubject = -1);
    virtual std::string getFilePath(const Subject& sub);
    
    virtual tc_t loadTimeCourse(const std::string& fn);
private:
    static const std::vector<std::string> header;
    bool checkHeader(const std::string& line);
    std::pair<std::string,int> parsePhenotypeLine(const std::string& line);
};