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

   void cursorView(char show)//커서숨기기
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
         
			if (i == 7) { cout << "       ================================수강신청===================================="; }
			else if (i == 8) {
				cout << "	번호를 입력하세요 :				저장하기" << "              ";
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
				cout << "	강의번호	강의";
				while (s[j] != 0) {
					subject = subjectFile.fileLoad(s[j]);
					gotoXY(20, 13+j);
					cout << "	" << s[j] << "		" << subject.getSubName() << "		삭제하기";
					j++;
				}
				returnNum = j;
				gotoXY(20, 15+j);
				cout << "	종료" << endl << endl << endl;
				
				this->timetable->show(115, 8);
			}

			gotoXY(110, i);
			cout << "|";
         }
      }

	  gotoXY(cursorX + 21, y);
	  cout << "▶";

	  this->cursorView(0);
	  return returnNum;
   }

   Subject search(int inputnum) {

	   for (int i = 0; i < (sizeof(list) / sizeof(Subject)); i++) {
		   if (list[i].getSubNum() == inputnum) { 
			   return list[i]; 
		   }
	   }
	   //예외처리
	   return Subject();

   }

   void save(int inputNum) {
	   Subject temp;
	   
	   time = clock() - start;


	   temp = search(inputNum);
	   inputLimit = temp.getSubLimit();

	   if (inputLimit > time) {
		   if (timetable->add(temp)) {
			   result = "저장에 성공하셨습니다.";
		   }
		   else {
			   result = "이미 존재하는 강의입니다.";
		   }
	   }
	   else if (inputLimit <= time) {
		   if (temp.getSubName() == "") {
			   result = "존재하지 않는 강의입니다.";
		   }
		   else {
			   result = "저장에 실패했습니다.";
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
		   result = "삭제에 성공하셨습니다.";
	   }
	   else {
		   result = "존재하지 않는 과목입니다 다시 확인하세요";
	   }


   }
   
   void showMenu(Account* account) {
	   int y = 8;
	   int ch;
	   int inputX = 47;
	   int maxNum = 0;
	   int cursorX = 0;

	   //메모리 리킹을 막기위해 무한루프 사용
	   //1.스위치문에 들어간 후 기능에 따른 메소드가 실행된다
	   //2.메소드가 종료된다.
	   //3.종료로나 이전 메뉴로 돌아가기전까지 계속 반복한다.
	   // 이전메뉴로 돌아가는 방법은 스위치문으로 들어간 후 아무 것도 실행하지 않고
	   //현재 while(1)로 되어있는 무한루프를 break로 끊어주는 방식을 사용했다.
	   while (1) {
		   do {
			   //화면그리기
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
					   //위
				   case 72:
					   if (cursorX == 0) {
						   if (y != 8) { y--; }
						   if (y == 14 + maxNum) { y = 12 + maxNum; }
						   if (y == 12) { y = 8; }
					   }
					   break;
					   //아래
				   case 80:
					   if (cursorX == 0) {
						   if (y != 15 + maxNum) { y++; }
						   if (y == 9) { y = 13; }
						   if (y == 13 + maxNum) { y = maxNum + 15; }
					   }
					   break;
					   //왼쪽
				   case 75:
					   if ((y > 9) && (y < (15 + maxNum))) {
						   cursorX = 0;
					   }
					   
					   
					   break;
					   //오른쪽
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
 
		   //while문을 탈출하고 현재기능을 종료 할 수 있다. 
		   if (y == 15 + maxNum ) {
			   AccountFile accountFile;
			   int *temp;
			   temp = timetable->getList();

			   //수강신청 할 때마다 새롭게 갱신하기위한 문장.
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
	   start = clock();//시작시간 받기
	   this->timetable = new TimeTable();
	   this->inputNum = 0;
	   this->showMenu(account);
   }
};
Subject registerSubject::list[55];