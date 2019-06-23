#pragma once
#include "FileManager.h"
#include "Student.h"
#include "Administrator.h"
#include <string>
using namespace std;

//FileMager 자식클래스, 계정 파일 입출력
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
		string studentListFile = ".\\계정\\accountList.txt";

		
		ofs.open((".\\계정\\" + fileName).data());
		

		if (exist) {
			ofs.close();
		}
		else {
			if (!ofs) {
				cout << "학생정보를 저장할 수 없습니다." << endl;
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
		ofs.open((".\\계정\\" + fileName).data());
		if (!ofs) {
			cout << "관리자정보를 저장할 수 없습니다." << endl;
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
		string studentListFile = ".\\계정\\accountList.txt";
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
		string studentListFile = ".\\계정\\accountList.txt";
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

	//수강신청시 할때마다 수강강의가 초기화되어 저장.

	void subjectSaveAfterReset(Student* student, int subjectNum) {
		this->fileSave(*student);
		this->subjectSave(student, subjectNum);
	}

	void subjectSave(Student* student, int subjectNum) {
		string filePath = student->getName() + ".txt";
		// write File
		string chekSubject;
		//이미 과목이 있으면 true 없으면 false;
		bool check = false;
		ofstream ofs;
		ifstream ifs;
		ofs.open((".\\계정\\" + filePath).data(), ios::app);
		ifs.open((".\\계정\\" + filePath).data());
		// ios::app 이어쓰기 가능하게 하는 역할
		if (!ofs) {
			cout << "파일을 열 수 없습니다" << endl;
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
		ifs.open((".\\계정\\" + studentId).data());
		if (!ifs) {
			cout << "파일을 열 수 없습니다.";
			
		}
		else {
			if (ifs >> id >> pw >> name >> email >> accountGrade) {
				// 회원 정보 뒤에 저장된 과목 이름을 받아오기위해 ifs로 회원정보를 받아 흘려버린다.
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
		ifs.open((".\\계정\\" + fileId).data());
		if (!ifs) {
			ifs.close();
			return NULL;
		}
		else {
			while (ifs >> id >> pw >> name >> email >> accountGrade) {
				if (accountGrade == 0) {
					//관리자일때
					account = new Administrator(name, id, pw, email);
				}
				else if (accountGrade == 1) {
					//학생일때
					account = new Student(name, id, pw, email);
				}
			}
			ifs.close();
			return account;
		}
	}
};