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
		//goto xy 함수 -> Windows.h 헤더파일필요
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
			cout << "강의명을 입력해주세요: ";
			cin >> subName;
			cin.ignore();

			system("cls");
			this->cursorView(0);
			if (SubjectPlanFile.fileLoad(subName)) {
				cout << "▶   강의계획서 메뉴로 가기";
				do {
					ch = _getch();
				} while (ch != '\r');
				system("cls");
				break;
			}
			else {
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "강의계획서가 존재하지 않습니다." << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	다시입력" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	강의계획서 메뉴로 가기" << endl;
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
				cout << "      강의계획서     " << endl;
				gotoXY(64, startY + sizeOfHeight * 2);
				cout << "=========================================================================================================";
				gotoXY(startX, startY + sizeOfHeight * 3);
				cout << "   1.강의계획서 보기 " << endl;
				gotoXY(startX, startY + sizeOfHeight * 4);
				cout << "   2.메인으로 이동   " << endl;
				gotoXY(64, startY + sizeOfHeight * 5);
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
						if (y != 1) {
							y++;
						}
						break;
					default:
						break;
					}
				}
				system("cls"); // 반복문에 앞선 결과를 지워주는 함수 

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