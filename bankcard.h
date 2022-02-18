#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include<time.h>
using namespace std;

enum Status { UNHOOKED, HOOKED };

enum MenuType { MAINMENU, ADM_SUBMENU, USER_SUBMENU };

enum FuncType {
	NONE, ADMMOD, USERMOD, OPENACCOUNT, REPORTLOSS, UNHOOKING, CLOSEACCOUNT,
	MONEYSAVE, MONEYDRAW, INQUIRING, TRANSFERING, MODIFYPASSWORD, EXIT
};

struct Date
{
	int month;
	int day;
	int year;
};

struct UserInfo
{
	char user_Num[14];
	char user_Name[15];
	char user_ID[19];
	char user_passwd[20];
	Date openDate;
	Status status;
	int money;
};

struct UserNode
{
	UserInfo userinfo;
	UserNode *next;
};

UserNode *head = NULL, *p = NULL;
void Wait();
void Save(char filename[]);
void RemoveUserList();
void GenCardNum(char cardnum[], UserNode *&head);
bool CloseAccount(UserNode *&head);
bool Hook_Account(UserNode *&head);
bool UnHook_Account(UserNode *&head);
FuncType ShowMenu(MenuType which);
UserInfo &GetUserInfo(UserInfo &userinfo);
UserNode *CreateUserList(char filename[]);
UserNode *OpenAccount(UserInfo &userinfo);
UserNode *Entry(UserNode *&head);
void Money_Save(UserNode *&);
void Money_Draw(UserNode *&);
void Inquiring(UserNode *&);
void Transfering(UserNode *&);
void ModifyPassword(UserNode *&);
int count;