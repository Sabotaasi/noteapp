#include "User.h"
#include "mysqlFunctions.h"

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
	if (!mysql_functions::mysqlFunctions::usernameExists(this->username)){
		return mysql_functions::mysqlFunctions::createUser(this->username, this->password);
	}
	else{
		return 0;
	}
}
/**
Delte current user from database
@return 0 || 1, fail || success
*/
int User::deleteMe(){
	//save me
	return mysql_functions::mysqlFunctions::deleteUser(this->userId);

}
/**
Write new message to database
@param msg The actual message
@return msgId
*/
int User::writeNew(string msg){

	return mysql_functions::mysqlFunctions::writeMessage(this->userId, msg);
}
/**
Read message from database
@param id Message id
@return message
*/
string User::readMsg(int id){
	return mysql_functions::mysqlFunctions::readMessage(id);
}
/**
Delete message from database
@param id MsgId
@return 0 || 1, fail || success
*/
int User::deleteMsg(int id){
	return mysql_functions::mysqlFunctions::deleteMessage(id);
}
/**
Get all messages from user
@return messages
*/
string User::listAllMsgs(){
	return mysql_functions::mysqlFunctions::listMessages(this->userId);
}
/**
Check if userinfo authenticates from database
@return userId
*/
int User::authenticate(){
	return mysql_functions::mysqlFunctions::authenticate(this->username, this->password);
}

User::~User()
{
}
