// chat_sqlite.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdc++.h>
#include <conio.h>
#include <windows.h> //  dung cho clrscr
#include "Maccount.h"

using namespace std;
void showmess();
void view_bak_login();
void view_bak_showmess();
void viewmain();
Maccount us = Maccount();
//ham xoa man hinh
void clrscr()
{
	COORD origin = { 0, 0 };
	unsigned long len;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	unsigned long size;
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(handle, &csbi);
	size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(handle, TEXT(' '), size, origin, &len);
	FillConsoleOutputAttribute(handle, csbi.wAttributes, size, origin, &len);
	SetConsoleCursorPosition(handle, origin);
}

void Detail_send_fr() {
	int chon;
	cout << "chon menu: [1] Detail_send_friend [2] exit" << endl;
	while (1)
	{
		cout << "ban chon so: ";
		cin >> chon;
		switch (chon) {
		case 1:
			us.Detail_Reply(us.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			return;
		}
	}
}

void  Ctrl_R() {
	int chon;
	while (1)
	{
		cout << "chon menu: [1] Reply friend    [2] exit" << endl;
		cout << "ban chon so: ";
		cin >> chon;
		switch (chon) {
		case 1:
			us.Reply(us.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			return;
		}
	}
}

void send() {
	int chon;
	while (1)
	{
		cout << "chon menu: [1] SendMess  [2] cach 2: bam ctr_L  [3] exit" << endl;
		cout << "ban chon so: ";
		cin >> chon;
		switch (chon) {
		case 1:
			us.SendMess(us.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			us.SendMess_ctr_l(us.id);
			cout << "-----------------------" << endl;
			break;
		case 3:
			return;
		}
	}
}

void login() {
	int chon;
	enum { ONE_KEYID = 1, TWO_KEYID = 2 };
	RegisterHotKey(0, ONE_KEYID, MOD_CONTROL | MOD_NOREPEAT, 0x42); // register 1 key as hotkey
	RegisterHotKey(0, TWO_KEYID, MOD_CONTROL | MOD_NOREPEAT, 0x4E); // register 2 key 
	MSG msg;
	clrscr();
	while (1)
	{
		cout << "-------- chon menu-------" << endl;
		cout << "----[1]showmess [2]detailmess [3]sendmess [4]Addfriend [5]showfr [6]block [7]Update_fr [8]Detail_friend [9]exit" << endl;
		cout << "ban chon so: ";
		cin >> chon;
		switch (chon) {
		case 1:
			showmess();
			break;
		case 2:
			us.ShowMessDetail(us.id);
			if (us.Detail) {
				Ctrl_R();
			}
			break;
		case 3:
			send();
			break;
		case 4:
			us.AddFriend(us.id);
			break;
		case 5:
			us.ShowFriend(us.id);
			cout << " Ctrl + c to arrange friends" << endl;
			us.ShowFriend_ctr_C(us.id);
			cout << "Ctr+B to back or Ctr+N to next" << endl;
			while (GetMessage(&msg, 0, 0, 0))
			{
				PeekMessage(&msg, 0, 0, 0, 0x0001);
				if (msg.message == WM_HOTKEY)
				{
					if (msg.wParam == ONE_KEYID)
					{
						viewmain();
						break;
					}
					else if (msg.wParam == TWO_KEYID)
					{
						view_bak_login();
					}
				}
				/*switch (msg.message)
				{
				case WM_HOTKEY:
					if (msg.wParam == ONE_KEYID)
					{
						viewmain();
						break;
					}
					else if (msg.wParam == TWO_KEYID)
					{
						viewtest();
						if (msg.wParam == ONE_KEYID)
						{
							login();
							break;
						}
					}
				}*/
			}
			break;
		case 6:
			us.BlockFriend(us.id);
			break;
		case 7:
			us.Update_fr(us.id);
			break;
		case 8:
			us.Detail_fr(us.id);
			if (us.Detail) {
				Detail_send_fr();
			}
			break;
		case 9:
			break;
		default:
			printf("\r\n>> Ban chon sai, an phim bat ki de chon lai..");
			_getch();
		}
		if (chon == 9)
		{
			break;
		}
	}
}

void view_bak_login() {
	clrscr();
	cout << "Ban Da Di Den View Tiep Theo" << endl;
	cout << "Ctr+B to back view" << endl;
	enum { ONE_KEYID = 1, TWO_KEYID = 2 };
	RegisterHotKey(0, ONE_KEYID, MOD_CONTROL | MOD_NOREPEAT, 0x42); // register 1 key as hotkey
	RegisterHotKey(0, TWO_KEYID, MOD_CONTROL | MOD_NOREPEAT, 0x4E); // register 2 key 
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY)
		{
			if (msg.wParam == ONE_KEYID)
			{
				login();
				break;
			}
			else if (msg.wParam == TWO_KEYID)
			{
				
			}
		}
	}
}
void view_bak_showmess() {
	clrscr();
	cout << "Ban Da Di Den View Tiep Theo" << endl;
	cout << "Ctr+B to back view" << endl;
}
void showmess() {
	int chon;
	cout << "chon menu: [1] send mess  [2] receive messages  [3] exit" << endl;
	cout << "ban chon so: ";
	cin >> chon;
	enum { ONE_KEYID = 1, TWO_KEYID = 2 };
	RegisterHotKey(0, ONE_KEYID, MOD_CONTROL | MOD_NOREPEAT, 0x42); // register 1 key as hotkey
	RegisterHotKey(0, TWO_KEYID, MOD_CONTROL | MOD_NOREPEAT, 0x4E); // register 2 key 
	MSG msg;
	switch (chon) {
	case 1:
		us.ShowMess_send(us.id);
		cout << "-----------------------" << endl;
		cout << "Ctr+B to back or Ctr+N to next" << endl;
		while (GetMessage(&msg, 0, 0, 0))
		{
			PeekMessage(&msg, 0, 0, 0, 0x0001);
			switch (msg.message)
			{
			case WM_HOTKEY:
				if (msg.wParam == ONE_KEYID)
				{
					showmess();
					break;
				}
				else if (msg.wParam == TWO_KEYID)
				{
					view_bak_showmess();
				}
			}
		}
		break;
	case 2:
		us.ShowMess_rec(us.id);
		cout << "-----------------------" << endl;
		cout << "Ctr+B to back or Ctr+N to next" << endl;
		while (GetMessage(&msg, 0, 0, 0))
		{
			PeekMessage(&msg, 0, 0, 0, 0x0001);
			switch (msg.message)
			{
			case WM_HOTKEY:
				if (msg.wParam == ONE_KEYID)
				{
					showmess();
					break;
				}
				else if (msg.wParam == TWO_KEYID)
				{
					view_bak_showmess();
				}
			}
		}
		break;
	case 3:
		login();
		break;
	}
}

void print_menu() {
	cout << "Danh sach lua chon:\r\n";
	cout << "\t1. [1] Login\r\n";
	cout << "\t2. [2] SingUp\r\n";
	cout << "\t2. [3] Logout\r\n";
	cout << "\t3. [4] Exit\r\n";
	cout << "\r\n>> Chon (1->4) tuong ung : ";
}

void viewmain() {
	int choice = 0;
	do {
		system("cls");
		print_menu();
		fflush(stdin);
		cin >> choice;
		switch (choice) {
		case 1:
			us.SignIn();
			if (us.check) {
				login();
			}
			break;
		case 2:
			us.SingUp();
			break;
		case 3:
			us.SignOut();
			break;
		case 4:
			break;
		default:
			printf("\r\n>> Ban chon sai, an phim bat ki de chon lai..");
			_getch();
		}
		if (choice == 4)
		{
			break;
		}
	} while (1);
	// Stop to view
	printf("\r\n>> Nhap phim bat ki de ket thuc chuong trinh...");
}

int main()
{
	viewmain();
	return 0;
}


