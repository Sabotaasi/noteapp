#include "stdafx.h"
#include "mysqlFunctions.h"
#include <mysql.h>
#include <iostream>

namespace mysql_functions
{
	/**
		Creates a new user into the database
		@param username string
		@param password string
		@returns int 1 success || 0 error
	*/
	int mysqlFunctions::createUser(string username, string password)
	{
		/* Initialize mysql variables */
		MYSQL *conn;
		MYSQL_RES *res;
		MYSQL_ROW row;

		/* Initialize the connection */
		conn = mysql_init(NULL);
		
		/* Connect to database */
		if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0))
		{
			/* Return with error code */
			return 0;
		}

		/* Create the query string */
		string query = "INSERT INTO noteapp_users (username, password) VALUES ('" + username + "','" + password + "')";


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

		/* Return with success code */
		return 1;
	}

	/**
		Removes a user from the database
		@param userId int index of the user in the user table
		@returns int 1 success || 0 error
	*/
	int mysqlFunctions::deleteUser(int userId)
	{
		/* Initialize mysql variables */
		MYSQL *conn;
		MYSQL_RES *res;
		MYSQL_ROW row;

		/* Initialize the connection */
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

		/* Return with success code */
		return 1;
	}

	/**
		Writes a new message into the messages table
		using the user's own id to identify it.

		@param userId int
		@param message string the message to save
		@returns int 1 success || 0 error
	*/
	int mysqlFunctions::writeMessage(int userId, string message)
	{
		/* Initialize mysql variables */
		MYSQL *conn;
		MYSQL_RES *res;
		MYSQL_ROW row;

		/* Initialize the connection */
		conn = mysql_init(NULL);

		/* Connect to database */
		if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0))
		{
			/* Return with error code */
			return 0;
		}

		/* Create the query string */
		string query = "INSERT INTO noteapp_messages (user_id, message) VALUES (" + to_string(userId) + ",'" + message + "')";

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

		/* Return with success code */
		return 1;
	}

	/**
		Reads a message from the current user's messages
		@param id int the message's id
		@returns message string || error string
	*/
	string mysqlFunctions::readMessage(int id)
	{
		/* Initialize mysql variables */
		MYSQL *conn;
		MYSQL_RES *res;
		MYSQL_ROW row;

		/* String to hold the respond message */
		string message;

		/* Initialize the connection */
		conn = mysql_init(NULL);

		/* Connect to database */
		if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0))
		{
			/* Return with error code */
			return "0";
		}

		/* Create the query string */
		string query = "SELECT message FROM noteapp_messages WHERE id = " + to_string(id);

		/* Send SQL query */
		if (mysql_query(conn, query.c_str()))
		{
			/* Return with error code */
			return "0";
		}

		/* Fetch the result */
		res = mysql_store_result(conn);
		
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
		return "0";
	}


	/**
		Deletes a message from the current user's messages
		@param id int the message's id
		@returns int 1 success || 0 error
	*/
	int mysqlFunctions::deleteMessage(int id)
	{
		/* Initialize mysql variables */
		MYSQL *conn;
		MYSQL_RES *res;
		MYSQL_ROW row;

		/* Initialize the connection */
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

		/* Return with success code */
		return 1;
	}

	/**
		Lists all the messages of the current user
		@param userId int the user's user id
		@returns messages string list of messages with ';' as separator
	*/
	string mysqlFunctions::listMessages(int userId)
	{
		/* Initialize mysql variables */
		MYSQL *conn;
		MYSQL_RES *res;
		MYSQL_ROW row;

		/* String to hold the respond message */
		string messages = "";

		/* Initialize the connection */
		conn = mysql_init(NULL);

		/* Connect to database */
		if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0))
		{
			/* Return with error code */
			return "0";
		}

		/* Create the query string */
		string query = "SELECT id,message FROM noteapp_messages WHERE user_id = " + to_string(userId);

		/* Send SQL query */
		if (mysql_query(conn, query.c_str()))
		{
			/* Return with error code */
			return "0";
		}

		/* Fetch the result */
		res = mysql_store_result(conn);

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
		return "0";
	}

	/**
		Authenticate the user
		Check that the username and password pair are found from the database
		@param username string
		@param password string
		@returns int 1 success || 0 error
	*/
	int mysqlFunctions::authenticate(string username, string password)
	{

		
		/* Initialize mysql variables */
		MYSQL *conn;
		MYSQL_RES *res;
		MYSQL_ROW row;

		/* Initialize the connection */
		conn = mysql_init(NULL);

		/* Connect to database */
		if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0))
		{
			/* Return with error code */
			return 0;
		}

		/* Create the query string */
		string query = "SELECT id FROM noteapp_users WHERE username = '" + username + "' AND password = '" + password + "'";

		/* Send SQL query */
		if (mysql_query(conn, query.c_str()))
		{
			/* Close the connection */
			mysql_close(conn);

			/* Return with error code */
			return 0;
		}

		/* Fetch the result */
		res = mysql_store_result(conn);

		/* Check we got any results*/
		if (mysql_num_rows(res)==1)
		{
			/* Close the connection */
			mysql_close(conn);

			while ((row = mysql_fetch_row(res)) != NULL)
			{
				int id = atoi(row[0]);
				return id;
			}
			/* Return with successful code */
		}

		/* Close the connection */
		mysql_close(conn);

		/* Return with error code */
		return 0;
	}
	/**
	check if username exists
	@param username string
	@returns int 1 success || 0 error
	*/
	int mysqlFunctions::usernameExists(string username)
	{
		/* Initialize mysql variables */
		MYSQL *conn;
		MYSQL_RES *res;
		MYSQL_ROW row;
		
		/* Initialize the connection */
		conn = mysql_init(NULL);

		/* Connect to database */
		if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0))
		{
			/* Return with error code */
			return 0;
		}

		/* Create the query string */
		string query = "SELECT id FROM noteapp_users WHERE username = '" + username + "'";
		/* Send SQL query */
		if (mysql_query(conn, query.c_str()))
		{
			
			/* Close the connection */
			mysql_close(conn);

			/* Return with error code */
			return 0;
		}
		/* Fetch the result */
		res = mysql_store_result(conn);

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

