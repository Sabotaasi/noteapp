#include <iostream>
#include "User.h"
#include <Windows.h>

using namespace std;

void printHelp();
#ifdef eng
string helpmsg = "help\nmsg\neng";
string failloginmsg = "Wrong username or password";
string createfailmsg = "Username already exists";
string createsuccessmsg = "Account was succesfully created";
string registeryerrormsg = "Registry error";
#else
string helpmsg = "help\nmsg\nfi";
string failloginmsg = "Vaara kayttajanimi tai salasana";
string createfailmsg = "Kayttajanimi on jo olemassa";
string createsuccessmsg = "Kayttajatilin luonti onnistui";
string registeryerrormsg = "Rekisterivirhe";
#endif

int main(int argc, char *argv[])
{
	HKEY key;
	LONG nError;
	nError = RegOpenKey(HKEY_CURRENT_USER, TEXT("Software\\muistiosofta\\"), &key);
	if (nError == ERROR_FILE_NOT_FOUND)
	{
		nError = RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\muistiosofta\\"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
		if (nError){
			cout << registeryerrormsg << endl;
			return 0;
		}

	}
	int offset = 0;

	//lue rekisteristä tunnarit useriin
	string pw, uname;
	char username[1024];
	DWORD u_size = sizeof(username);
	DWORD u_type = REG_SZ;
	nError = RegQueryValueExA(key, "muistio_username", NULL, &u_type, (LPBYTE)&username, &u_size);
	if (nError == ERROR_FILE_NOT_FOUND){
		uname = '0';
	}
	else{
		uname = string(username);
	}


	char password[1024];
	DWORD p_size = sizeof(password);
	DWORD p_type = REG_SZ;
	nError = RegQueryValueExA(key, "muistio_password", NULL, &p_type, (LPBYTE)&password, &p_size);
	if (nError == ERROR_FILE_NOT_FOUND){
		pw = "0";
	}
	else{
		pw = string(password);
	}

	User* user = new User(uname, pw);
	if (argc > 1 && string(argv[1]) == "-u" && string(argv[3]) == "-p"){
		//login
		uname = string(argv[2]);
		pw = string(argv[4]);
		user = new User(uname, pw);
		offset = 4;
		if (argc > 1 + offset && string(argv[offset + 1]) == "-nu"){
			//create user
			if (user->createMe() != 0){
				cout << createsuccessmsg << endl;
			}
			else{
				cout << createfailmsg << endl;
			}
			return 0;
		}
	}
	else if (argc > 1 && string(argv[1]) == "-lo"){
		RegSetValueExA(key, "muistio_password", 0, REG_SZ, (const BYTE*)"0", 1);
		RegSetValueExA(key, "muistio_username", 0, REG_SZ, (const BYTE*)"0", 1);
		return 0;
	}
	else if (argc > 1 && string(argv[1]) == "-h"){
		//hjap
		printHelp();
		return 0;
	}

	if (user->isLoggedIn() != 0){
		//kirjoita rekisteriin tunnarit
		RegSetValueExA(key, "muistio_password", 0, REG_SZ, (const BYTE*)pw.c_str(), pw.length() + 1);
		RegSetValueExA(key, "muistio_username", 0, REG_SZ, (const BYTE*)uname.c_str(), uname.length() + 1);

		if (argc > 1 + offset && string(argv[offset + 1]) == "-du"){
			//delete user
			user->deleteMe();
			RegSetValueExA(key, "muistio_password", 0, REG_SZ, (const BYTE*)"0", 1);
			RegSetValueExA(key, "muistio_username", 0, REG_SZ, (const BYTE*)"0", 1);
		}
		else if (argc > 1 + offset && string(argv[offset + 1]) == "-w"){
			//write new
			user->writeNew(string(argv[offset + 2]));
		}
		else if (argc > 1 + offset && string(argv[offset + 1]) == "-r"){
			//read id
			user->readMsg(atoi(argv[offset + 2]));
		}
		else if (argc > 1 + offset && string(argv[offset + 1]) == "-d"){
			//delete id
			user->deleteMsg(atoi(argv[offset + 2]));
		}
		else if (argc > 1 + offset && string(argv[offset + 1]) == "-l"){
			//list all
			user->listAllMsgs();
		}
		else{
			printHelp();
		}

	}
	else{
		cout << failloginmsg << endl;
	}
	return 0;
}

void printHelp(){
	cout << helpmsg << endl;
	getchar();
}