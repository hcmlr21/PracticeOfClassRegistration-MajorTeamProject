#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include"Subject.h"
#include "SubjectFile.h"
#include "AccountFile.h"
class Student;

using namespace std;

class TimeTable {
private:
	const int numCol = 5; //��(������) : ��ȭ�����
	const int numLow = 18; //��(������) : ����9��~����6��
	int timeTable[5][18]; // TimeTable�⺻�� ũ��
	int addList[10] = { 0 };
	int index = 0;
	
	void gotoXY(int x, int y) {
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
	void timeReset() {
		//2�����迭 �ʱ�ȭ.
		for (int col = 0; col < numCol; col++) {
			for (int low = 0; low < numLow; low++) {
				timeTable[col][low] = 0;
			}
		}
	}
	
public:
	TimeTable() {
		this->timeReset();
	}

	int* getList() {
		return this->addList;
	}

	bool add(Subject sub) {
		int day1;
		int day2;

		//������ �迭���� ����ϱ� ���� ���ڷ� �����ϴ� ����.
		//�ٷ� ���ڸ� ��� �� ���� ������ String���� ��� �ϴ°��� ���� �������̾ ���.
		if (sub.getSubDay() == "Mon") {
			day1 = 0;
		}
		if (sub.getSubDay() == "Tue") {
			day1 = 1;
		}
		if (sub.getSubDay() == "Wed") {
			day1 = 2;
		}
		if (sub.getSubDay() == "Thu") {
			day1 = 3;
		}
		if (sub.getSubDay() == "Fri") {
			day1 = 4;
		}
		if (sub.getSubDay() == "Sat") {
			day1 = 5;
		}
		if (sub.getSubDay() == "Sun") {
			day1 = 6;
		}

		if (sub.getSubDay2() == "Mon") {
			day2 = 0;
		}
		if (sub.getSubDay2() == "Tue") {
			day2 = 1;
		}
		if (sub.getSubDay2() == "Wed") {
			day2 = 2;
		}
		if (sub.getSubDay2() == "Thu") {
			day2 = 3;
		}
		if (sub.getSubDay2() == "Fri") {
			day2 = 4;
		}
		if (sub.getSubDay2() == "Sat") {
			day2 = 5;
		}
		if (sub.getSubDay2() == "Sun") {
			day2 = 6;
		}

		// ��� ������ 0���� �ʱ�ȭ�� �迭�� ������ �ִ� �ð��� 1�� �ٲ��ֱ� ���� ����
		//�� ���� �� ���� ������ �ִ� ���
		if (sub.getSubDay() != "" && sub.getSubDay2() != "") {

			bool occupied = false;

			for (int i = sub.getSubStart(); i <= sub.getSubFinish(); i++) {
				if (this->timeTable[day1][i - 1] == 1) {
					occupied = true;
				}
			}

			for (int i = sub.getSubStart2(); i <= sub.getSubFinish2(); i++) {
				if (this->timeTable[day2][i - 1] == 1) {
					occupied = true;
				}
			}

			if (occupied) {
				return false;
			}
			else {
				for (int i = sub.getSubStart(); i <= sub.getSubFinish(); i++) {
					this->timeTable[day1][i - 1] = 1;
				}

				for (int i = sub.getSubStart2(); i <= sub.getSubFinish2(); i++) {
					this->timeTable[day2][i - 1] = 1;
				}
			}
		//������ �ϳ��� �ִ� ���
		}else if (sub.getSubDay() != "") {
			//�ð�ǥ�� ��ġ�� �κ��� �Ǵ��ϱ����� ����
			bool occupied = false;

			for (int i = sub.getSubStart(); i <= sub.getSubFinish(); i++) {
				if (this->timeTable[day1][i - 1] == 1) {
					occupied = true;
				}
			}

			if (occupied) {
				return false;
			}
			else {
				for (int i = sub.getSubStart(); i <= sub.getSubFinish(); i++) {
					this->timeTable[day1][i - 1] = 1;
				}
			}
			
		}
		//���� ���
		else {
			return false;
		}

		//�ϳ��� �ְ� �� ������ �����ϸ� �����迭�� �߰�
		addList[index] = sub.getSubNum();
		index++;
		return true;
	}

	void show(int startX, int startY) {
		
		gotoXY(startX, startY);
		cout << "  ��ȭ�����" << endl;
		for (int i = 9; i <= 18; i++) {
			int time = i % 12;
			gotoXY(startX, startY + 2 * (i - 9) + 1);
			if (time == 0) {
				time = 12;
				cout << time << endl << endl;
			}
			else if (time < 10) {
				cout << "0" << time << endl << endl;
			}
			else {
				cout << time << endl << endl;
			}
		}

		for (int col = 0; col < numCol; col++) {
			for (int low = 0; low < numLow; low++) {
				gotoXY(startX + 2 * col + 2, startY + low + 1);
				if (timeTable[col][low] == 1) {
					cout << "��"; // �ð�ǥ ����
				}
				else {
					cout << "��"; // �ð�ǥ ����
				}
			}
		}
		
	}

	bool remove(Subject sub) {
		int day1;
		int day2;
		bool exist = false;

		if (sub.getSubDay() == "Mon") {
			day1 = 0;
		}
		if (sub.getSubDay() == "Tue") {
			day1 = 1;
		}
		if (sub.getSubDay() == "Wed") {
			day1 = 2;
		}
		if (sub.getSubDay() == "Thu") {
			day1 = 3;
		}
		if (sub.getSubDay() == "Fri") {
			day1 = 4;
		}
		if (sub.getSubDay() == "Sat") {
			day1 = 5;
		}
		if (sub.getSubDay() == "Sun") {
			day1 = 6;
		}

		if (sub.getSubDay2() == "Mon") {
			day2 = 0;
		}
		if (sub.getSubDay2() == "Tue") {
			day2 = 1;
		}
		if (sub.getSubDay2() == "Wed") {
			day2 = 2;
		}
		if (sub.getSubDay2() == "Thu") {
			day2 = 3;
		}
		if (sub.getSubDay2() == "Fri") {
			day2 = 4;
		}
		if (sub.getSubDay2() == "Sat") {
			day2 = 5;
		}
		if (sub.getSubDay2() == "Sun") {
			day2 = 6;
		}

		if (sub.getSubDay() != "") {
			for (int j = 0; j < 10; j++) {
				if (addList[j] == sub.getSubNum()) {
					for (int i = sub.getSubStart(); i <= sub.getSubFinish(); i++) {
						this->timeTable[day1][i - 1] = 0;
					}

					if (sub.getSubDay2() == "") {
						for (int i = j; i < 9; i++) {
							addList[i] = addList[i + 1];
						}
						index--;
						return true;
					}
					exist = true;
				}
			}
			if (!exist) {
				return false;
			}
		}

		if (sub.getSubDay2() != "") {
			for (int j = 0; j < 10; j++) {
				if (addList[j] == sub.getSubNum()) {
					for (int i = sub.getSubStart2(); i <= sub.getSubFinish2(); i++) {
						this->timeTable[day2][i - 1] = 0;
						addList[j] = 0;
						for (int i = j; i < 9; i++) {
							addList[i] = addList[i + 1];
						}
						index--;
					}
				}
			}
		}

		return true;
	}

	void run(int startX, int startY, Account* account) {
		int ch;
		int y = 0;

		Student* student = ((Student*)account);
		SubjectFile subjectFile;
		AccountFile accountFile;
		int* subjectNums = (accountFile.subjectLoad(student->getId()));
		Subject subject;

		for (int i = 0; i < 10; i++) {
			int subjectNum = subjectNums[i];// �����ȣ
			subject = subjectFile.fileLoad(subjectNum);
			this->add(subject);
		}
		delete[] subjectNums;

		while (1) {
			do {
				this->show(startX, startY);

				cout << endl << endl;;
				gotoXY(startX, startY + y + this->numLow + 2);
				cout << "		�޴��� ����";
				gotoXY(startX, startY + y + this->numLow + 2);
				cout << "��";

				ch = _getch();
				if (ch == 224) {
					ch = _getch();
					switch (ch) {
					case 72:
						if (y != 0) {
							y--;
						}
						break;
					case 80:
						if (y != 0) {
							y++;
						}
						break;
					default:
						break;
					}
				}
				system("cls");

			} while (ch != '\r');

			switch (y) {
			case 0:  break;
			default: break;
			}

			if (y == 0) {
				break;
			}
		}
	}
};