#include "User.h"


User::User()
{
}
/**
Create user
@param username Username
@param password Password
@return User
*/
User::User(string username, string password)
{
	this->username = username;
	this->password = password;
}
/**
Create current user into database
@return userId
*/
int User::createMe(){
	//save me
	return 0;
}
/**
Delte current user from database
@return 0 || 1, fail || success
*/
int User::deleteMe(){
	//save me
	return 0;
}
/**
Write new message to database
@param msg The actual message
@return msgId
*/
int User::writeNew(string msg){
	return 0;
}
/**
Read message from database
@param id Message id
@return message
*/
string User::readMsg(int id){
	return "";
}
/**
Delete message from database
@param id MsgId
@return 0 || 1, fail || success
*/
int User::deleteMsg(int id){
	return 0;
}
/**
Get all messages from user
@return messages
*/
string User::listAllMsgs(){
	return "";
}
/**
Check if userinfo authenticates from database
@return userId
*/
int User::isLoggedIn(){
	return 1;
}

User::~User()
{
}
