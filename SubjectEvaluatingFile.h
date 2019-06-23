#pragma once
#include "FileManager.h"
#include "SubjectEvaluation.h"
using namespace std;
class SubjectEvaluating : public FileManager {
public:
	SubjectEvaluating() {

	}
	//save 필요
	bool fileSave(Account* account,string lectureName) {
		string evaluation;
		string filePath = lectureName + " 강의평가.txt";

		// write File
		ofstream ofs;
		ofs.open((".\\강의평가\\" + filePath).data(), ios::ate | ios::_Nocreate);
		// 이어쓰기 가능하게 하는 역할
		if (!ofs) {
			ofs.close();
			return false;
		}
		else {
			cout << "내용을 입력해주세요: " << endl;
			getline(cin, evaluation);
			ofs << endl << account->getName() << ": " << evaluation << endl;
			ofs.close();
			return true;
		}
	}

	bool fileLoad(string lectureName) {
		ifstream ifs;
		string line;

		lectureName += " 강의평가.txt";
		ifs.open((".\\강의평가\\" + lectureName).data(), ios::in);

		if (!ifs) {
			ifs.close();
			return false;
		}
		else {
			while (!ifs.eof()) {
				line.clear();
				getline(ifs, line);
				cout << line << endl;
			}
			ifs.close();
			return true;
		}
	}
};