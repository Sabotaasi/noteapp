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
			/* Close the connection */
			mysql_close(conn);

			/* Return with error code */
			return 0;
		}
		
		/* Close the connection */
		mysql_close(conn);

		return 1;
	}

	/**
		Removes a user from the database
		@param userId int
		@returns int
	*/
	int mysqlFunctions::deleteUser(int userId)
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
		string query = "DELETE FROM noteapp_users WHERE id = " + to_string(userId);

		/* Send SQL query */
		if (mysql_query(conn, query.c_str()))
		{
			/* Close the connection */
			mysql_close(conn);

			/* Return with error code */
			return 0;
		}

		/* Close the connection */
		mysql_close(conn);

		return 1;
	}

	int mysqlFunctions::writeMessage(int userId, string message)
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
		string query = "INSERT INTO noteapp_messages (user_id, message) VALUES (" + to_string(userId) + "," + message + ")";

		/* Send SQL query */
		if (mysql_query(conn, query.c_str()))
		{
			/* Close the connection */
			mysql_close(conn);

			/* Return with error code */
			return 0;
		}

		/* Close the connection */
		mysql_close(conn);

		return 1;
	}

	string mysqlFunctions::readMessage(int id)
	{
		/* Initialize mysql variables */
		MYSQL *conn;
		MYSQL_RES *res;
		MYSQL_ROW row;

		/* String to hold the respond message */
		string message;

		conn = mysql_init(NULL);

		/* Connect to database */
		if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0))
		{
			/* Return with error code */
			return 0;
		}

		/* Create the query string */
		string query = "SELECT message FROM noteapp_messages WHERE id = " + to_string(id);

		/* Send SQL query */
		if (mysql_query(conn, query.c_str()))
		{
			/* Return with error code */
			return 0;
		}

		/* Fetch the result */
		res = mysql_use_result(conn);

		/* Make sure we only got one row */
		if (mysql_num_rows(res) == 1)
		{
			while ((row = mysql_fetch_row(res)) != NULL)
			{
				message = row[0];
			}

			/* Close the connection */
			mysql_close(conn);

			/* Return the message */
			return message;
		}

		/* Return with error */
		return "Multiple rows returned";
	}

	int mysqlFunctions::deleteMessage(int id)
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
		string query = "DELETE FROM noteapp_messages WHERE id = " + to_string(id);

		/* Send SQL query */
		if (mysql_query(conn, query.c_str()))
		{
			/* Close the connection */
			mysql_close(conn);

			/* Return with error code */
			return 0;
		}

		/* Close the connection */
		mysql_close(conn);

		return 1;
	}

	string mysqlFunctions::listMessages(int userId)
	{
		/* Initialize mysql variables */
		MYSQL *conn;
		MYSQL_RES *res;
		MYSQL_ROW row;

		/* String to hold the respond message */
		string messages = "";

		conn = mysql_init(NULL);

		/* Connect to database */
		if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0))
		{
			/* Return with error code */
			return 0;
		}

		/* Create the query string */
		string query = "SELECT message FROM noteapp_messages WHERE user_id = " + to_string(userId);

		/* Send SQL query */
		if (mysql_query(conn, query.c_str()))
		{
			/* Return with error code */
			return 0;
		}

		/* Fetch the result */
		res = mysql_use_result(conn);

		/* Make sure we only got one row */
		if (mysql_num_rows(res))
		{
			while ((row = mysql_fetch_row(res)) != NULL)
			{
				messages = messages + row[0] + ":" + row[1] + ";";
			}

			/* Close the connection */
			mysql_close(conn);

			/* Return the list of messages */
			return messages;
		}

		/* Return with error */
		return "No rows returned";
	}

	int mysqlFunctions::authenticate(string username, string password)
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
		string query = "SELECT id FROM noteapp_users WHERE username = " + username + " AND password = " + password;

		/* Send SQL query */
		if (mysql_query(conn, query.c_str()))
		{
			/* Close the connection */
			mysql_close(conn);

			/* Return with error code */
			return 0;
		}

		/* Fetch the result */
		res = mysql_use_result(conn);

		/* Check we got any results*/
		if (mysql_num_rows(res))
		{
			/* Close the connection */
			mysql_close(conn);

			/* Return with successful code */
			return 1;
		}

		/* Close the connection */
		mysql_close(conn);

		/* Return with error code */
		return 0;
	}
}

