#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include "SubjectEvaluatingFile.h"
using namespace std;

class SubjectEvaluation {
private:
	int startX = 108;
	int startY = 20;
	int sizeOfHeight = 4;
	void gotoXY(int x, int y) {
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
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
	SubjectEvaluation() {

	}
	void showSubjectEvaluation(Account* account) {
		int y = 0;
		int ch;
		while (1) {
			this->cursorView(0);
			do {
				gotoXY(64, startY);
				cout << "=========================================================================================================";
				gotoXY(startX + 1, startY + sizeOfHeight * 1);
				cout << "	������" << endl;
				gotoXY(64, startY + sizeOfHeight * 2);
				cout << "=========================================================================================================";
				gotoXY(startX, startY + sizeOfHeight * 3);
				cout << "   1. ���ϱ�       " << endl;
				gotoXY(startX, startY + sizeOfHeight * 4);
				cout << "   2. �����򺸱�     " << endl;
				gotoXY(startX, startY + sizeOfHeight * 5);
				cout << "   3. �������� �̵�  " << endl;
				gotoXY(64, startY + sizeOfHeight * 6);
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
						if (y != 2) {
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
			case 0: this->doSubjectEvaluation(account); break;
			case 1: this->seeSubjectEvaluation(); break;
			case 2: break;
			default: break;
			}
			if (y == 2) {
				break;
			}
		}
	}

	void doSubjectEvaluation(Account* account) {
		SubjectEvaluating subjectEvaluating;
		int ch;
		int y = 0;
		string subName;
		
		while (1) {
			this->cursorView(1);

			gotoXY(startX, startY + sizeOfHeight * 0);
			cout << "���Ͻ� ���Ǹ��� �Է����ּ���: ";
			cin >> subName;
			cin.ignore();
			system("cls");

			this->cursorView(0);
			if (subjectEvaluating.fileSave(account, subName)) {
				system("cls");
				gotoXY(startX, startY + sizeOfHeight * 0);
				cout << "�����򰡿� ��ϵǾ����ϴ�" << endl;
				gotoXY(startX, startY + sizeOfHeight * 1);
				cout << "��   ������ �޴��� ����" << endl;
				do {
					ch = _getch();
				} while (ch != '\r');
				system("cls");
				break;
			}
			else {
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "�ش簭�ǰ� �������� �ʽ��ϴ�." << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	�ٽ��Է�" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	������ �޴��� ����" << endl;
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

	void seeSubjectEvaluation() {
		SubjectEvaluating subjectEvaluating;
		int ch;
		int y = 0;
		string subName;
		
		while (1) {
			this->cursorView(1);
			gotoXY(startX, startY + sizeOfHeight * 0);
			cout << "���Ǹ��� �Է����ּ���: ";
			cin >> subName;
			cin.ignore();

			system("cls");
			this->cursorView(0);
			if (subjectEvaluating.fileLoad(subName)) {
				gotoXY(startX, startY + sizeOfHeight * 0);
				cout << "��   ������ �޴��� ����" << endl;
				do {
					ch = _getch();
				} while (ch != '\r');
				system("cls");
				break;
			} else {
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "�ش簭�ǰ� �������� �ʽ��ϴ�." << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	�ٽ��Է�" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	������ �޴��� ����" << endl;
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

	void run(Account* account) {
		showSubjectEvaluation(account);
	}
};