
#pragma once
#include "TCLoader.h"
#include <tuple>

class LoaderABIDE
    :public TCLoader

{
    static std::string filePrefix;
public:
    virtual std::vector<Subject> loadValidList(const std::string& fn, const int nSubject = -1);
    
//    virtual std::vector<Subject> getAllSubjects(std::vector<Subject>& vldlist, const std::string& root);
    
    
    virtual std::string getFilePath(const Subject& sub);
    
    virtual tc_t loadTimeCourse(const std::string& fn);
private:
    static const std::vector<std::string> header;
    bool checkHeader(const std::string& line);
    std::tuple<bool,std::string,int> parsePhenotypeLine(const std::string& line);
};


