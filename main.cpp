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
		cout << "*           ��ӭ�������п�����ϵͳ             *\n";
		cout << "*                                              *\n";
		cout << "*            ѡ��һ��ģʽ:                     *\n";
		cout << "*     (1) ����Աģʽ                           *\n";
		cout << "*     (2) �û�ģʽ                             *\n";
		cout << "*     (3) �˳�                                 *\n";
		cout << "************************************************\n";
		cout << "*   ���ѡ����:";
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
		cout << "*           ��ӭ�������п�����ϵͳ            *\n";
		cout << "*                                             *\n";
		cout << "*          ��������ѡ����ѡ��һ������:        *\n";
		cout << "*     (1) �����˻�                            *\n";
		cout << "*     (2) ���涪ʧ                            *\n";
		cout << "*     (3) ���                                *\n";
		cout << "*     (4) ����                                *\n";
		cout << "*     (5) ����                                *\n";
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
		cout << "*           ��ӭ�������п�����ϵͳ            *\n";
		cout << "*                                             *\n";
		cout << "*          ��������ѡ����ѡ��һ������:        *\n";
		cout << "*     (1) ���                                *\n";
		cout << "*     (2) ȡ��                                *\n";
		cout << "*     (3) ��ѯ���                            *\n";
		cout << "*     (4) ת��                                *\n";
		cout << "*     (5) �޸�����                            *\n";
		cout << "*     (6) ����                                *\n";
		cout << "***********************************************\n";
		cout << "*   ���ѡ����:";
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
		cout << "�Բ���û�и�ѡ��!!\n";
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
		cout << "�Բ���,�ļ�������!" << endl;
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
	cout << "ȷ����ѡY,ȡ����ѡN: ";
	cin >> c;
	cout << "���Ŀ���Ϊ: " << p->userinfo.user_Num << endl;
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
	cout << "�������û�����: ";
	cin >> cardnum;
	UserNode *p1 = head, *p2 = head->next;
	if (!strcmp(head->userinfo.user_Num, cardnum))
	{
		if (head->userinfo.status == 1) { cout << "�˿��ѹ�ʧ!" << endl; return false; }
		cout << "ȷ����ѡY,ȡ����ѡN: ";
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
	if (p2 == NULL) { cout << "�Բ���,�˿��Ų�����,�޷���ʧ!" << endl; return false; }
	if (p2->userinfo.status == 1) { cout << "�˿��ѹ�ʧ!" << endl; return false; }
	cout << "ȷ����ѡY,ȡ����ѡN: ";
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
	cout << "�������û�����: ";
	cin >> cardnum;
	UserNode *p1 = head, *p2 = head->next;
	if (!strcmp(head->userinfo.user_Num, cardnum))
	{
		if (head->userinfo.status == 0) { cout << "�˿�û�й�ʧ,������!" << endl; return false; }
		head->userinfo.status = (Status)status;
		cout << "ȷ����ѡY,ȡ����ѡN: ";
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
	if (p2 == NULL) { cout << "�˿��Ų�����,�޷����!" << endl; return false; }
	if (p2->userinfo.status == 0) { cout << "�˿�û�й�ʧ,������!" << endl; return false; }
	p2->userinfo.status = (Status)status;
	cout << "ȷ����ѡY,ȡ����ѡN: ";
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
	cout << "�������û�����: ";
	cin >> cardnum;
	UserNode *p1 = head, *p2 = head->next;
	if (p1 == NULL)
	{
		cout << "�û���¼Ϊ��,�޷�����!" << endl;
		return false;
	}
	if (!strcmp(head->userinfo.user_Num, cardnum))
	{
		cout << "����������: ";
		cin >> code;
		count++;
		while (strcmp(head->userinfo.user_passwd, code) != 0 && count <= 3)
		{
			cout << "�������,����������: ";
			cin >> code;
			count++;
		}
		if (count>3) return false;
		cout << "�û�����: " << p1->userinfo.user_Num << endl;
		cout << "�û�����: " << p1->userinfo.user_Name << endl;
		cout << "�û����֤��: " << p1->userinfo.user_ID << endl;
		cout << "�û�����: " << p1->userinfo.user_passwd << endl;
		cout << "�û������: " << p1->userinfo.money << endl;
		cout << "��������: " << p1->userinfo.openDate.year << "��" << p1->userinfo.openDate.month << "��" << p1->userinfo.openDate.day << "��" << endl;
		cout << "ȷ����ѡY,ȡ����ѡN: ";
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
	if (p2 == NULL) { cout << "�˿��Ų�����,�޷�����!" << endl; return false; }
	cout << "����������: ";
	cin >> code;
	count++;
	while (strcmp(p2->userinfo.user_passwd, code) != 0 && count<3)
	{
		cout << "�������,����������: ";
		cin >> code;
		count++;
	}
	if (count >= 3) return false;
	cout << "�û�����: " << p2->userinfo.user_Num << endl;
	cout << "�û�����: " << p2->userinfo.user_Name << endl;
	cout << "�û����֤��: " << p2->userinfo.user_ID << endl;
	cout << "�û�����: " << p2->userinfo.user_passwd << endl;
	cout << "�û������: " << p2->userinfo.money << endl;
	cout << "��������: " << p2->userinfo.openDate.year << "��" << p1->userinfo.openDate.month << "��" << p1->userinfo.openDate.day << "��" << endl;
	cout << "ȷ����ѡY,ȡ����ѡN: ";
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
	cout << "�������û�����: ";
	cin >> userinfo.user_Name;
	cout << "�������û����֤��: ";
	cin >> userinfo.user_ID;
	cout << "����������: ";
	cin >> userinfo.user_passwd;
	cout << "���ٴ���������: ";
	cin >> code;
	while (strcmp(userinfo.user_passwd, code))
	{
		cout << "��������������: ";
		cin >> userinfo.user_passwd;
		cout << "���ٴ���������: ";
		cin >> code;
	}
	cout << "�����봢����: ";
	cin >> userinfo.money;
	cout << "�����뿪������: ";
	cin >> userinfo.openDate.year >> userinfo.openDate.month >> userinfo.openDate.day;
	GenCardNum(userinfo.user_Num, head);
	return userinfo;
}


void Money_Save(UserNode *&p)
{
	int money;
	char c;
	cout << "���������: ";
	cin >> money;
	cout << "�������ڴ�����,���Ժ�..." << endl;
	Wait();
	p->userinfo.money = p->userinfo.money + money;
	Save("users_info.txt");
	cout << "�Ƿ��ӡƾ��?(��-Y/��-N): ";
	cin >> c;
	if (c == 'Y')
	{
		cout << "ƾ�����ڴ�ӡ��..." << endl;
		Wait();
	}
	return;
}


UserNode *Entry(UserNode *&head)
{
	int count = 0;
	char cardnum[14], code[20];
	cout << "�����뿨��: ";
	cin >> cardnum;
	UserNode *p1 = head, *p2 = head->next;
	if (p1 == NULL)
	{
		cout << "�Բ���,�����û���¼,�޷���¼!" << endl;
		return p1;
	}
	if (!strcmp(head->userinfo.user_Num, cardnum))
	{
		if (head->userinfo.status == 1)
		{
			cout << "�Բ���,�˿��ѹ�ʧ,�޷���¼!" << endl;
			return NULL;
		}
		cout << "����������: ";
		cin >> code;
		count++;
		while (strcmp(head->userinfo.user_passwd, code) != 0 && count <= 3)
		{
			cout << "�������,����������: ";
			cin >> code;
			count++;
		}
		if (count>3) return NULL;
		cout << "�������ڴ�����,���Ժ�..." << endl;
		return head;
	}
	while (p2 != NULL)
	{
		if (!strcmp(p2->userinfo.user_Num, cardnum)) break;
		else { p1 = p2; p2 = p2->next; }
	}
	if (p2 == NULL) { cout << "�˿��Ų�����,�޷���¼!" << endl; return NULL; }
	if (p2->userinfo.status == 1)
	{
		cout << "�˿��Ѿ���ʧ,�޷���¼!" << endl;
		return NULL;
	}
	cout << "����������: ";
	cin >> code;
	count++;
	while (strcmp(p2->userinfo.user_passwd, code) != 0 && count<3)
	{
		cout << "�������,����������: ";
		cin >> code;
		count++;
	}
	if (count >= 3) return NULL;
	cout << "�������ڴ���,���Ժ�..." << endl;
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
	sprintf_s(cardnum, 10, "%08d", count);//ת���ַ�
}

void Money_Draw(UserNode *&p)
{
	int money;
	char c;
	cout << "������ȡ���: ";
	cin >> money;
	if (money>p->userinfo.money)
	{
		cout << "�Բ��𣬿�������!";
		return;
	}
	else
	{
		cout << "�������ڴ�����,���Ժ�..." << endl;
		Wait();
		p->userinfo.money = p->userinfo.money - money;
		Save("users_info.txt");
		cout << "ȡ��ɹ�,�뾡��ȡ�߳�Ʊ!" << endl;
		Wait();
		cout << "�Ƿ��ӡƾ��?(��-Y/��-N): ";
		cin >> c;
		if (c == 'Y')
		{
			cout << "ƾ�����ڴ�ӡ��..." << endl;
			Wait();
		}
	}
	return;
}


void Inquiring(UserNode *&p)
{
	cout << "�������: " << p->userinfo.money << endl;
}

void Transfering(UserNode *&p)
{
	char cardnum[14], c;
	int money;
	cout << "������Է��Ŀ���: ";
	cin >> cardnum;
	UserNode *q;
	for (q = head; q; q = q->next)
	{
		if (!strcmp(cardnum, q->userinfo.user_Num))
			break;
	}
	if (q == NULL)
	{
		cout << "�Բ��𣬴˿��Ų�����,�޷�����ת��!";
		return;
	}
	cout << "������ת������: ";
	cin >> money;
	if (money>p->userinfo.money)
	{
		cout << "�����ϵ�����,�޷�����ת��!";
		return;
	}
	cout << "�������ڴ�����,���Ժ�..." << endl;
	Wait();
	p->userinfo.money = p->userinfo.money - money;
	q->userinfo.money = q->userinfo.money + money;
	Save("users_info.txt");
	cout << "ת�˳ɹ�!" << endl;
	cout << "�Ƿ��ӡƾ��?(��-Y/��-N): ";
	cin >> c;
	if (c == 'Y') cout << "ƾ�����ڴ�ӡ��..." << endl;
	Wait();
}

void ModifyPassword(UserNode *&p)
{
	char password[20];
	cout << "������ԭ����: ";
	cin >> password;
	cout << "������������: ";
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
		cout << "�Բ���,����ļ��޷���!" << endl;
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


