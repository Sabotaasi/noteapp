#pragma once
#include <string>
using namespace std;

class User
{
public:
	User();
	User(string username, string password);
	~User();
	string getUsername(){ return this->username; }
	void setUsername(string username){ this->username = username; }
	void setPassword(string password){ this->password = password; }
	int createMe();
	int deleteMe();
	int writeNew(string msg);
	string readMsg(int id);
	int deleteMsg(int id);
	string listAllMsgs();
	int isLoggedIn();
private:
	string username;
	string password;

};

