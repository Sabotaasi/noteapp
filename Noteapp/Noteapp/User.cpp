#include "User.h"


User::User()
{
}
User::User(string username,string password)
{
	this->username = username;
	this->password = password;
}
int User::createMe(){
	//save me
	return 0;
}
int User::deleteMe(){
	//save me
	return 0;
}
int User::writeNew(string msg){
	return 0;
}
string User::readMsg(int id){
	return "";
}
int User::deleteMsg(int id){
	return 0;
}
string User::listAllMsgs(){
	return "";
}
int User::isLoggedIn(){
	return 0;
}
User::~User()
{
}
