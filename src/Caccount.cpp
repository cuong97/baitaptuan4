#include "Maccount.h"
#include "Mchat.h"
#include<stdc++.h>
#include <iostream>
#include <windows.h>
#include<conio.h>
using namespace std;

Maccount::Maccount(){}
Maccount::~Maccount(){}
void Maccount::SignIn() {
	username = new (char);
	password = new (char);

	cout << "Nhap vao username: ";
	cin >> username;
	cout << "Nhap password: ";
	cin >> password;
	Mchat conn;
	conn.Open();
	if (conn.Select_login(conn.db,username,password)>0) {
		cout << "Sign in successfuly!\n";
		id = conn.Select_login(conn.db, username, password);
		check = true;
		zID = id;
	}
	else {
		cout << "Sign in fail!\n";
		check = false;
		_getch();
	}
}
void Maccount::SingUp() {
	username = new (char);
	password = new char;
	birth = new char;
	name = new char;
	cout << "Nhap vao username: ";
	cin >> username;
	cout << "Nhap password: ";
	cin >> password;
	cout << "Nhap sex: ";
	cin >> sex;
	cout << "Nhap birth: ";
	cin >> birth;
	cout << "Nhap name: ";
	cin >> name;
	cout << "Nhap address: ";
	cin >> address;
	Mchat conn;
	conn.Open();
	if (conn.Select_all(conn.db,username)>0) {
		cout << "user da ton tai" << endl;
	}
	else
	{
		conn.Insert_Acc(conn.db, username, password, sex, birth, name, address);
		int id_mask = conn.Select_mask(conn.db);
		conn.Insert_maskuser(conn.db, id_mask, name, sex, address);
		cout << "them thanh cong" << endl;
	}
}
void Maccount::SignOut() {
	check = false;
	cout << "-----Ban da dang xuat.-------\n";
}

void Maccount::SendMess(int id) {
	if (check) {
		int id2;
		cout << "Chon nguoi dung: ";
		char *frien;
		frien = new char;
		cin >> frien;
		Mchat conn;
		conn.Open();
		id2 = conn.Seach_fr(frien);
		if (id2 > 0) {
			char *mess, *dt;
			mess = new char;
			dt = new char;
			if (conn.CheckBlock(conn.db, id, id2)) {
				cout << "---------You is blocked by her--------\n";
			}
			else {
				int tt = 1;
				conn.update_tt(conn.db, id, id2);
				cout << "Nhap Tin nhan: \n";
				cin.ignore();
				cin.getline(mess,100);
				time_t hientai = time(0);
				dt = ctime(&hientai);
				long int x;
				x = static_cast<int> (hientai);
				conn.WriteToMess(conn.db, id, id2, mess, dt,tt, x);
				conn.ShowMessDetail(conn.db, id, id2);
			}
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Maccount::SendMess_ctr_l(int id) {
	
	if (check) {
		if (RegisterHotKey(
			NULL,
			1,
			MOD_CONTROL | MOD_NOREPEAT,
			0x4c))  //0x42 is 'b'
		{
			cout << " Ctrl + L send" << endl;
		}
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				Mchat conn;
				conn.Open();
				ShowFriend(id);
				cout << "Chon vi tri nguoi ban: ";
				int n;
				cin >> n;
				int id2=conn.ShowaaFriend(conn.db,id,n);
				char *mess, *dt;
				mess = new char;
				dt = new char;
				int tt = 1;
				conn.update_tt(conn.db, id, id2);
				cout << "Nhap Tin nhan: \n";
				cin.ignore();
				cin.getline(mess, 100);
				time_t hientai = time(0);
				dt = ctime(&hientai);
				long int x;
				x = static_cast<int> (hientai);
				conn.WriteToMess(conn.db, id, id2, mess, dt, tt, x);
			}
			break;
		}
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Maccount::ShowMess_send(int ID) {
	if (check) {
		Mchat conn;
		conn.Open();
		conn.SelectMess_send(conn.db, zID);
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Maccount::ShowMess_rec(int ID) {
	if (check) {
		Mchat conn;
		conn.Open();
		conn.SelectMess_receive(conn.db, zID);
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
int Maccount::ShowMessDetail(int id1) {
	if (check) {
		int id2;
		cout << "Chon nguoi dung: ";
		char *frien;
		frien = new char;
		cin >> frien;
		Mchat conn;
		conn.Open();
		id2 = conn.Seach_fr(frien);
		if (id2 > 0) {
			conn.ShowMessDetail(conn.db, id1, id2);
			zID2 = id2;
			Detail = true;
		}
		else { cout << "----Tai khoan khong ton tai-----------\n"; Detail = false; }
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
	return zID2;
}
void Maccount::ShowFriend(int id) {
	if (check) {
		Mchat conn;
		conn.Open();
		conn.ShowFriend(conn.db, id);
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Maccount::ShowFriend_ctr_C(int id) {
	if (check) {
		//ShowFriend(id);
		if (RegisterHotKey(
			NULL,
			1,
			MOD_CONTROL | MOD_NOREPEAT,
			0x43)) 
		{
			//cout << " Ctrl + c to arrange friends" << endl;
		}
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				Mchat conn;
				conn.Open();
				conn.sepxepadd(conn.db, id);
			}
			break;
		}
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Maccount::AddFriend(int id) {
	if (check) {
		cout << "Nhap ten nguoi ban muon them: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		Mchat conn;
		conn.Open();
		int id2 = conn.Seach_fr(newfr);
		if (id2 > 0) {
			if (!conn.CheckFriend(conn.db, id, id2)) {
				if (!conn.CheckBlock(conn.db, id, id2)) {
					conn.WriteToFriend(conn.db, id, id2);
					ShowFriend(id);
				}
				else cout << "------You were blocked by her -------\n\n\n";
			}
			else cout << "------You was friend ----------\n\n\n";
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
	}
	else cout << "----------Ban chua dang nhap.--------\n\n";
}
void Maccount::BlockFriend(int id) {
	if (check) {
		cout << "---------Chon nguoi block :(-------- \n";
		char *name;
		name = new char;
		cin >> name;
		Mchat conn;
		conn.Open();
		int id2 = conn.Seach_fr(name);
		if (id2 > 0) {
			conn.BlockFriend(conn.db, id, id2);
			cout << "---------Block Successfuly---------\n";
			conn.ShowFriend(conn.db, id);
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Maccount::Update_fr(int id) {
	if (check) {
		cout << "Nhap ten nguoi ban muon sua: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		Mchat conn;
		conn.Open();
		int id2 = conn.Seach_fr(newfr);
		if (id2 > 0) {
			if (conn.CheckFriend(conn.db, id, id2)) {
				name = new char;
				cout << "Nhap name: ";
				cin >> name;
				cout << "Nhap sex: ";
				cin >> sex;
				cout << "Nhap address: ";
				cin >> address;
				conn.Update_fr(conn.db,name,sex,address,id2);
			}
			else cout << "------You was friend ----------\n\n\n";
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
	}
	else cout << "----------Ban chua dang nhap.--------\n\n";
}
int Maccount::Detail_fr(int id) {
	if (check) {
		cout << "Nhap ten nguoi ban muon xem: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		Mchat conn;
		conn.Open();
		int id2 = conn.Seach_fr(newfr);
		if (id2 > 0) {
			if (conn.CheckFriend(conn.db, id, id2)) {
				conn.Detail_fr(conn.db, id2);
				Detail = true;
				zID2 = id2;
			}
			else { cout << "------You was friend ----------\n\n\n"; Detail = false;}
		}
		else { cout << "----Tai khoan khong ton tai-----------\n"; Detail = false;}
	}
	else cout << "----------Ban chua dang nhap.--------\n\n";
	return zID2;
}
void Maccount::Reply(int id) {
	if (RegisterHotKey(
		NULL,
		1,
		MOD_CONTROL | MOD_NOREPEAT,
		0x52)) 
	{
		cout << " Ctrl + R in Reply" << endl;
	}
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY)
		{
			char *mess, *dt;
			mess = new char;
			dt = new char;
			int tt = 1;
			Mchat conn;
			conn.Open();
			conn.update_tt(conn.db, id, zID2);
			cout << "Nhap Tin nhan: \n";
			cin.ignore();
			cin >> mess;
			time_t hientai = time(0);
			dt = ctime(&hientai);
			long int x;
			x = static_cast<int> (hientai);
			conn.WriteToMess(conn.db, id, zID2, mess, dt, tt, x);
			conn.ShowMessDetail(conn.db, id, zID2);
		}
		break;
	}
}
void Maccount::Detail_Reply(int id) {
	char *mess, *dt;
	mess = new char;
	dt = new char;
	int tt = 1;
	Mchat conn;
	conn.Open();
	conn.update_tt(conn.db, id, zID2);
	cout << "Nhap Tin nhan: \n";
	cin.ignore();
	cin >> mess;
	time_t hientai = time(0);
	dt = ctime(&hientai);
	long int x;
	x = static_cast<int> (hientai);
	conn.WriteToMess(conn.db, id, zID2, mess, dt, tt, x);
	conn.ShowMessDetail(conn.db, id, zID2);
}
