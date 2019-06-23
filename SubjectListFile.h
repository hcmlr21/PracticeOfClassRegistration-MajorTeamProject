#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"Subject.h"
#include"SubjectFile.h"

using namespace std;

class SubjectListFile {
private:
	SubjectFile subjectfile;
	
public:

	void subjectlistLoad(Subject list[])
	{
		ifstream ifs;

		ifs.open("subjectlist.txt");
		int subjectNum;
		int index = -1;

		while (ifs >> subjectNum) {
			Subject temp = subjectfile.fileLoad(subjectNum);
			index++;
			list[index] = temp;
		}

		ifs.close();
	}


};