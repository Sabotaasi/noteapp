#pragma once
#define DEX __declspec(dllexport)
#define SERVER "niisku.lamk.fi"
#define USER "heinhei1"
#define PASSWORD "Koodaus1"
#define DATABASE "user_heinhei1"

#include <string>
#include <mysql.h>
using namespace std;

namespace mysql_functions
{
	class mysqlFunctions
	{
	public:
		static DEX int createUser(string username, string password);
		static DEX int deleteUser(int userId);
		static DEX int writeMessage(int userId, string message);
		static DEX string readMessage(int id);
		static DEX int deleteMessage(int id);
		static DEX string listMessages(int userId);
		static DEX int authenticate(string username, string password);
	};
}


