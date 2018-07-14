#pragma once
class Maccount
{
public:
	int  id;
	char *username;
	char *password;
	bool sex;
	char *birth;
	char *name;
	int address;
	int zID; // gan ID 
	bool check; // check dang nhap
	bool Detail;//kiem tra co bb
	int zID2; // gan ID2
public:
	Maccount();
	~Maccount();
	void SignIn();
	void SingUp();
	void SignOut();
	void ShowMess_send(int);
	void ShowMess_rec(int);
	int ShowMessDetail(int);
	void SendMess(int);
	void SendMess_ctr_l(int);
	void AddFriend(int);
	void ShowFriend(int);
	void BlockFriend(int);
	void Update_fr(int);
	int Detail_fr(int);
	void Reply(int);
	void Detail_Reply(int);
	void ShowFriend_ctr_C(int);
	void sapxepadd(int);
};

