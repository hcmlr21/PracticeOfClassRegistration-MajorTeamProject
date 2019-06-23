#pragma once
#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>
#include<windows.h>
#include<time.h>
#include"Subject.h"
#include"TimeTable.h"
#include"Menu.h"
#include "SubjectListFile.h"

using namespace std;

class registerSubject {
private:
	SubjectListFile listfile;
	TimeTable* timetable;
	double start;
	static Subject list[55];
	double time;
	string result;
	int inputLimit;
	int inputNum;

public:
   registerSubject() {
	   inputNum = 0;
	   time = 0;
	   result = "                               ";
	   inputLimit = 0;
	   listfile.subjectlistLoad(list);
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

   void gotoXY(int x, int y) {
	   COORD Cur;
	   Cur.X = x;
	   Cur.Y = y;
	   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
   }

   int drawStroke(int x, int y, int cursorX) {
	   int returnNum = 0;
      for (int i = 5; i < 41; i++) {

		 gotoXY(20, i);
		 time = clock() - start;
         if (i == 5 || i == 40) { cout << "-------------------------------------------------------------------------------------------"; }
         else {
            cout << "|";
         
			if (i == 7) { cout << "       ================================������û===================================="; }
			else if (i == 8) {
				cout << "	��ȣ�� �Է��ϼ��� :				�����ϱ�" << "              ";
				gotoXY(47, 8);
				if (inputNum == 0) {
					cout << (char)inputNum;
				}
				else {
					cout << inputNum;
				}			
			} 
			else if (i == 9) { cout << "list limit :" << inputLimit; }
			else if (i == 10) { cout << "time :" << time; }
			else if (i == 11) { cout << "result :" << result; }
			else if (i == 12) {
				SubjectFile subjectFile;
				Subject subject;
				int j = 0;
				int* s = this->timetable->getList();
				cout << "	���ǹ�ȣ	����";
				while (s[j] != 0) {
					subject = subjectFile.fileLoad(s[j]);
					gotoXY(20, 13+j);
					cout << "	" << s[j] << "		" << subject.getSubName() << "		�����ϱ�";
					j++;
				}
				returnNum = j;
				gotoXY(20, 15+j);
				cout << "	����" << endl << endl << endl;
				
				this->timetable->show(115, 8);
			}

			gotoXY(110, i);
			cout << "|";
         }
      }

	  gotoXY(cursorX + 21, y);
	  cout << "��";

	  this->cursorView(0);
	  return returnNum;
   }

   Subject search(int inputnum) {

	   for (int i = 0; i < (sizeof(list) / sizeof(Subject)); i++) {
		   if (list[i].getSubNum() == inputnum) { 
			   return list[i]; 
		   }
	   }
	   //����ó��
	   return Subject();

   }

   void save(int inputNum) {
	   Subject temp;
	   
	   time = clock() - start;


	   temp = search(inputNum);
	   inputLimit = temp.getSubLimit();

	   if (inputLimit > time) {
		   if (timetable->add(temp)) {
			   result = "���忡 �����ϼ̽��ϴ�.";
		   }
		   else {
			   result = "�̹� �����ϴ� �����Դϴ�.";
		   }
	   }
	   else if (inputLimit <= time) {
		   if (temp.getSubName() == "") {
			   result = "�������� �ʴ� �����Դϴ�.";
		   }
		   else {
			   result = "���忡 �����߽��ϴ�.";
		   }
	   }

	   this->inputNum = 0;
   }
   
   void remove(int order) {
	   Subject temp;
	   time = clock() - start;
	   int subNum = (this->timetable->getList())[order];
	   temp = search(subNum);
	   if (timetable->remove(temp)) {
		   result = "������ �����ϼ̽��ϴ�.";
	   }
	   else {
		   result = "�������� �ʴ� �����Դϴ� �ٽ� Ȯ���ϼ���";
	   }


   }
   
   void showMenu(Account* account) {
	   int y = 8;
	   int ch;
	   int inputX = 47;
	   int maxNum = 0;
	   int cursorX = 0;

	   //�޸� ��ŷ�� �������� ���ѷ��� ���
	   //1.����ġ���� �� �� ��ɿ� ���� �޼ҵ尡 ����ȴ�
	   //2.�޼ҵ尡 ����ȴ�.
	   //3.����γ� ���� �޴��� ���ư��������� ��� �ݺ��Ѵ�.
	   // �����޴��� ���ư��� ����� ����ġ������ �� �� �ƹ� �͵� �������� �ʰ�
	   //���� while(1)�� �Ǿ��ִ� ���ѷ����� break�� �����ִ� ����� ����ߴ�.
	   while (1) {
		   do {
			   //ȭ��׸���
			    maxNum = this->drawStroke(inputX, y, cursorX);

			   if (y == 8) {
				   gotoXY(inputX, y);
				   cursorView(1);
			   }
			   else {
				   cursorView(0);
			   }
			   
			   ch = getch();
			   if (ch == 224) {
				   ch = getch();
				   switch (ch) {
					   //��
				   case 72:
					   if (cursorX == 0) {
						   if (y != 8) { y--; }
						   if (y == 14 + maxNum) { y = 12 + maxNum; }
						   if (y == 12) { y = 8; }
					   }
					   break;
					   //�Ʒ�
				   case 80:
					   if (cursorX == 0) {
						   if (y != 15 + maxNum) { y++; }
						   if (y == 9) { y = 13; }
						   if (y == 13 + maxNum) { y = maxNum + 15; }
					   }
					   break;
					   //����
				   case 75:
					   if ((y > 9) && (y < (15 + maxNum))) {
						   cursorX = 0;
					   }
					   
					   
					   break;
					   //������
				   case 77:
					   if ((y > 9) && (y < (15 + maxNum))) {
						   cursorX = 30;
					   }
					   break;
				   default:
					   break;
				   }
			   }
			   else if (isdigit(ch) && y == 8 && inputNum < 1000) {
				   int temp = (int)(ch - '0');
				   inputNum = inputNum * 10 + temp;
				   inputX++;
			   }
			   else if (ch == 8 && y == 8)  {
				   inputNum /= 10;
				   if(inputX != 47) {
					   inputX--; 
				   }
			   }
			   system("cls");

		   } while (ch != '\r');


		   if ( y == 8) {
			   this->save(inputNum);
			   inputX = 47;
		   }
		   else if ((y <= 12 + maxNum) && cursorX == 30) {
			   this->remove(y-13);
			   cursorX = 0;
			   y = 8;
		   }
 
		   //while���� Ż���ϰ� �������� ���� �� �� �ִ�. 
		   if (y == 15 + maxNum ) {
			   AccountFile accountFile;
			   int *temp;
			   temp = timetable->getList();

			   //������û �� ������ ���Ӱ� �����ϱ����� ����.
			   accountFile.fileSave(*((Student*)account));
			   for (int i = 0; i < 10; i++)
			   {
				   accountFile.subjectSave((Student*)account, temp[i]);
			   }
			   system("cls");
			   delete this->timetable;
			   break;
		   }
	   }
   }

   void run(Account* account) {
	   start = clock();//���۽ð� �ޱ�
	   this->timetable = new TimeTable();
	   this->inputNum = 0;
	   this->showMenu(account);
   }
};
Subject registerSubject::list[55];