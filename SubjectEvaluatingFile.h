#pragma once
#include "FileManager.h"
#include "SubjectEvaluation.h"
using namespace std;
class SubjectEvaluating : public FileManager {
public:
	SubjectEvaluating() {

	}
	//save �ʿ�
	bool fileSave(Account* account,string lectureName) {
		string evaluation;
		string filePath = lectureName + " ������.txt";

		// write File
		ofstream ofs;
		ofs.open((".\\������\\" + filePath).data(), ios::ate | ios::_Nocreate);
		// �̾�� �����ϰ� �ϴ� ����
		if (!ofs) {
			ofs.close();
			return false;
		}
		else {
			cout << "������ �Է����ּ���: " << endl;
			getline(cin, evaluation);
			ofs << endl << account->getName() << ": " << evaluation << endl;
			ofs.close();
			return true;
		}
	}

	bool fileLoad(string lectureName) {
		ifstream ifs;
		string line;

		lectureName += " ������.txt";
		ifs.open((".\\������\\" + lectureName).data(), ios::in);

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