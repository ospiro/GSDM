#pragma once
#include "TCLoader.h"
#include <tuple>

class LoaderADHD200
	: public TCLoader
{
public:
	// 1st column: scan id, 6th column: Diagnosis (0-control, 1-ADHD-combined,
	//  2-ADHD-Hyperactive/Impulsive, 3-ADHD-Inattentive)
	// 18th column: QC_Rest_1, 22nd column: QC_Anatomical_1
	// return list of <scan id, type>
	virtual std::vector<std::pair<std::string, int>> loadValidList(const std::string& fn);
	// 1st column: file, 2nd column: sequence id, 3rd~end: data 
	virtual tc_t loadTimeCourse(const std::string& fn);

private:
	static const std::vector<std::string> header;
	bool checkHeader(const std::string& line);
	// return <QC passed, scan id, diagnosis result>
	std::tuple<bool, std::string, int> parsePhenotypeLine(const std::string& line);
};
