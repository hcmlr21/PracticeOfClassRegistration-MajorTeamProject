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

	void cursorView(char show)//Ŀ�������
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
		SetConsoleTitleA("�������� ������û");
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
			cout << "         ȸ������        ";
			gotoXY(64, startY + sizeOfHeight * 2);
			cout << "=========================================================================================================";
			gotoXY(startX, startY + sizeOfHeight * 3);
			cout << "�̸��� �Է����ּ���: ";
			cin >> name;
			account.setName(name);
			cin.ignore();
			gotoXY(startX, startY + sizeOfHeight * 4);
			cout << "����Ͻ� ID�� �Է����ּ���: ";
			cin >> id;
			account.setId(id);
			cin.ignore();
			gotoXY(startX, startY + sizeOfHeight * 5);
			cout << "����Ͻ� PW�� �Է����ּ���: ";
			cin >> pw;
			account.setPW(pw);
			cin.ignore();
			gotoXY(startX, startY + sizeOfHeight * 6);
			cout << "�̸����� �Է����ּ���: ";
			cin >> email;
			account.setEmail(email);
			cin.ignore();

			if (accountFile.checkIdExistance(account)) {
				//���� ����
				system("cls");
				cursorView(0);
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "�̹� �����ϴ� ID�Դϴ�.";
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	�ٽ��Է�";
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	�������� ����";
					//gotoXY(0, y + 1);
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "��";

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
				//���� ����
				accountFile.fileSave(account);
				
				system("cls");
				cursorView(0);
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "�����մϴ�! ȸ�����Կ� �����Ͽ����ϴ�.";
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	LogIn";
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	�������� ����";
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "��";

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
			cout << "         �α���          " << endl;
			gotoXY(64, startY + sizeOfHeight * 2);
			cout << "=========================================================================================================";
			gotoXY(startX, startY + sizeOfHeight * 3);
			cout << "ȸ������ ID�� �Է����ּ���: ";
			cin >> id;
			cin.ignore();
			gotoXY(startX, startY + sizeOfHeight * 4);
			cout << "ȸ������ PW�� �Է����ּ���: ";
			cin >> pw;
			account = accountFile.fileLoad(id);
			cin.ignore();

			if (account == NULL) {
				//���̵� ���� ���
				system("cls");
				do
				{
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "ID�� �����ϴ�." << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	�ٽ��Է�" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	�������� ����" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "��";

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
				//�α��� ������ ���
				system("cls");
				this->showMenuAfterLogIn(account);
				break;
			}
			else {
				system("cls");
				do
				{
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "ID �Ǵ� PW�� ��ġ���� �ʽ��ϴ�" << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	�ٽ��Է�" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	�������� ����" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "��";

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
			cout << "         ID ã��         ";
			gotoXY(64, startY + sizeOfHeight * 2);
			cout << "=========================================================================================================";
			gotoXY(startX, startY + sizeOfHeight * 3);
			cout << "ȸ������ �̸��� �Է����ּ���: " ;
			cin >> name;
			cin.ignore();
			gotoXY(startX, startY + sizeOfHeight * 4);
			cout << "ȸ������ Email�� �Է����ּ���: ";
			cin >> email;
			cin.ignore();

			id = accountFile.findId(name, email);
			if (id !=" ") {
				system("cls");
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "ȸ������ ID�� "<< "\'" << id << "\'" << "�� Ȯ�� �Ǿ����ϴ�." << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	�������� ����" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "��";

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
					cout << "ID�� ã�� �� �����ϴ�." ;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	�ٽ��Է�" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	�������� ����" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "��";

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
			cout << "         PW ã��         " << endl;
			gotoXY(64, startY + sizeOfHeight * 2);
			cout << "=========================================================================================================";
			gotoXY(startX, startY + sizeOfHeight * 3);
			cout << "ȸ������ ID�� �Է����ּ���: " ;
			cin >> id;
			cin.ignore();
			gotoXY(startX, startY + sizeOfHeight * 4);
			cout << "ȸ������ Email�� �Է����ּ���: ";
			cin >> email;
			account = accountFile.fileLoad(id);
			cin.ignore();

			if (account != NULL && account->getEmail() == email) {
				//����, ID�� �ְ� email�� �´� ���
				system("cls");
				do {
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "ȸ������ PW�� " << "\'" << account->getPW() << "\'" << "(��)�� Ȯ�� �Ǿ����ϴ�" << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	�������� ����" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "��";

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
				//ID �� ���ų� email�� Ʋ�����
				system("cls");
				do
				{
					gotoXY(startX, startY + sizeOfHeight * 0);
					cout << "PW�� ã�� �� �����ϴ�." << endl;
					gotoXY(startX, startY + sizeOfHeight * 1);
					cout << "	�ٽ��Է�" << endl;
					gotoXY(startX, startY + sizeOfHeight * 2);
					cout << "	�������� ����" << endl;
					gotoXY(startX, startY + sizeOfHeight * (y + 1));
					cout << "��";

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
				cout << "���Ǽ�����û���α׷�  " ;
				gotoXY(64, startY + sizeOfHeight*2);
				cout << "=========================================================================================================";
				gotoXY(startX, startY + sizeOfHeight * 3);
				cout << "	1. ȸ������        ";
				gotoXY(startX, startY + sizeOfHeight * 4);
				cout << "	2. �α���          ";
				gotoXY(startX, startY + sizeOfHeight * 5);
				cout << "	3. ���̵�ã��      ";
				gotoXY(startX, startY + sizeOfHeight * 6);
				cout << "	4. ��й�ȣã��    ";
				gotoXY(startX, startY + sizeOfHeight * 7);
				cout << "	5. ����" << endl;
				gotoXY(64, startY + sizeOfHeight * 8);
				cout << "=========================================================================================================";
				gotoXY(startX , startY + sizeOfHeight * (y + 3));
				cout << "��";

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
				cout << "���Ǽ�����û���α׷�  " << endl;
				gotoXY(64, startY + sizeOfHeight * 2);
				cout << "=========================================================================================================";
				gotoXY(startX, startY + sizeOfHeight * 3);
				cout << "	1. ������û        " << endl;
				gotoXY(startX, startY + sizeOfHeight * 4);
				cout << "	2. ���ǰ�ȹ��          " << endl;
				gotoXY(startX, startY + sizeOfHeight * 5);
				cout << "	3. ������      " << endl;
				gotoXY(startX, startY + sizeOfHeight * 6);
				cout << "	4. ������û���    " << endl;
				gotoXY(startX, startY + sizeOfHeight * 7);
				cout << "	5. �α׾ƿ�		" << endl;
				gotoXY(startX, startY + sizeOfHeight * 8);
				cout << "	6. ����" << endl;
				gotoXY(64, startY + sizeOfHeight * 9);
				cout << "=========================================================================================================";
				gotoXY(startX, startY + sizeOfHeight * (y + 3));
				cout << "��";

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

			
			//�α��� ���� ��ɵ��� �ҷ����� ���̱� ������ account�� �Ķ���ͷ� �ް� �� ������ ������ �����ؾ� �Ѵ�.
			switch (y) {
				//������û
			case 0: registerClass.run(account); break;
				//���� ��ȹ��
			case 1: subjectPlan.run(); break;
				//������
			case 2: subjectEvaluation.run(account); break;
				//�ð�ǥ �������
			case 3: timeTable.run(100, 20, account); break;
				//�α׾ƿ�
			case 4: break;
				//����
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
