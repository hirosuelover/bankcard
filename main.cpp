#include "bankcard.h"

int main()
{
	UserInfo userinfo;
	bool b1 = true;
	bool b2 = true;
	int cont = 1;
	int cont1 = 1;
	int cont2 = 1;
	head = CreateUserList("users_info.txt");
	while (cont)
	{
		switch (ShowMenu(MAINMENU))
		{
		case ADMMOD:
			cont1 = 1;
			while (cont1)
			{
				FuncType func;
				func = ShowMenu(ADM_SUBMENU);
				switch (func)
				{
				case OPENACCOUNT:
					GetUserInfo(userinfo);
					head = OpenAccount(userinfo);
					break;
				case REPORTLOSS:
					Hook_Account(head);
					break;
				case UNHOOKING:
					UnHook_Account(head);
					break;
				case CLOSEACCOUNT:
					CloseAccount(head);
					break;
				case EXIT:
					cont1 = 0;
					break;
				default:
					break;
				}
			}
			break;
		case USERMOD:
			if (p = Entry(head))
			{
				cont2 = 1;
				while (cont2)
				{
					FuncType func;
					func = ShowMenu(USER_SUBMENU);
					switch (func)
					{
					case MONEYSAVE:
						Money_Save(p);    //
						break;
					case MONEYDRAW:
						Money_Draw(p);    //
						break;
					case INQUIRING:
						Inquiring(p);  //
						break;
					case TRANSFERING:
						Transfering(p);  //
						break;
					case MODIFYPASSWORD:
						ModifyPassword(p);    //
						break;
					case EXIT:
						cont2 = 0;
						break;
					default:
						break;
					}
				}
			}
			break;
		case EXIT:
			RemoveUserList();
			cont = 0;
			break;
		default:
			break;
		}
	}
	return 0;
}

void Wait()
{
	long j = 0;
	for (double i = 1000000; i>0;)
	{
		i = i - 0.002;
		j++;
		j--;
	}
}

FuncType ShowMenu(MenuType which)
{
	FuncType func = NONE;
	int choice = 0;
	switch (which)
	{
	case MAINMENU:
		cout << "************************************************\n";
		cout << "*           欢迎来到银行卡管理系统             *\n";
		cout << "*                                              *\n";
		cout << "*            选择一个模式:                     *\n";
		cout << "*     (1) 管理员模式                           *\n";
		cout << "*     (2) 用户模式                             *\n";
		cout << "*     (3) 退出                                 *\n";
		cout << "************************************************\n";
		cout << "*   你的选择是:";
		cin >> choice;
		cout << "************************************************\n";
		switch (choice)
		{
		case 1: func = ADMMOD; break;
		case 2: func = USERMOD; break;
		case 3: func = EXIT; break;
		default: func = NONE; break;
		}
		break;
	case ADM_SUBMENU:
		cout << "***********************************************\n";
		cout << "*           欢迎来到银行卡管理系统            *\n";
		cout << "*                                             *\n";
		cout << "*          请在以下选项中选择一个功能:        *\n";
		cout << "*     (1) 创建账户                            *\n";
		cout << "*     (2) 报告丢失                            *\n";
		cout << "*     (3) 解挂                                *\n";
		cout << "*     (4) 销户                                *\n";
		cout << "*     (5) 返回                                *\n";
		cout << "***********************************************\n";
		cout << "*";
		cin >> choice;
		cout << "***********************************************\n";
		switch (choice)
		{
		case 1: func = OPENACCOUNT; break;
		case 2: func = REPORTLOSS; break;
		case 3: func = UNHOOKING; break;
		case 4: func = CLOSEACCOUNT; break;
		case 5: func = EXIT; break;
		default: func = NONE; break;
		}
		break;
	case USER_SUBMENU:
		cout << "***********************************************\n";
		cout << "*           欢迎来到银行卡管理系统            *\n";
		cout << "*                                             *\n";
		cout << "*          请在以下选项中选择一个功能:        *\n";
		cout << "*     (1) 存款                                *\n";
		cout << "*     (2) 取款                                *\n";
		cout << "*     (3) 查询余额                            *\n";
		cout << "*     (4) 转账                                *\n";
		cout << "*     (5) 修改密码                            *\n";
		cout << "*     (6) 返回                                *\n";
		cout << "***********************************************\n";
		cout << "*   你的选择是:";
		cin >> choice;
		cout << "***********************************************\n";
		switch (choice)
		{
		case 1: func = MONEYSAVE; break;
		case 2: func = MONEYDRAW; break;
		case 3: func = INQUIRING; break;
		case 4: func = TRANSFERING; break;
		case 5: func = MODIFYPASSWORD; break;
		case 6: func = EXIT; break;
		default: func = NONE; break;
		}
		break;
	default:
		cout << "对不起，没有该选项!!\n";
		break;
	}
	return func;
}

UserNode *CreateUserList(char filename[])
{
	UserNode *p;
	int status = 0;
	ifstream userdata(filename);
	if (!userdata)
	{
		cout << "对不起,文件不存在!" << endl;
		return NULL;

	}
	while (!userdata.eof())
	{
		if (p = new UserNode)
		{
			userdata >> p->userinfo.user_Num;
			userdata >> p->userinfo.user_Name;
			userdata >> p->userinfo.user_ID;
			userdata >> p->userinfo.user_passwd;
			userdata >> p->userinfo.money;
			userdata >> p->userinfo.openDate.year >> p->userinfo.openDate.month >> p->userinfo.openDate.day;
			userdata >> status; p->userinfo.status = (Status)status;
			p->next = head;
			head = p;
		}
	}
	userdata.close();
	return head;
}

void RemoveUserList()
{
	for (UserNode *p2, *p1 = head; p1; p1 = p2)
	{
		p2 = p1->next;
		delete p1;
	}
	head = NULL;
}

UserNode *OpenAccount(UserInfo &userinfo)
{
	UserNode *p;
	char c;
	if (p = new UserNode)
	{
		strcpy_s(p->userinfo.user_Num, userinfo.user_Num);
		strcpy_s(p->userinfo.user_Name, userinfo.user_Name);
		strcpy_s(p->userinfo.user_ID, userinfo.user_ID);
		strcpy_s(p->userinfo.user_passwd, userinfo.user_passwd);
		p->userinfo.openDate.year = userinfo.openDate.year;
		p->userinfo.openDate.month = userinfo.openDate.month;
		p->userinfo.openDate.day = userinfo.openDate.day;
		p->userinfo.money = userinfo.money;
		p->userinfo.status = userinfo.status;
		p->next = head;
		head = p;
	}
	cout << "确认请选Y,取消请选N: ";
	cin >> c;
	cout << "您的卡号为: " << p->userinfo.user_Num << endl;
	if (c == 'Y')
	{
		Save("users_info.txt");
		return p;
	}
	else
	{
		p = head;
		head = head->next;
		delete p;
		return head;
	}
}

bool Hook_Account(UserNode *&head)
{
	char cardnum[14], c;
	int status = 1;
	cout << "请输入用户卡号: ";
	cin >> cardnum;
	UserNode *p1 = head, *p2 = head->next;
	if (!strcmp(head->userinfo.user_Num, cardnum))
	{
		if (head->userinfo.status == 1) { cout << "此卡已挂失!" << endl; return false; }
		cout << "确认请选Y,取消请选N: ";
		cin >> c;
		if (c == 'Y')
		{
			head->userinfo.status = (Status)status;
			Save("users_info.txt");
			return true;
		}
		else return false;
	}
	while (p2 != NULL)
	{
		if (!strcmp(p2->userinfo.user_Num, cardnum)) break;
		else { p1 = p2; p2 = p2->next; }
	}
	if (p2 == NULL) { cout << "对不起,此卡号不存在,无法挂失!" << endl; return false; }
	if (p2->userinfo.status == 1) { cout << "此卡已挂失!" << endl; return false; }
	cout << "确认请选Y,取消请选N: ";
	cin >> c;
	if (c == 'Y')
	{
		p2->userinfo.status = (Status)status;
		Save("users_info.txt");
		return true;
	}
	else return false;
}

bool UnHook_Account(UserNode *&head)
{
	char cardnum[14], c;
	int status = 0;
	cout << "请输入用户卡号: ";
	cin >> cardnum;
	UserNode *p1 = head, *p2 = head->next;
	if (!strcmp(head->userinfo.user_Num, cardnum))
	{
		if (head->userinfo.status == 0) { cout << "此卡没有挂失,无需解挂!" << endl; return false; }
		head->userinfo.status = (Status)status;
		cout << "确认请选Y,取消请选N: ";
		cin >> c;
		if (c == 'Y')
		{
			Save("users_info.txt");
			return true;
		}
		else return false;
	}
	while (p2 != NULL)
	{
		if (!strcmp(p2->userinfo.user_Num, cardnum)) break;
		else { p1 = p2; p2 = p2->next; }
	}
	if (p2 == NULL) { cout << "此卡号不存在,无法解挂!" << endl; return false; }
	if (p2->userinfo.status == 0) { cout << "此卡没有挂失,无需解挂!" << endl; return false; }
	p2->userinfo.status = (Status)status;
	cout << "确认请选Y,取消请选N: ";
	cin >> c;
	if (c == 'Y')
	{
		Save("users_info.txt");
		return true;
	}
	else return false;
}

bool CloseAccount(UserNode *&head)
{
	int count = 0;
	char cardnum[14], code[20], c;
	cout << "请输入用户卡号: ";
	cin >> cardnum;
	UserNode *p1 = head, *p2 = head->next;
	if (p1 == NULL)
	{
		cout << "用户记录为空,无法销户!" << endl;
		return false;
	}
	if (!strcmp(head->userinfo.user_Num, cardnum))
	{
		cout << "请输入密码: ";
		cin >> code;
		count++;
		while (strcmp(head->userinfo.user_passwd, code) != 0 && count <= 3)
		{
			cout << "密码错误,请重新输入: ";
			cin >> code;
			count++;
		}
		if (count>3) return false;
		cout << "用户卡号: " << p1->userinfo.user_Num << endl;
		cout << "用户姓名: " << p1->userinfo.user_Name << endl;
		cout << "用户身份证号: " << p1->userinfo.user_ID << endl;
		cout << "用户密码: " << p1->userinfo.user_passwd << endl;
		cout << "用户储蓄额: " << p1->userinfo.money << endl;
		cout << "开户日期: " << p1->userinfo.openDate.year << "年" << p1->userinfo.openDate.month << "月" << p1->userinfo.openDate.day << "日" << endl;
		cout << "确认请选Y,取消请选N: ";
		cin >> c;
		if (c == 'Y')
		{
			head = p2;
			delete p1;
			Save("users_info.txt");
			return true;
		}
		else return false;
	}
	while (p2 != NULL)
	{
		if (!strcmp(p2->userinfo.user_Num, cardnum)) break;
		else { p1 = p2; p2 = p2->next; }
	}
	if (p2 == NULL) { cout << "此卡号不存在,无法销户!" << endl; return false; }
	cout << "请输入密码: ";
	cin >> code;
	count++;
	while (strcmp(p2->userinfo.user_passwd, code) != 0 && count<3)
	{
		cout << "密码错误,请重新输入: ";
		cin >> code;
		count++;
	}
	if (count >= 3) return false;
	cout << "用户卡号: " << p2->userinfo.user_Num << endl;
	cout << "用户姓名: " << p2->userinfo.user_Name << endl;
	cout << "用户身份证号: " << p2->userinfo.user_ID << endl;
	cout << "用户密码: " << p2->userinfo.user_passwd << endl;
	cout << "用户储蓄额: " << p2->userinfo.money << endl;
	cout << "开户日期: " << p2->userinfo.openDate.year << "年" << p1->userinfo.openDate.month << "月" << p1->userinfo.openDate.day << "日" << endl;
	cout << "确认请选Y,取消请选N: ";
	cin >> c;
	if (c == 'Y')
	{
		p1->next = p2->next;
		delete p2;
		Save("users_info.txt");
		return true;
	}
	else return false;
}

UserInfo &GetUserInfo(UserInfo &userinfo)
{
	char code[20];
	int status = 0;
	userinfo.status = (Status)status;
	cout << "请输入用户姓名: ";
	cin >> userinfo.user_Name;
	cout << "请输入用户身份证号: ";
	cin >> userinfo.user_ID;
	cout << "请输入密码: ";
	cin >> userinfo.user_passwd;
	cout << "请再次输入密码: ";
	cin >> code;
	while (strcmp(userinfo.user_passwd, code))
	{
		cout << "请重新输入密码: ";
		cin >> userinfo.user_passwd;
		cout << "请再次输入密码: ";
		cin >> code;
	}
	cout << "请输入储蓄金额: ";
	cin >> userinfo.money;
	cout << "请输入开户日期: ";
	cin >> userinfo.openDate.year >> userinfo.openDate.month >> userinfo.openDate.day;
	GenCardNum(userinfo.user_Num, head);
	return userinfo;
}


void Money_Save(UserNode *&p)
{
	int money;
	char c;
	cout << "请输入存款额: ";
	cin >> money;
	cout << "操作正在处理中,请稍后..." << endl;
	Wait();
	p->userinfo.money = p->userinfo.money + money;
	Save("users_info.txt");
	cout << "是否打印凭条?(是-Y/否-N): ";
	cin >> c;
	if (c == 'Y')
	{
		cout << "凭条正在打印中..." << endl;
		Wait();
	}
	return;
}


UserNode *Entry(UserNode *&head)
{
	int count = 0;
	char cardnum[14], code[20];
	cout << "请输入卡号: ";
	cin >> cardnum;
	UserNode *p1 = head, *p2 = head->next;
	if (p1 == NULL)
	{
		cout << "对不起,暂无用户记录,无法登录!" << endl;
		return p1;
	}
	if (!strcmp(head->userinfo.user_Num, cardnum))
	{
		if (head->userinfo.status == 1)
		{
			cout << "对不起,此卡已挂失,无法登录!" << endl;
			return NULL;
		}
		cout << "请输入密码: ";
		cin >> code;
		count++;
		while (strcmp(head->userinfo.user_passwd, code) != 0 && count <= 3)
		{
			cout << "密码错误,请重新输入: ";
			cin >> code;
			count++;
		}
		if (count>3) return NULL;
		cout << "操作正在处理中,请稍后..." << endl;
		return head;
	}
	while (p2 != NULL)
	{
		if (!strcmp(p2->userinfo.user_Num, cardnum)) break;
		else { p1 = p2; p2 = p2->next; }
	}
	if (p2 == NULL) { cout << "此卡号不存在,无法登录!" << endl; return NULL; }
	if (p2->userinfo.status == 1)
	{
		cout << "此卡已经挂失,无法登录!" << endl;
		return NULL;
	}
	cout << "请输入密码: ";
	cin >> code;
	count++;
	while (strcmp(p2->userinfo.user_passwd, code) != 0 && count<3)
	{
		cout << "密码错误,请重新输入: ";
		cin >> code;
		count++;
	}
	if (count >= 3) return NULL;
	cout << "操作正在处理,请稍后..." << endl;
	Wait();
	return p2;
}

void GenCardNum(char cardnum[], UserNode *&head)
{
	cardnum[14];
	//char str1[100], str2[100];
	int n;
	int i = 0;
	//	int j;
	int bits = 0;
	int count = 0;
	for (UserNode *p = head; p; p = p->next)
		count++;
	n = count;
	sprintf_s(cardnum, 10, "%08d", count);//转换字符
}

void Money_Draw(UserNode *&p)
{
	int money;
	char c;
	cout << "请输入取款额: ";
	cin >> money;
	if (money>p->userinfo.money)
	{
		cout << "对不起，卡中余额不足!";
		return;
	}
	else
	{
		cout << "操作正在处理中,请稍后..." << endl;
		Wait();
		p->userinfo.money = p->userinfo.money - money;
		Save("users_info.txt");
		cout << "取款成功,请尽快取走钞票!" << endl;
		Wait();
		cout << "是否打印凭条?(是-Y/否-N): ";
		cin >> c;
		if (c == 'Y')
		{
			cout << "凭条正在打印中..." << endl;
			Wait();
		}
	}
	return;
}


void Inquiring(UserNode *&p)
{
	cout << "您的余额: " << p->userinfo.money << endl;
}

void Transfering(UserNode *&p)
{
	char cardnum[14], c;
	int money;
	cout << "请输入对方的卡号: ";
	cin >> cardnum;
	UserNode *q;
	for (q = head; q; q = q->next)
	{
		if (!strcmp(cardnum, q->userinfo.user_Num))
			break;
	}
	if (q == NULL)
	{
		cout << "对不起，此卡号不存在,无法进行转账!";
		return;
	}
	cout << "请输入转账数额: ";
	cin >> money;
	if (money>p->userinfo.money)
	{
		cout << "您卡上的余额不足,无法进行转账!";
		return;
	}
	cout << "操作正在处理中,请稍后..." << endl;
	Wait();
	p->userinfo.money = p->userinfo.money - money;
	q->userinfo.money = q->userinfo.money + money;
	Save("users_info.txt");
	cout << "转账成功!" << endl;
	cout << "是否打印凭条?(是-Y/否-N): ";
	cin >> c;
	if (c == 'Y') cout << "凭条正在打印中..." << endl;
	Wait();
}

void ModifyPassword(UserNode *&p)
{
	char password[20];
	cout << "请输入原密码: ";
	cin >> password;
	cout << "请输入新密码: ";
	cin >> p->userinfo.user_passwd;
	Save("users_info.txt");
	return;
}

void Save(char filename[])
{
	UserNode *p;
	int status;
	ofstream userdata(filename);
	if (!userdata)
	{
		cout << "对不起,输出文件无法打开!" << endl;
		return;
	}
	for (p = head; p; p = p->next)
	{
		userdata << " " << p->userinfo.user_Num;
		userdata << " " << p->userinfo.user_Name;
		userdata << " " << p->userinfo.user_ID;
		userdata << " " << p->userinfo.user_passwd;
		userdata << " " << p->userinfo.money;
		userdata << " " << p->userinfo.openDate.year << " " << p->userinfo.openDate.month << " " << p->userinfo.openDate.day;
		status = p->userinfo.status;
		userdata << " " << status;
	}
	userdata.close();
}


