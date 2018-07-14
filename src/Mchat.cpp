#include "Mchat.h"
#include <windows.h>
using namespace std;
Mchat::Mchat(){}
Mchat::~Mchat(){}
void Mchat::Open() {
	rc = sqlite3_open("w3.db", &db);
	if (rc) {
		cout << "Can't open database" << sqlite3_errmsg(db) << endl;
		exit(0);
	}else {}
}
int Mchat::Select_login(sqlite3 *db, char *us, char *pa) {
	int id = 0;
	szSQL = "SELECT * FROM  user WHERE username = ? and password = ? ";
	rc = sqlite3_prepare(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_text(stmt, 1, us, strlen(us), 0);
		sqlite3_bind_text(stmt, 2, pa, strlen(pa), 0);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return id;
}
void Mchat::Insert_Acc(sqlite3 *db, char *fn, char *ln,bool se, char *bir, char *na,int add) {
	szSQL = "insert into user (username, password,sex,birth,name,address) values (?,?,?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, fn, strlen(fn), 0);
		sqlite3_bind_text(stmt, 2, ln, strlen(ln), 0);
		sqlite3_bind_int(stmt, 3, se);
		sqlite3_bind_text(stmt, 4, bir, strlen(bir), 0);
		sqlite3_bind_text(stmt, 5, na, strlen(na), 0);
		sqlite3_bind_int(stmt, 6, add);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Mchat::SelectMess_receive(sqlite3 *db, int zID) {
	if (!db)return;
	szSQL = "select messenger.contend from messenger,user where user.id=messenger.idrec and user.id=?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, zID);
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			answer.push_back(string((const char *)sqlite3_column_text(stmt, 0)));
		}
		sqlite3_finalize(stmt);
		cout << "-----Danh sach tin nhan receive-------\n";
		for (list<std::string>::const_iterator it = answer.begin(); it != answer.end(); it++)
			cout << *it << endl;
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Mchat::SelectMess_send(sqlite3 *db, int zID) {
	if (!db)return;
	szSQL = "select messenger.contend from messenger,user where user.id=messenger.idsen and user.id=?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, zID);
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			answer.push_back(string((const char *)sqlite3_column_text(stmt, 0)));
		}
		sqlite3_finalize(stmt);
		cout << "-----Danh sach tin nhan send-------\n";
		for (list<std::string>::const_iterator it = answer.begin(); it != answer.end(); it++)
			cout << *it << endl;
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
int Mchat::Seach_fr(char *frien) {
	int id2 = -1;
	szSQL = "SELECT id FROM user WHERE username = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, frien, strlen(frien), 0);
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id2;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return id2;
}
void Mchat::ShowMessDetail(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	cout << "--------Detail--------\n";
	szSQL = "SELECT * FROM messenger,user WHERE(idsen = ? OR idsen = ?) AND(idrec = ? OR idrec = ?) and user.id = messenger.idsen";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	// cout << id1 << id2;
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, id1);
		sqlite3_bind_int(stmt, 4, id2);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			cout << string((const char *)sqlite3_column_text(stmt, 7)) << ": " << endl;
			cout << "	"<< string((const char *)sqlite3_column_text(stmt, 2)) << " - ";
			cout << string((const char *)sqlite3_column_text(stmt, 3)) << endl;

		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
bool Mchat::CheckFriend(sqlite3 *db, int id1, int id2) {
	int isFriend = 0;
	szSQL = "SELECT * FROM friend WHERE ( id1 = ? AND id2 = ?) OR ( id1 = ? AND id2 = ?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, id2);
		sqlite3_bind_int(stmt, 4, id1);
		// commit
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> isFriend;
			if (isFriend != 0) isFriend = 1;
			else isFriend = 0;
			sqlite3_finalize(stmt);
		}
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return isFriend;
}
bool Mchat::CheckBlock(sqlite3 *db, int id1, int id2) {
	int isblock = 0;
	if (!db)return 0;
	szSQL = "SELECT isblock FROM friend WHERE (id1 = ? AND id2 = ?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id2);
		sqlite3_bind_int(stmt, 2, id1);
		// commit
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> isblock;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return isblock;
}
void Mchat::WriteToFriend(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "INSERT INTO friend VALUES (?,?,?),(?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		int isblock = 0;
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, isblock);
		sqlite3_bind_int(stmt, 4, id2);
		sqlite3_bind_int(stmt, 5, id1);
		sqlite3_bind_int(stmt, 6, isblock);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Mchat::ShowFriend(sqlite3 *db, int id1) {
	cout << "-------List Friends-----------\n";
	if (!db)return;
	szSQL = "SELECT user.name FROM friend left JOIN messenger on messenger.idrec = Friend.id2 join user on user.id = Friend.id2 where id1 = ? AND isblock = 0 group by id2 order by time desc";
	//szSQL = "SELECT DISTINCT user.username FROM (SELECT * FROM friend where (id1 = ?) AND isblock = 0) as A LEFT JOIN user ON (A.id2 = user.id)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		// commit
		int a = 0;
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int cols = sqlite3_column_count(stmt);
			for (int i = 0; i <cols; i++) {
				a++;
				cout << a << ": ";
				printf("%s \n", sqlite3_column_text(stmt, i));
			}
		}
		sqlite3_finalize(stmt);
		cout << "-------------------------------------\n";
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
int Mchat::ShowaaFriend(sqlite3 *db, int id1,int n) {
	int id = 0;
	if (!db) return id;
	szSQL = "SELECT id FROM(SELECT * FROM friend where(id1 = ?) AND isblock = 0) as A LEFT JOIN user ON(A.id2 = user.id)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		// commit
		int a = 0;
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int cols = sqlite3_column_count(stmt);
			for (int i = 0; i <cols; i++) {
				a++;
				if (n==a) {
					stringstream str;
					str << sqlite3_column_text(stmt, 0);
					str >> id;
				}
			}
		}
		sqlite3_finalize(stmt);
		cout << "-------------------------------------\n";
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return id;
}
void Mchat::BlockFriend(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "UPDATE friend SET isblock = 1 WHERE id1 = ? AND id2 = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Mchat::WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *tim,int tt,int sec) {
	szSQL = "INSERT INTO messenger VALUES (?,?,?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_text(stmt, 3, mes, strlen(mes), 0);
		sqlite3_bind_text(stmt, 4, tim, strlen(tim), 0);
		sqlite3_bind_int(stmt, 5, tt);
		sqlite3_bind_int(stmt, 6, sec);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Mchat::update_tt(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "UPDATE messenger SET status = 0 WHERE idsen = ? AND idrec = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id2);
		sqlite3_bind_int(stmt, 2, id1);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
int Mchat::Select_all(sqlite3 *db,char *us) {
	int id = 0;
	szSQL = "select * from user where username = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_text(stmt, 1, us, strlen(us), 0);
		// commit
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id;
			sqlite3_finalize(stmt);
		}
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return id;
}
int Mchat::Select_mask(sqlite3 *db) {
	int id = 0;
	szSQL = "select max(id) from user";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id;
			sqlite3_finalize(stmt);
		}
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return id;
}
void Mchat::Insert_maskuser(sqlite3 *db, int id1,char *na,bool se,int add) {
	if (!db)return;
	szSQL = "INSERT INTO mask_user VALUES (?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		int isblock = 0;
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_text(stmt, 2, na,strlen(na),0);
		sqlite3_bind_int(stmt, 3, se);
		sqlite3_bind_int(stmt, 4, add);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Mchat::Update_fr(sqlite3 *db,char *na,bool se,int add,int id) {
	if (!db)return;
	szSQL = "UPDATE mask_user SET name = ?,sex=?,address=? WHERE id = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_text(stmt, 1, na, strlen(na), 0);
		sqlite3_bind_int(stmt, 2, se);
		sqlite3_bind_int(stmt, 3, add);
		sqlite3_bind_int(stmt, 4, id);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Mchat::Detail_fr(sqlite3 *db,int id2) {
	if (!db)return;
	szSQL = "select mask_user.name,sex,address from Friend,mask_user where Friend.id2=mask_user.id and id2 = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id2);
		// commit
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW)
		{
			int cols = sqlite3_column_count(stmt);
			for (int i = 0; i <cols; i++) {
				printf("%s: ", sqlite3_column_name(stmt, i));
				printf("%s \n", sqlite3_column_text(stmt, i));
			}
		}
		cout << "-------------------------------------\n";
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Mchat::sepxepadd(sqlite3 *db, int id) {
	if (!db)return;
	int n=0,temp=0;
	szSQL = "select * from user inner join Friend on user.id = Friend.id2 join address on address.id = user.address where id1 = ? order by address.name asc";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 10);
			str >> temp;
			if (n == temp) {
				cout << "	" << string((const char *)sqlite3_column_text(stmt, 1)) << " - " << endl;
			}
			else
			{
				n = temp;
				cout << string((const char *)sqlite3_column_text(stmt, 11)) << ": " << endl;
				cout << "	" << string((const char *)sqlite3_column_text(stmt, 1)) << endl;
			}
		}
		cout << "-------------------------------------\n";
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}