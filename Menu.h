#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "Student.h"
#include "AccountFile.h"
#include "registerSubject.h"
#include "SubjectPlan.h"
#include "SubjectEvaluation.h"
#include "TimeTable.h"

using namespace std;

class Menu {
private:
	int startX = 108;
	int startY = 20;
	int sizeOfHeight = 4;
	//Student* s;
	void gotoXY(int x, int y) {
		COORD pos = {x, y};
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
	void consoleSize(int x, int y, int width, int height) {
		HWND console = GetConsoleWindow();
		MoveWindow(console, x, y, width, height, TRUE);
	}

public:
	Menu() {
		//s = new Student();
		SetConsoleTitleA("미정이의 수강신청");
		this->consoleSize(-5, 0, 1933, 1165);
	}

	void signUp() {
		AccountFile accountFile;
		Student account;
		string name;
		string id;
		string pw;
		string email;
		int ch;
		int y = 0;
		while (1) {
			gotoXY(64, startY);
			cout << "=========================================================================================================";
			gotoXY(startX + 1, startY + sizeOfHeight * 1);
			cout << "         회원가입        ";
			gotoXY(64, startY + sizeOfHeight * 2);
			cout << "=========================================================================================================";
			gotoXY(startX, startY + sizeOfHeight * 3);
			cout << "이름을 입력해주세요: ";
			cin >> name;
			account.setName(name);
			cin.ignore();
			gotoXY(startX, startY + sizeOfHeight * 4);
			cout << "사용하실 ID를 입력해주세요: ";
			cin >> id;
			account.setId(id);
			cin.ignore();
			gotoXY(startX, startY + sizeOfHeight * 5);
			cout << "사용하실 PW를 입력해주세요: ";
			cin >> pw;
			account.setPW(pw);
			cin.ignore();
			gotoXY(startX, startY + sizeOfHeight * 6);
			cout << "이메일을 입력해주세요: ";
			cin >> email;
			account.setEmail(email);
			cin.ignore();

			if (accountFile.checkIdExistance(account)) {
				//가입 실패
				system("cls");
				cursorView(0);
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "이미 존재하는 ID입니다.";
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	다시입력";
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	메인으로 가기";
					//gotoXY(0, y + 1);
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "▶";

					ch = getch();
					if (ch == 224) {
						ch = getch();
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
				case 0:
					break;
				case 1:
					break;
				}

				if (y == 1) {
					break;
				}
			}
			else {
				//가입 성공
				accountFile.fileSave(account);
				
				system("cls");
				cursorView(0);
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "축하합니다! 회원가입에 성공하였습니다.";
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	LogIn";
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	메인으로 가기";
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "▶";

					ch = getch();
					if (ch == 224) {
						ch = getch();
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
				case 0:
					this->logIn();
					break;
				case 1:
					break;
				}

				break;
			}			
		}
	}

	void logIn() {
		AccountFile accountFile;
		Account * account;
		string id;
		string pw;
		int ch;
		int y = 0;

		while (1) {

			gotoXY(64, startY);
			cout << "=========================================================================================================";
			gotoXY(startX + 1, startY + sizeOfHeight * 1);
			cout << "         로그인          " << endl;
			gotoXY(64, startY + sizeOfHeight * 2);
			cout << "=========================================================================================================";
			gotoXY(startX, startY + sizeOfHeight * 3);
			cout << "회원님의 ID를 입력해주세요: ";
			cin >> id;
			cin.ignore();
			gotoXY(startX, startY + sizeOfHeight * 4);
			cout << "회원님의 PW를 입력해주세요: ";
			cin >> pw;
			account = accountFile.fileLoad(id);
			cin.ignore();

			if (account == NULL) {
				//아이디가 없는 경우
				system("cls");
				do
				{
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "ID가 없습니다." << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	다시입력" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	메인으로 가기" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "▶";

					ch = getch();
					if (ch == 224) {
						ch = getch();
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
				case 0:
					break;
				case 1:
					break;
				}
				if (y == 1) {
					break;
				}
			}
			else if (account->getPW() == pw) {
				//로그인 성공한 경우
				system("cls");
				this->showMenuAfterLogIn(account);
				break;
			}
			else {
				system("cls");
				do
				{
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "ID 또는 PW가 일치하지 않습니다" << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	다시입력" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	메인으로 가기" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "▶";

					ch = getch();
					if (ch == 224) {
						ch = getch();
						switch (ch) {
						case 72:
							if (y != 0) {
								y--;
							}
							break;
						case 80:
							if (y != 3) {
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
				case 0:
					break;
				case 1:
					break;
				}
				if (y == 1) {
					break;
				}
			}
		}
	}

	void findId() {
		AccountFile accountFile;
		string name;
		string id;
		string email;
		int ch;
		int y = 0;
		
		while (1) {
			gotoXY(64, startY);
			cout << "=========================================================================================================";
			gotoXY(startX + 1, startY + sizeOfHeight * 1);
			cout << "         ID 찾기         ";
			gotoXY(64, startY + sizeOfHeight * 2);
			cout << "=========================================================================================================";
			gotoXY(startX, startY + sizeOfHeight * 3);
			cout << "회원님의 이름을 입력해주세요: " ;
			cin >> name;
			cin.ignore();
			gotoXY(startX, startY + sizeOfHeight * 4);
			cout << "회원님의 Email을 입력해주세요: ";
			cin >> email;
			cin.ignore();

			id = accountFile.findId(name, email);
			if (id !=" ") {
				system("cls");
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "회원님의 ID는 "<< "\'" << id << "\'" << "로 확인 되었습니다." << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	메인으로 가기" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "▶";

					ch = getch();
					if (ch == 224) {
						ch = getch();
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
				case 0:
					break;
				}
				if (y == 0) {
					break;
				}
			}
			else {
				system("cls");
				do
				{
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "ID를 찾을 수 없습니다." ;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	다시입력" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	메인으로 가기" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "▶";

					ch = getch();
					if (ch == 224) {
						ch = getch();
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
				case 0:
					break;
				case 1:
					break;
				default: 
					break;
				}
				if (y == 1) {
					break;
				}
			}
		}
		
	}

	void findPw() {
		Account * account;
		AccountFile accountFile;
		string id;
		string email;
		int ch;
		int y = 0;
		while (1) {
			gotoXY(64, startY);
			cout << "=========================================================================================================";
			gotoXY(startX + 1, startY + sizeOfHeight * 1);
			cout << "         PW 찾기         " << endl;
			gotoXY(64, startY + sizeOfHeight * 2);
			cout << "=========================================================================================================";
			gotoXY(startX, startY + sizeOfHeight * 3);
			cout << "회원님의 ID을 입력해주세요: " ;
			cin >> id;
			cin.ignore();
			gotoXY(startX, startY + sizeOfHeight * 4);
			cout << "회원님의 Email을 입력해주세요: ";
			cin >> email;
			account = accountFile.fileLoad(id);
			cin.ignore();

			if (account != NULL && account->getEmail() == email) {
				//성공, ID가 있고 email도 맞는 경우
				system("cls");
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "회원님의 PW는 " << "\'" << account->getPW() << "\'" << "(으)로 확인 되었습니다" << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	메인으로 가기" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "▶";

					ch = getch();
					if (ch == 224) {
						ch = getch();
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
				case 0:
					break;
				}
				if (y == 0) {
					break;
				}
			}
			else {
				//ID 가 없거나 email이 틀린경우
				system("cls");
				do
				{
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "PW를 찾을 수 없습니다." << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	다시입력" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	메인으로 가기" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "▶";

					ch = getch();
					if (ch == 224) {
						ch = getch();
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
				case 0:
					break;
				case 1:
					break;
				}
				if (y == 1) {
					break;
				}
			}
		}
		
	}

	void showMenu() {
		while (1) {
			int y = 0;
			int ch;
			
			do {
				this->cursorView(0);

				gotoXY(64, startY);
				cout << "=========================================================================================================";
				gotoXY(startX + 1, startY + sizeOfHeight*1);
				cout << "모의수강신청프로그램  " ;
				gotoXY(64, startY + sizeOfHeight*2);
				cout << "=========================================================================================================";
				gotoXY(startX, startY + sizeOfHeight * 3);
				cout << "	1. 회원가입        ";
				gotoXY(startX, startY + sizeOfHeight * 4);
				cout << "	2. 로그인          ";
				gotoXY(startX, startY + sizeOfHeight * 5);
				cout << "	3. 아이디찾기      ";
				gotoXY(startX, startY + sizeOfHeight * 6);
				cout << "	4. 비밀번호찾기    ";
				gotoXY(startX, startY + sizeOfHeight * 7);
				cout << "	5. 종료" << endl;
				gotoXY(64, startY + sizeOfHeight * 8);
				cout << "=========================================================================================================";
				gotoXY(startX , startY + sizeOfHeight * (y + 3));
				cout << "▶";

				ch = getch();
				if (ch == 224) {
					ch = getch();
					switch (ch) {
					case 72:
						if (y != 0) {
							y--;
						}
						break;
					case 80:
						if (y != 4) {
							y++;
						}
						break;
					default:
						break;
					}
				}
				system("cls");

			} while (ch != '\r');
			this->cursorView(1);
			
			switch (y) {
			case 0: this->signUp(); break;
			case 1: this->logIn(); break;
			case 2: this->findId(); break;
			case 3: this->findPw(); break;
			case 4: exit(0); break;
			default: break;
			}
		}
	}

	void showMenuAfterLogIn(Account* account) {
		while (1) {
			registerSubject registerClass;
			SubjectPlan subjectPlan;
			SubjectEvaluation subjectEvaluation;
			TimeTable timeTable;
			int y = 0;
			int ch;

			do {
				this->cursorView(0);
				gotoXY(64, startY);
				cout << "=========================================================================================================";
				gotoXY(startX + 1, startY + sizeOfHeight * 1);
				cout << "모의수강신청프로그램  " << endl;
				gotoXY(64, startY + sizeOfHeight * 2);
				cout << "=========================================================================================================";
				gotoXY(startX, startY + sizeOfHeight * 3);
				cout << "	1. 수강신청        " << endl;
				gotoXY(startX, startY + sizeOfHeight * 4);
				cout << "	2. 강의계획서          " << endl;
				gotoXY(startX, startY + sizeOfHeight * 5);
				cout << "	3. 강의평가      " << endl;
				gotoXY(startX, startY + sizeOfHeight * 6);
				cout << "	4. 수강신청결과    " << endl;
				gotoXY(startX, startY + sizeOfHeight * 7);
				cout << "	5. 로그아웃		" << endl;
				gotoXY(startX, startY + sizeOfHeight * 8);
				cout << "	6. 종료" << endl;
				gotoXY(64, startY + sizeOfHeight * 9);
				cout << "=========================================================================================================";
				gotoXY(startX, startY + sizeOfHeight * (y + 3));
				cout << "▶";

				ch = getch();
				if (ch == 224) {
					ch = getch();
					switch (ch) {
					case 72:
						if (y != 0) {
							y--;
						}
						break;
					case 80:
						if (y != 5) {
							y++;
						}
						break;
					default:
						break;
					}
				}
				system("cls");

			} while (ch != '\r');

			
			//로그인 후의 기능들을 불러오는 것이기 때문에 account를 파라미터로 받고 각 계정에 정보를 저장해야 한다.
			switch (y) {
				//수강신청
			case 0: registerClass.run(account); break;
				//강의 계획서
			case 1: subjectPlan.run(); break;
				//강의평가
			case 2: subjectEvaluation.run(account); break;
				//시간표 결과보기
			case 3: timeTable.run(100, 20, account); break;
				//로그아웃
			case 4: break;
				//종료
			case 5: exit(0); break;
			default: break;
			}

			if (y == 4) {
				break;
			}
		}
	}
	
	void run() {
		this->showMenu();
	}
};
