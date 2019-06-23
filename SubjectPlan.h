#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "SubjectPlanFile.h"

using namespace std;

class SubjectPlan {
private:
	int startX = 108;
	int startY = 20;
	int sizeOfHeight = 4;

	void gotoXY(int x, int y) {
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		//goto xy �Լ� -> Windows.h ��������ʿ�
	}

	void cursorView(char show)//Ŀ�������
	{
		HANDLE hConsole;
		CONSOLE_CURSOR_INFO ConsoleCursor;

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		ConsoleCursor.bVisible = show;
		ConsoleCursor.dwSize = 1;

		SetConsoleCursorInfo(hConsole, &ConsoleCursor);
	}

public:
	SubjectPlan() {

	}
	void seeSubjectPlan() {
		SubjectPlanFile SubjectPlanFile;
		string subName;
		int ch; 
		int y = 0;
		while (1) {
			this->cursorView(1);
			gotoXY(startX, startY + sizeOfHeight * 0);
			cout << "���Ǹ��� �Է����ּ���: ";
			cin >> subName;
			cin.ignore();

			system("cls");
			this->cursorView(0);
			if (SubjectPlanFile.fileLoad(subName)) {
				cout << "��   ���ǰ�ȹ�� �޴��� ����";
				do {
					ch = _getch();
				} while (ch != '\r');
				system("cls");
				break;
			}
			else {
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "���ǰ�ȹ���� �������� �ʽ��ϴ�." << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	�ٽ��Է�" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	���ǰ�ȹ�� �޴��� ����" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
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
							if (y != 1) {
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
				case 0: break;
				case 1: break;
				default: break;
				}

				if (y == 1) {
					break;
				}
			}
		}
	}

	void showSubjectPlan() {
		int y = 0;
		int ch;
		while (1) {
			this->cursorView(0);
			do
			{
				gotoXY(64, startY);
				cout << "=========================================================================================================";
				gotoXY(startX + 1, startY + sizeOfHeight * 1);
				cout << "      ���ǰ�ȹ��     " << endl;
				gotoXY(64, startY + sizeOfHeight * 2);
				cout << "=========================================================================================================";
				gotoXY(startX, startY + sizeOfHeight * 3);
				cout << "   1.���ǰ�ȹ�� ���� " << endl;
				gotoXY(startX, startY + sizeOfHeight * 4);
				cout << "   2.�������� �̵�   " << endl;
				gotoXY(64, startY + sizeOfHeight * 5);
				cout << "=========================================================================================================";
				gotoXY(startX, startY + sizeOfHeight * (y + 3));
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
						if (y != 1) {
							y++;
						}
						break;
					default:
						break;
					}
				}
				system("cls"); // �ݺ����� �ռ� ����� �����ִ� �Լ� 

			} while (ch != '\r');

			switch (y) {
			case 0: this->seeSubjectPlan(); break;
			case 1: break;
			default: break;
			}
			if (y == 1) {
				break;
			}
		}
	}
	void run() {
		this->showSubjectPlan();
	}
};