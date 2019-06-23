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

	void cursorView(char show)//커서숨기기
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
				cout << "	강의평가" << endl;
				gotoXY(64, startY + sizeOfHeight * 2);
				cout << "=========================================================================================================";
				gotoXY(startX, startY + sizeOfHeight * 3);
				cout << "   1. 평가하기       " << endl;
				gotoXY(startX, startY + sizeOfHeight * 4);
				cout << "   2. 강의평보기     " << endl;
				gotoXY(startX, startY + sizeOfHeight * 5);
				cout << "   3. 메인으로 이동  " << endl;
				gotoXY(64, startY + sizeOfHeight * 6);
				cout << "=========================================================================================================";
				gotoXY(startX, startY + sizeOfHeight * (y + 3));
				cout << "▶";


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
			cout << "평가하실 강의명을 입력해주세요: ";
			cin >> subName;
			cin.ignore();
			system("cls");

			this->cursorView(0);
			if (subjectEvaluating.fileSave(account, subName)) {
				system("cls");
				gotoXY(startX, startY + sizeOfHeight * 0);
				cout << "강의평가에 등록되었습니다" << endl;
				gotoXY(startX, startY + sizeOfHeight * 1);
				cout << "▶   강의평가 메뉴로 가기" << endl;
				do {
					ch = _getch();
				} while (ch != '\r');
				system("cls");
				break;
			}
			else {
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "해당강의가 존재하지 않습니다." << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	다시입력" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	강의평가 메뉴로 가기" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "▶";

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
			cout << "강의명을 입력해주세요: ";
			cin >> subName;
			cin.ignore();

			system("cls");
			this->cursorView(0);
			if (subjectEvaluating.fileLoad(subName)) {
				gotoXY(startX, startY + sizeOfHeight * 0);
				cout << "▶   강의평가 메뉴로 가기" << endl;
				do {
					ch = _getch();
				} while (ch != '\r');
				system("cls");
				break;
			} else {
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "해당강의가 존재하지 않습니다." << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	다시입력" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	강의평가 메뉴로 가기" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "▶";

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