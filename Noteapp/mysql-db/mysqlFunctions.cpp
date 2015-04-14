#include "stdafx.h"
#include "mysqlFunctions.h"
#include <mysql.h>

namespace mysql_functions
{
	/**
		Creates a new user into the database
		@param username string
		@param password string
		@returns int 
	*/
	int mysqlFunctions::createUser(string username, string password)
	{
		/* Initialize mysql variables */
		MYSQL *conn;
		MYSQL_RES *res;
		MYSQL_ROW row;

		conn = mysql_init(NULL);
		
		/* Connect to database */
		if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0))
		{
			/* Return with error code */
			return 0;
		}

		/* Create the query string */
		string query = "INSERT INTO noteapp_users (username, password) VALUES (" + username + "," + password + ")";


		/* Send SQL query */
		if (mysql_query(conn, query.c_str()))
		{
			/* Return with error code */
			return 0;
		}
		mysql_close(conn);

		return 1;
	}

	int mysqlFunctions::deleteUser(int userId)
	{
		return 0;
	}

	int mysqlFunctions::writeMessage(int userId, string message)
	{
		return 0;
	}

	string mysqlFunctions::readMessage(int id)
	{
		return "fail";
	}

	int mysqlFunctions::deleteMessage(int id)
	{
		return 0;
	}

	string mysqlFunctions::listMessages(int userId)
	{
		return "fail";
	}

	int mysqlFunctions::authenticate(string username, string password)
	{
		return 0;
	}
}

