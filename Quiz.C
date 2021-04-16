/*               ====================
CODE OF QUIZ PROGRAM
====================

Q U I Z Program by Mr.K.Chandrasekhar Omkar (kcomkar@gmail.com)
Q.DAT --> Questions Database file
HISCORE.DAT --> High scorer's file
USER.DAT --> Stores user id's ans passwords

FUNCTIONS USED :-
==============
 addq() --> The function which adds questions to the database
 delq() --> The function which deletes questions from the database
 modq() --> The function which modifies questions in the database
 viewrec(int id,int i) --> This function displays a record of ID number
			   "id". If i==1 it displays the record with answer
 viewrec1(struct question *,int a) --> This function displays a record with call
				   be reference method with answer if a=1
 test1() --> This function displays menu of Manipulating Records
 viewmenu() --> This function displays menu for Viewing Records
 reg1() --> This function registers a username
 login() --> This function logins a user into the game


Question structure :
==================
1. ques[] --> STRING VARIABLE WHICH STORES THE QUESTION
2. id     --> INTEGER VARIABLE WHICH STORES THE QUESTION ID
3. op1[]  --> OPTION VARIABLE 1 (STRING)
4. op2[]  --> OPTION VARIABLE 2 (STRING)
5. op3[]  --> OPTION VARIABLE 3 (STRING)
6. op4[]  --> OPTION VARIABLE 4 (STRING)
7. ans    --> INTEGER VARIABLE WHICH STORES THE ANSWER

   "q" IS THE QUESTION STRUCTURE VARIABLE
	Another sturcture variable "t1" is also declared for temporary
	access.
	This structure is declared globally



User structure :-
==============

name[]      --> NAME OF THE USER (STRING)
id[]        --> THIS IS A UNIQUE ID WITH WHICH THE USER ACCESSES HIS/HER
		ACCOUNT. (STRING)
password[]  --> THIS IS LIKE A KEY FOR A USER TO ACCESS HIS ACCOUNT (STRING)
log         --> THIS STORES THE NUMBER OF TIMES THE USER ACCESSED HIS/HER
		ACCOUNT. (INTEGER)

	 "usr" IS THE USER STRUCTURE VARIABLE
	  This structute is decalred globally




Accessing of Files :
==================
TWO FILES ARE USED IN THE PROGRAM. THEY ARE:-
1.  Q.DAT       -->  THE FILE WHICH STORES THE QUESTIONS DATABASE
			 This file is accessed using the file pointer "q"

2. HISCORES.DAT -->  THE FILE WHICH STORES THE WINNERS OF THE QUIZ
			 This file is accessed using the file pointer "h"

3. USER.DAT     -->  THIS FILE STORES THE REGISTERED USERS DETAILS
Both these file pointers are declared globally. Both these files are
opened in APPENDED BINARY READ/WRITE mode (ab+) at the beginning of the program
and are closed finally at the end of the program. Remember, file opening
and closing are done only once in the program to avoid confusion.



CODE BEGINS HERE :-
================                                          			 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <process.h>

FILE* q, * h, * idd;
FILE* reg, * log1;

struct question {         /* Structure Question */
	char ques[200];
	int id;
	char op1[200];
	char op2[200];
	char op3[200];
	char op4[200];
	char ans;
} qe, t1;

struct user {
	char name[100];
	char id[100];
	char password[100];
	int log;
} usr;

void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}

void clrscr(void)
{
	/***
	*   Use "cls" for Microsoft Windows
	*   Use "clear" for Linux
	***/
	system("cls");
}

/***** getch and getche *****/

//static struct termios old, new1;

/* Initialize new terminal i/o settings */
//void initTermios(int echo)
//{
//  tcgetattr(0, &old); //grab old terminal i/o settings
//  new1 = old; //make new settings same as old settings
//  new1.c_lflag &= ~ICANON; //disable buffered i/o
//  new1.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
//  tcsetattr(0, TCSANOW, &new1); //apply terminal io settings
//}

/* Restore old terminal i/o settings */
//void resetTermios(void)
//{
//  tcsetattr(0, TCSANOW, &old);
//}

/* Read 1 character - echo defines echo mode */
//char getch_(int echo)
//{
//  char ch;
//  initTermios(echo);
//  ch = getchar();
//  resetTermios();
//  return ch;
//}

/*
Read 1 character without echo
getch() function definition.
*/
//char getch(void)
//{
//  return getch_(0);
//}

/*
Read 1 character with echo
getche() function definition.
*/
//char getche(void)
//{
//  return getch_(1);
//}

/****************************/


addq() {
	char ch, an = 'Y';
	int id1, f, flag;
	while (toupper(an) == 'Y') {
		clrscr();
		gotoxy(1, 25);
		printf("Radical Softwares Limited");
		gotoxy(1, 1);
		printf("ENTER AN ID TO THE QUESTION : ");
		rewind(q);
		printf("\nENTER THE QUESTION : ");
		printf("\n\n\n\nENTER OPTION 1 : ");
		printf("\nENTER OPTION 2 : ");
		printf("\nENTER OPTION 3 : ");
		printf("\nENTER OPTION 4 : ");
		printf("\nENTER THE ANSWER NUMBER : ");
	enid:
		flag = 0;
		while (flag == 0) {
			id1 = NULL;
			gotoxy(31, 1);
			flag = scanf("%d", &id1);
		}
		rewind(q);
		while (fread(&qe, sizeof(qe), 1, q) == 1) {
			if (qe.id == id1) {
				// textcolor(-3);
				gotoxy(10, 15);
				printf("ID NUMBER IS REPEATED ");
				getch();
				gotoxy(10, 15);
				//clreol();
				printf("                      ");
				// textcolor (7);
				printf(" ");
				goto enid;

			}
		}
		qe.id = id1;
		flushall();
	enqe:
		gotoxy(22, 2);
		gets(qe.ques);
		if (strlen(qe.ques) <= 2) {
			gotoxy(10, 15);
			// textcolor (-4);
			printf("INVALID QUESTION. PLEASE ENTER IT AGAIN");
			// textcolor (7);
			getch();
			gotoxy(10, 15);
			printf("                                        ");
			goto enqe;
		}
		flushall();
	enop1:
		gotoxy(18, 6);
		gets(qe.op1);
		if (strlen(qe.op1) < 1) {
			gotoxy(10, 15);
			// textcolor (-5);
			printf("AN OPTION FIELD CANNOT BE EMPTY");
			getch();
			gotoxy(10, 15);
			printf("                              ");
			// textcolor(7);
			printf(" ");
			goto enop1;
		}
		flushall();
	enop2:
		gotoxy(18, 7);
		gets(qe.op2);
		if (strlen(qe.op2) < 1) {
			gotoxy(10, 15);
			// textcolor (-5);
			printf("AN OPTION FIELD CANNOT BE EMPTY");
			getch();
			gotoxy(10, 15);
			// textcolor (7);
			printf("                               ");
			goto enop2;
		}
		flushall();
	enop3:
		gotoxy(18, 8);
		gets(qe.op3);
		if (strlen(qe.op3) < 1) {
			gotoxy(10, 15);
			// textcolor (-5);
			printf("AN OPTION FIELD CANNOT BE EMPTY");
			getch();
			// textcolor (7);
			gotoxy(10, 15);
			printf("                               ");
			goto enop3;
		}
		flushall();
	enop4:
		gotoxy(18, 9);
		gets(qe.op4);
		if (strlen(qe.op4) < 1) {
			gotoxy(10, 15);
			// textcolor (-5);
			printf("AN OPTION FIELD CANNOT BE EMPTY");
			getch();
			// textcolor(7);
			gotoxy(10, 15);
			printf("                               ");
			goto enop4;
		}
		flushall();

	enans:
		gotoxy(27, 10);
		qe.ans = getchar();
		if (qe.ans != '1' && qe.ans != '2' && qe.ans != '3' && qe.ans != '4') {
			gotoxy(10, 15);
			// textcolor (-3);
			printf("ANSWER MUST BE ONLY 1 OR 2 OR 3 OR 4. INPUT ERROR");
			getch();
			gotoxy(10, 15);
			// textcolor(7);
			printf("                                                 ");
			goto enans;
		}
		flushall();
		fwrite(&qe, sizeof(qe), 1, q);
		printf("\n\nADD ANOTHER QUESTION (Y/N) : ");
		an = getche();
	}
}


viewrec1(struct question* q1, int a) {
	printf("\n");
	// textcolor (BROWN);
	printf("Q.ID : %d", q1->id);
	printf("\n\n");
	// textcolor (LIGHTRED);
	printf("QUESTION : %s", q1->ques);
	printf("\n\n");
	// textcolor(LIGHTCYAN);
	printf("1. %s", q1->op1);
	printf("\n");
	printf("2. %s", q1->op2);
	printf("\n");
	printf("3. %s", q1->op3);
	printf("\n");
	printf("4. %s", q1->op4);
	if (a == 1) {
		printf("\n\n");
		// textcolor (YELLOW);
		printf("ANSWER : %c", q1->ans);
		// textcolor (7);
		printf("");
	}
	// textcolor(7);
	printf("");
}


test() {
	int i = 0, j = 0;
	clrscr();
	rewind(q);
	// textcolor(7);
	printf("");
	while (fread(&qe, sizeof(qe), 1, q) == 1) {
		j++;
	}
	if (j != 0) {
		rewind(q);
		while (fread(&qe, sizeof(qe), 1, q) == 1) {
			clrscr();
			gotoxy(1, 25);
			printf("Radical Softwares Limited");
			gotoxy(1, 1);
			i++;
			printf("QUESTION %d of %d", i, j);
			viewrec1(&qe, 0);
			getch();
		}
	}
	else {
		clrscr();
		printf("NO RECORDS IN THE FILE Q.DAT");
	}

	printf("\n\nTOTAL QUESTIONS LISTED : %d", i);
	getch();
}

delq() {
	int id1, i, j = 0, k, flag = 0;
	char an = 'Y';
	FILE* t;
	rewind(q);
	while (fread(&qe, sizeof(qe), 1, q) == 1) {
		j++;
	}
	if (j == 0) {
		clrscr();
		gotoxy(1, 25);
		printf("Radical Softwares Limited");
		gotoxy(20, 10);
		printf("NO RECORDS TO DELETE");
		gotoxy(20, 11);
		printf("The file Q.DAT is empty");
		getch();
		return 0;
	}
	while (toupper(an) == 'Y') {
		clrscr();
		gotoxy(1, 25);
		printf("Radical Softwares Limited");
		gotoxy(1, 1);
		flag = 0;
		printf("ENTER THE QUESTION ID TO BE DELETED : ");
		scanf("%d", &id1);
		rewind(q);
		while (fread(&qe, sizeof(qe), 1, q) == 1) {
			if (id1 == qe.id) {
				flag = 1;
				break;
			}
		}
		rewind(q);
		if (flag == 1) {
			unlink("TEMP.DAT");
			t = fopen("TEMP.DAT", "ab+");
			while (fread(&qe, sizeof(qe), 1, q) == 1) {
				if (id1 != qe.id) {
					fwrite(&qe, sizeof(qe), 1, t);
				}
			}
			rewind(t);
			fclose(q);
			unlink("Q.DAT");
			q = fopen("Q.DAT", "ab+");
			if (q == NULL) {
				printf("\n\nUNABLE TO CREATE Q.DAT.");
				getch();
				fclose(q);
				fclose(h);
				fclose(t);
				exit(0);
			}
			while (fread(&qe, sizeof(qe), 1, t) == 1) {
				fwrite(&qe, sizeof(qe), 1, q);
			}
			fclose(t);
			printf("\nDO YOU WANT TO DELETE ANOTHER RECORD (Y or N) : ");
			an = getche();
		}
		if (flag != 1) {
			printf("\nID NUMBER %d NOT FOUND", id1);
			printf("\nDO YOU WANT TO DELETE ANOTHER RECORD (Y or N) : ");
			an = getche();
		}
	}
}


reg1() {
	int nrec = 0, flag = 0;
	char password[100], usrid[100];
	rewind(reg);
	while (fread(&usr, sizeof(usr), 1, reg) == 1) {
		nrec++;
	}
	clrscr();
	gotoxy(1, 25);
	printf("Radical Softwares Limited");
	gotoxy(1, 1);
	printf("ENTER YOUR FULL NAME   : ");
	printf("\nENTER DESIRED USERNAME : ");
	printf("\nENTER PASSWORD         : ");
	gotoxy(26, 1);
	gets(usr.name);
enusrid:
	gotoxy(26, 2);
	gets(usrid);
	rewind(reg);
	while (fread(&usr, sizeof(usr), 1, reg) == 1) {
		flag = 0;
		if (strcmp(usrid, usr.id) == 0) {
			flag = 1;
			break;
		}
	}
	if (flag == 1 || strlen(usrid) < 2) {
		gotoxy(1, 5);
		// textcolor (-3);
		printf("This USER ID is already in use by someone");
		gotoxy(1, 6);
		printf("Please Choose another one");
		getch();
		gotoxy(1, 5);
		//clreol();
		printf("                                         ");
		gotoxy(1, 6);
		//clreol();
		printf("                         ");
		// textcolor (7);
		printf("");
		gotoxy(26, 2);
		//clreol();    /* CLREOL() --> THIS FUNCTIONS CLEARS A LINE */
		printf("                    ");
		// textcolor (7);
		printf("");
		goto enusrid;
	}
	gotoxy(26, 3);
	gets(usr.password);
	strcpy(usr.id, usrid);
	fseek(reg, 0, SEEK_END);
	fwrite(&usr, sizeof(usr), 1, reg);
}
modq() {
	int id1, j = 0;
	int flag = 0;
	char an = 'Y', ch;
	FILE* t;
	rewind(q);                                        /* ********** */
	while (fread(&qe, sizeof(qe), 1, q) == 1) {
		j++;
	}
	if (j == 0) {
		clrscr();
		gotoxy(1, 25);
		printf("Radical Softwares Limited");
		gotoxy(20, 10);
		printf("NO RECORDS TO MODIFY");
		gotoxy(20, 11);
		printf("The file Q.DAT is empty");
		getch();
		return 0;
	}                                               /* ********** */

	while (toupper(an) == 'Y') {
		clrscr();
		gotoxy(1, 25);
		printf("Radical Softwares Limited");
		flag = 0;
		// textcolor(GREEN);
		gotoxy(10, 12);
		printf("\nENTER THE RECORD ID TO BE MODIFIED : ");
		// textcolor(7);
		printf("");
		scanf("%d", &id1);
		rewind(q);
		while (fread(&qe, sizeof(qe), 1, q) == 1) {
			if (id1 == qe.id) {
				clrscr();
				gotoxy(1, 25);
				printf("Radical Softwares Limited");
				gotoxy(1, 1);
				flag = 1;
				// textcolor(LIGHTRED);
				gotoxy(1, 1);
				printf("DETAILS OF CURRENT RECORD NUMBER %d : ", id1);
				// textcolor(GREEN);
				gotoxy(20, 10);
				printf("QUESTION : ");
				// textcolor (CYAN);
				printf("%s", qe.ques);
				gotoxy(20, 12);
				// textcolor (GREEN);
				printf("OPTION 1 : ");
				// textcolor(CYAN);
				printf("%s", qe.op1);
				gotoxy(20, 13);
				// textcolor (GREEN);
				printf("OPTION 2 : ");
				// textcolor(CYAN);
				printf("%s", qe.op2);
				gotoxy(20, 14);
				// textcolor (GREEN);
				printf("OPTION 3 : ");
				// textcolor (CYAN);
				printf("%s", qe.op3);
				// textcolor(GREEN);
				gotoxy(20, 15);
				printf("OPTION 4 : ");
				// textcolor (CYAN);
				printf("%s", qe.op4);
				gotoxy(20, 16);
				// textcolor (GREEN);
				printf("ANSWER   : ");
				// textcolor (CYAN);
				printf("%c", qe.ans);
				getch();
				// textcolor(7);
				printf("");
				printf("\n\nPress any key to modify this record...");
				break;
			}
		}
		clrscr();
		if (flag == 1) {
		sure:
			printf("\n\nAre you sure that you want to modify this record (Y/N) : ");
			ch = getche();
			switch (toupper(ch)) {
			case 'Y':
				clrscr();
				gotoxy(1, 25);
				printf("Radical Softwares Limited");
				gotoxy(1, 1);
				printf("ENTER AN ID TO THE QUESTION : %d", id1);
				rewind(q);
				printf("\nENTER THE QUESTION : ");
				printf("\n\n\n\nENTER OPTION 1 : ");
				printf("\nENTER OPTION 2 : ");
				printf("\nENTER OPTION 3 : ");
				printf("\nENTER OPTION 4 : ");
				printf("\nENTER THE ANSWER NUMBER : ");

				t1.id = id1;
				flushall();
			enqe1:
				gotoxy(22, 2);
				gets(t1.ques);
				if (strlen(t1.ques) <= 2) {
					gotoxy(10, 15);
					// textcolor (-4);
					printf("INVALID QUESTION. PLEASE ENTER IT AGAIN");
					// textcolor (7);
					getch();
					gotoxy(10, 15);
					printf("                                        ");
					goto enqe1;
				}
				flushall();
			enop11:
				gotoxy(18, 6);
				gets(t1.op1);
				if (strlen(t1.op1) < 1) {
					gotoxy(10, 15);
					// textcolor (-5);
					printf("AN OPTION FIELD CANNOT BE EMPTY");
					getch();
					gotoxy(10, 15);
					printf("                              ");
					// textcolor(7);
					printf(" ");
					goto enop11;
				}
				flushall();
			enop21:
				gotoxy(18, 7);
				gets(t1.op2);
				if (strlen(t1.op2) < 1) {
					gotoxy(10, 15);
					// textcolor (-5);
					printf("AN OPTION FIELD CANNOT BE EMPTY");
					getch();
					gotoxy(10, 15);
					// textcolor (7);
					printf("                               ");
					goto enop21;
				}
				flushall();
			enop31:
				gotoxy(18, 8);
				gets(t1.op3);
				if (strlen(t1.op3) < 1) {
					gotoxy(10, 15);
					// textcolor (-5);
					printf("AN OPTION FIELD CANNOT BE EMPTY");
					getch();
					// textcolor (7);
					gotoxy(10, 15);
					printf("                               ");
					goto enop31;
				}
				flushall();
			enop41:
				gotoxy(18, 9);
				gets(t1.op4);
				if (strlen(t1.op4) < 1) {
					gotoxy(10, 15);
					// textcolor (-5);
					printf("AN OPTION FIELD CANNOT BE EMPTY");
					getch();
					// textcolor(7);
					gotoxy(10, 15);
					printf("                               ");
					goto enop41;
				}
				flushall();

			enans1:
				gotoxy(27, 10);
				t1.ans = getchar();
				if (t1.ans != '1' && t1.ans != '2' && t1.ans != '3' && t1.ans != '4') {
					gotoxy(10, 15);
					// textcolor (-3);
					printf("ANSWER MUST BE ONLY 1 OR 2 OR 3 OR 4. INPUT ERROR");
					getch();
					gotoxy(10, 15);
					printf("                                                 ");
					goto enans1;
				}
				flushall();
				unlink("TEMP.DAT");
				t = fopen("TEMP.DAT", "ab+");
				t1.id = id1;
				rewind(q);
				while (fread(&qe, sizeof(qe), 1, q) == 1) {
					if (id1 != qe.id) {
						fwrite(&qe, sizeof(qe), 1, t);
					}
					if (id1 == qe.id) {
						fwrite(&t1, sizeof(t1), 1, t);
					}
				}
				rewind(t);

				fclose(q);
				unlink("Q.DAT");
				q = fopen("Q.DAT", "ab+");
				while (fread(&qe, sizeof(qe), 1, t) == 1) {
					fwrite(&qe, sizeof(qe), 1, q);
				}
				fclose(t);
				unlink("TEMP.DAT");
				printf("\n\n Record modified...");
				break;
			case 'N':
				break;
			default:
				goto sure;
			}
		}
		else {
			printf("RECORD ID %d NOT FOUND ", id1);
		}


		printf("\n\nDo you want to modify another record (Y/N) : ");
		an = getche();
	}
}


viewrec(int id1, int a) {  /* FUNCTION WHICH DISPLAYS A PARTICULAR RECORD */
	int found = 0;
	idd = q;
	rewind(idd);
	gotoxy(1, 25);
	printf("Radical Softwares Limited");
	gotoxy(1, 1);
	while (fread(&qe, sizeof(qe), 1, idd) == 1) {
		if (id1 == qe.id) {
			found = 1;
			printf("\n");
			// textcolor (BROWN);
			printf("Q.ID : %d", qe.id);
			// textcolor (LIGHTRED);
			printf("\n\n");
			printf("QUESTION : %s", qe.ques);
			printf("\n\n");
			// textcolor (LIGHTCYAN);
			printf("1. %s", qe.op1);
			printf("\n");
			printf("2. %s", qe.op2);
			printf("\n");
			printf("3. %s", qe.op3);
			printf("\n");
			printf("4. %s", qe.op4);
			if (a == 1) {
				// textcolor (YELLOW);
				printf("\n\n");
				printf("ANSWER : %c", qe.ans);
				// textcolor (7);
				printf("");
			}
		}
	}
	if (found == 0) {
		printf("\nRECORD NOT FOUND");
		getch();
	}
}

viewmenu() { /*DISPLAYS VIEWMENU */
	char ch;
	int i;
	char an = 'Y';
	do {
		clrscr();
		// textcolor (7);
		printf("");
		gotoxy(28, 10);
		// textcolor(7);
		printf("");
		gotoxy(1, 25);
		printf("Radical Softwares Limited");
		gotoxy(28, 10);
		printf("1.VIEW ALL RECORDS");
		gotoxy(28, 11);
		printf("2.VIEW A PARTICULAR RECORD");
		gotoxy(28, 12);
		printf("0.RETURN TO PREVIOUS MENU");
		gotoxy(28, 14);
		printf("ENTER YOUR CHOICE : ");
		ch = getche();
		switch (ch) {
		case '1':
			test();
			break;
		case '2':
			clrscr();
			gotoxy(1, 25);
			printf("Radical Softwares Limited");
			gotoxy(1, 1);
			printf("ENTER THE RECORD ID TO BE VIEWED : ");
			scanf("%d", &i);
			viewrec(i, 0);
			getch();
			break;
		case '0':
			an = 'N';
		}
	} while (an == 'Y');
}


test1() {
	char ch, an = 'Y';
	int i;
	do {
		clrscr();
		gotoxy(1, 25);
		printf("Radical Softwares Limited");
		gotoxy(28, 8);
		printf("1.ADD RECORDS");
		gotoxy(28, 9);
		printf("2.DELETE RECORDS");
		gotoxy(28, 10);
		printf("3.MODIFY RECORDS");
		gotoxy(28, 11);
		printf("4.VIEW ");
		gotoxy(28, 12);
		printf("0.RETURN TO PREVIOUS MENU");
		gotoxy(28, 14);
		printf("ENTER YOUR CHOICE : ");
		ch = getche();
		switch (ch) {
		case '1':
			addq();
			break;
		case '2':
			delq();
			break;
		case '3':
			modq();
			break;
		case '4':
			clrscr();
			viewmenu();
			break;
		case '5':
			clrscr();
			gotoxy(1, 25);
			printf("Radical Softwares Limited");
			gotoxy(10, 10);
			printf("ENTER RECORD ID TO BE VIEWED : ");
			scanf("%d", &i);
			viewrec(i, 1);
			getch();
			break;
		case '0':
			an = 'N';
		}
	} while (an == 'Y');
}


char usrname1[100], usr1[100];

conduct() {
	char ans, temp;
	int i, j, k, nrec = 0, qno = 0, cond = 1;
	int score = 0, qualify;
	rewind(q);
	clrscr();
	while (fread(&qe, sizeof(qe), 1, q) == 1) {
		nrec++;
	}
	if (nrec <= 0) {
		clrscr();
		gotoxy(1, 25);
		printf("Radical Softwares Limited");
		gotoxy(28, 11);
		printf("NO RECORDS TO PLAY QUIZ");
		gotoxy(28, 12);
		printf("Build Database and start playing");
		gotoxy(28, 13);
		printf("Press any key to continue...");
		getch();
		return 0;
	}

	printf("\nTOTAL NUMBER OF QUESTIONS ARE : %d", nrec);
	printf("\nYOUR MAXIMUM SCORE WILL BE    : %d", nrec);
	qualify = nrec * (0.75);
	printf("\nQUALIFYING MARK               : %d", qualify);
	printf("\n\nPress any key to start quiz...");
	gotoxy(1, 25);
	printf("Radical Softwares Limited");
	getch();
	flushall();
	clrscr();    /*viewrec1(struct *,0);*/
	rewind(q);
	while (fread(&qe, sizeof(qe), 1, q) == 1) {
		clrscr();
		gotoxy(1, 25);
		printf("Radical Softwares Limited");
		gotoxy(40, 1);
		{
			// textcolor(LIGHTGRAY);
			printf("CURRENTLY LOGGED : %s", usr1);
		}
		gotoxy(1, 1);
		printf("YOUR SCORE : %d", score);
		qno++;
		printf("\nQUESTION NUMBER : %d\n", qno);
		viewrec1(&qe, 0);
		printf("\n\n");
		// textcolor (LIGHTMAGENTA);
		printf("ENTER YOUR ANSWER : ");
		scanf("%c", &ans);
		flushall();
		flushall();
		cond++;
		if (cond >= 4) {
			cond = 0;
		}
		if (ans == qe.ans) {
			score++;
			if (cond == 1) {
				printf("\n\n");
				printf("So, r u thinking that ur answer is right (Y/N) : ");
				temp = getche();
				switch (toupper(temp)) {
				case 'Y':
					printf("\n\nU r absolutely correct.\nReally confidence builds a man");
					getch();
					break;
				case 'N':
					printf("\nHey, be confindent.\nYou are right...!");
					getch();
					break;
				default:
					printf("\nHey, dont get confused. You are right");
					getch();
					break;
				}
			}
			if (cond == 2) {
				printf("\n\nHmmmmm...Thinking of your answer");
				sleep(2);
				printf("\nYES, YOU ARE CORRECT!!!");
				getch();
			}
			if (cond == 3) {
				printf("\n\nBe cool. I am processing your answer");
				sleep(2);
				printf("\nhmmmmmm...YES, YOU ARE RIGHT. Hurray!!!!");
				getch();
			}
			if (cond == 4) {
				printf("\n\nYes, your answer is absolutely correct");
				getch();
			}
		}
		else {
			score = score + 0;
			if (cond == 1) {
				printf("\n\nI am sorry to say that....");
				printf("\nYour guess is wrong");
				getch();
			}
			if (cond == 2) {
				sleep(2);
				printf("\n\nJust now we processed your result.\nBut, you are wrong");
				getch();
			}
			if (cond == 3) {
				sleep(2);
				printf("\n\nAll the best to the next question...");
				printf("\nSorry to say that your answer is wrong");
				getch();
			}
			if (cond == 4) {
				sleep(2);
				printf("\n\nOh..NO..Your answer is wrong\nDon't worry. All the best for the next one.");
				getch();
			}

		}
		// textcolor (7);
		printf("");
	}
	clrscr();
	if (score >= qualify) {
		gotoxy(1, 25);
		printf("Radical Softwares Limited");
		// textcolor (-5);
		gotoxy(28, 11);
		printf("CONGRATULATIONS YOU ARE QUALIFIED");
		gotoxy(28, 12);
		// textcolor (RED);
		printf("Hope you celebrate it.");
		getch();
		// textcolor(7);
		printf("");
		return 0;
	}
	else {
		gotoxy(1, 25);
		printf("Radical Softwares Limited");
		// textcolor (2);
		printf("Sorry, you are disqualified");
		gotoxy(28, 12);
		printf("Hey, cheer up ur mood and play again");
		gotoxy(28, 13);
		printf("Press any key to return to main menu...");
		getch();
		// textcolor (7);
		printf("");
		return 0;
	}
}


char id1[100];

login() {
	char password[100], i;
	char c;
	int flag = 0;
enuid:
	clrscr();
	gotoxy(1, 25);
	printf("Radical Softwares Limited");
	gotoxy(28, 11);
	printf("ENTER USERID : ");
	gotoxy(28, 12);
	printf("PASSWORD     : ");
	gotoxy(44, 11);
	gets(usr1);
	i = 0;
	c = '\0';
	gotoxy(44, 12);
	while (c != '\r') {
		c = getch();
		if (c == '\t' || c == '\n') {
			printf("\a");
		}
		if (c != '\r' && c != '\b' && c != '\t' && c != '\0' && c != '\a') {
			password[i] = c;
			i++;
			/* printf ("�"); */
			/* printf (""); */
			/* printf ("�"); */
			printf("*");
			/* printf ("�"); */

		}
		if (c == '\b' && i > 0) {
			i--;
			printf("\b");
			printf(" ");
			printf("\b");
		}
	}
	password[i] = '\0';
	if (strlen(usr1) < 1 || strlen(password) < 1) {
		printf("\n\n\t\t\tUSERID/PASSWORD ARE INVALID ON DOMAIN");
		getch();
		goto enuid;
	}
	rewind(reg);
	while (fread(&usr, sizeof(usr), 1, reg) == 1) {
		flag = 0;
		if (strcmp(usr.id, usr1) == 0) {
			if (strcmp(usr.password, password) == 0) {
				flag = 1;
				fseek(reg, 1, SEEK_CUR);
				strcpy(usrname1, usr.name);
			}
		}
	}
	if (flag == 0) {
		printf("\n\n\t\t\tUSERID/PASSWORD ARE INVALID ON DOMAIN");
		getch();
	}
	if (flag == 1) {
		return(1);
	}
	else {
		return(0);
	}
}

main() {
	char ch, an = 'Y';
	int check = 0, nusr;
	q = fopen("Q.DAT", "ab+");
	h = fopen("HISCORE.DAT", "ab+");
	reg = fopen("USER.DAT", "ab+");
	clrscr();
	// textcolor(9);
	printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t");
	printf("Radical Softwares Limited");
	printf("\n\t\t\t");
	// textcolor(6);
	printf("     Q U I Z v.2.0");
	// textcolor(7);
	printf("");
	sleep(3);
	printf("\n\n\n\t\t\tPress any key to continue...");
	gotoxy(1, 1);
	getch();
	do {
		clrscr();
		rewind(reg);
		nusr = 0;
		while (fread(&usr, sizeof(usr), 1, reg) == 1)
			nusr++;
		gotoxy(45, 1);
		// textcolor(-6);
		printf("NUMBER OF REGISTERED USERS : %d", nusr);
		gotoxy(1, 25);
		printf("Radical Softwares Limited");
		// textcolor(7);
		printf("");
		gotoxy(28, 11);
		printf("1.LOGIN");
		gotoxy(28, 12);
		printf("2.REGISTER");
		gotoxy(28, 13);
		printf("3.HELP");
		gotoxy(28, 14);
		printf("0.EXIT");
		gotoxy(28, 16);
		printf("ENTER YOUR CHOICE : ");
		ch = getche();
		switch (ch) {
		case '1':
			check = login();
			break;
		case '2':
			reg1();
			break;
		case '3':
			clrscr();
			gotoxy(1, 25);
			printf("Radical Softwares Limited");
			gotoxy(1, 1);
			printf("1.IF YOU ALREADY HAVE A USERID AND PASSWORD.      ");
			printf("\nTHEN PRESS \"1\", TYPE YOUR USERID AND PASSWORD");
			printf("\n\n2.IF YOU DON'T HAVE ONE, THEN PRESS \"2\" AND FILL");
			printf("\nTHE FORM AND LOGIN AGAIN. REMEMBER, YOU SHOULD HAVE A UNIQUE ID");
			getch();
			clrscr();
			break;
		case '0':
			fclose(q);
			fclose(h);
			fclose(reg);
			unlink("TEMP.DAT");
			fcloseall();
			exit(0);
		}
	} while (check == 0);
	do {
		clrscr();
		// textcolor(7);
		printf("");
		gotoxy(1, 25);
		printf("Radical Softwares Limited");
		gotoxy(28, 11);
		printf("1.PLAY QUIZ");
		gotoxy(28, 12);
		printf("2.MANIPULATE RECORDS");
		gotoxy(28, 13);
		printf("3.HELP");
		gotoxy(28, 14);
		printf("0.QUIT");

		gotoxy(28, 16);
		printf("ENTER YOUR CHOICE : ");
		flushall();
		ch = getche();
		switch (ch) {
		case '1':
			conduct();
			break;
		case '2':
			test1();
			break;
		case '3':
			clrscr();
			gotoxy(1, 25);
			printf("Radical Softwares Limited");
			gotoxy(1, 1);
			printf("1.YOU WILL BE ASKED A NUMBER OF QUESTIONS DEPENDING UPON THE NUMBER OF");
			printf("\n  RECORDS IN THE DATABASE FILE.");
			printf("\n\n2.EACH QUESTION CARRIES ONE MARK.");
			printf("\n  THERE IS NO NEGATIVE MARKING");
			printf("\n\n3.ONE QUESTION WITH FOUR OPTIONALS WILL BE PROVIDED TO YOU");
			printf("\n  IN WHICH YOU HAVE TO CHOOSE THE RIGHT OPTIONAL");
			printf("\n\n4.YOU CAN EDIT,DELETE AND ADD RECORDS IN THE RECORD MANIPULATIONS MENU");
			getch();
			clrscr();
			break;
		case '0':
			an = 'N';
			fcloseall();
			break;
		default:
			gotoxy(10, 1);
			// textcolor (-3);
			printf("INVALID CHOICE");
			getch();
			// textcolor(7);
			printf("");
		}
	} while (an == 'Y');
	unlink("TEMP.DAT");
	fclose(q);
	fclose(h);
	fclose(reg);
}