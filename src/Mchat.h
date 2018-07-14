#pragma once
#include <iostream>
#include <sqlite3.h>
#include<stdc++.h>
using namespace std;
class Mchat
{
public:
	Mchat();
	~Mchat();
public:
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	const char *szSQL;
	const char *pzTest;
	sqlite3_stmt *stmt;
	list<string> answer;
public:
	void Open();
	int Select_login(sqlite3 *db, char *fn, char *ln);
	void Insert_Acc(sqlite3 *db, char *, char *,bool,char *,char *,int);
	void SelectMess_send(sqlite3 *db, int id);
	void SelectMess_receive(sqlite3 *db, int id);
	int Seach_fr(char *frien);
	void ShowMessDetail(sqlite3 *db, int id1, int id2);
	bool CheckFriend(sqlite3 *db, int id1, int id2);
	bool CheckBlock(sqlite3 *db, int id1, int id2);
	void WriteToFriend(sqlite3 *db, int id1, int id2);
	void ShowFriend(sqlite3 *db, int id1);
	void BlockFriend(sqlite3 *db, int id1, int id2);
	void WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *tim,int tt, int sec);
	void update_tt(sqlite3 *db, int id1, int id2);
	int Select_all(sqlite3 *db,char *us);
	int Select_mask(sqlite3 *db);
	void Insert_maskuser(sqlite3 *db, int id1,char *,bool, int add);
	void Update_fr(sqlite3 *db, char *na, bool se, int add, int id);
	void Detail_fr(sqlite3 *db,int id2);
	int ShowaaFriend(sqlite3 *db, int id1, int n);
	void sepxepadd(sqlite3 *db, int id1);
};

