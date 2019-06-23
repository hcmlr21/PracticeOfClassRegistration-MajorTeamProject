#pragma once
#include "FileManager.h"
#include "Student.h"
#include "Administrator.h"
#include <string>
using namespace std;

//FileMager �ڽ�Ŭ����, ���� ���� �����
class AccountFile : public FileManager {
public:
	AccountFile() {

	}

	void fileSave(Student student) {
		ofstream ofs;
		ofstream ofs2;

		string id;
		string email;
		bool exist = false;
		string fileName = student.getId() + ".txt";
		string studentListFile = ".\\����\\accountList.txt";

		
		ofs.open((".\\����\\" + fileName).data());
		

		if (exist) {
			ofs.close();
		}
		else {
			if (!ofs) {
				cout << "�л������� ������ �� �����ϴ�." << endl;
				ofs.close();
				exit(0);
			}
			else {
				ofs << student.getId() << " " << student.getPW() << " " << student.getName() << " " << student.getEmail() << " " << student.getAccountGrade() << endl;

				ofs2.open(studentListFile.data(), ios::app);
				if (!ofs) {
					ofs2.close();
				}
				else {
					ofs2 << student.getName() << " " << student.getId() << " " << student.getEmail() << endl;
				}
				ofs2.close();
			}
			ofs.close();
		}
	}

	void fileSave(Administrator admin) {
		ofstream ofs;
		string fileName = admin.getName() + ".txt";
		ofs.open((".\\����\\" + fileName).data());
		if (!ofs) {
			cout << "������������ ������ �� �����ϴ�." << endl;
			exit(0);
		}
		ofs << admin.getId() << " " << admin.getPW() << " " << admin.getName() << " " << admin.getEmail() << " " << admin.getAccountGrade() << endl;

		ofs.close();
	}
	bool checkIdExistance(Student student) {
		ifstream ifs;
		string id;
		string email;
		string name;
		string studentListFile = ".\\����\\accountList.txt";
		ifs.open(studentListFile.data());

		if (!ifs) {
		}
		else {
			while (ifs >> name >> id >> email) {
				if (id == student.getId()) {
					ifs.close();
					return true;
				}
			}
		}
		ifs.close();
		return false;
	}

	string findId(string name, string email) {
		ifstream ifs;
		string studentListFile = ".\\����\\accountList.txt";
		ifs.open(studentListFile.data());
		string id;
		string n;
		string e;

		if (!ifs) {
		}
		else {
			while (ifs >> n >> id >> e) {
				if ((name == n) && (email == e)) {
					return id;
				}
			}
			ifs.close();
		}
		return " ";
	}

	//������û�� �Ҷ����� �������ǰ� �ʱ�ȭ�Ǿ� ����.

	void subjectSaveAfterReset(Student* student, int subjectNum) {
		this->fileSave(*student);
		this->subjectSave(student, subjectNum);
	}

	void subjectSave(Student* student, int subjectNum) {
		string filePath = student->getName() + ".txt";
		// write File
		string chekSubject;
		//�̹� ������ ������ true ������ false;
		bool check = false;
		ofstream ofs;
		ifstream ifs;
		ofs.open((".\\����\\" + filePath).data(), ios::app);
		ifs.open((".\\����\\" + filePath).data());
		// ios::app �̾�� �����ϰ� �ϴ� ����
		if (!ofs) {
			cout << "������ �� �� �����ϴ�" << endl;
			exit(0);
		}
		else {
			while (ifs >> chekSubject) {
				if (chekSubject == to_string(subjectNum)) {
					check = true;
				}
			}
			if (check) {
			}
			else {
				ofs << subjectNum << " ";
			}
		}
		ofs.close();
	}

	int* subjectLoad(string studentId) {
		ifstream ifs;
		string subjectNum;
		int* subjects= new int[10];
		int count = -1;
		string name;
		string id;
		string pw;
		string email;
		int accountGrade;
		studentId += ".txt";
		ifs.open((".\\����\\" + studentId).data());
		if (!ifs) {
			cout << "������ �� �� �����ϴ�.";
			
		}
		else {
			if (ifs >> id >> pw >> name >> email >> accountGrade) {
				// ȸ�� ���� �ڿ� ����� ���� �̸��� �޾ƿ������� ifs�� ȸ�������� �޾� ���������.
			}
			while (ifs >> subjectNum) {
				count++;
				subjects[count] = atoi(subjectNum.c_str());
				subjectNum.clear();

			}
		}
		ifs.close();
		return subjects;
	}

	Account* fileLoad(string fileId) {
		ifstream ifs;
		Account* account;
		string name;
		string id;
		string pw;
		string email;
		int accountGrade;
		fileId += ".txt";
		ifs.open((".\\����\\" + fileId).data());
		if (!ifs) {
			ifs.close();
			return NULL;
		}
		else {
			while (ifs >> id >> pw >> name >> email >> accountGrade) {
				if (accountGrade == 0) {
					//�������϶�
					account = new Administrator(name, id, pw, email);
				}
				else if (accountGrade == 1) {
					//�л��϶�
					account = new Student(name, id, pw, email);
				}
			}
			ifs.close();
			return account;
		}
	}
};