#include <iostream>
#include "User.h"
#include <Windows.h>

using namespace std;

void printHelp();
#ifdef eng
string helpmsg = "-u (user) -p (password) /After first input saved to registery\n-lo (logout) /Log off\n-h (hjalp) / This hjalpmessage\n-nu (new user) /Creation of new account ex: -u erkki -p esim -nu\n-w (write) [string] / Write new message ex: -u erkki -p esim -w viesti tai -w viesti\n- r (read) [id] / Read message ex: -u erkki -p esim -r 1 tai -r 1\n-d (delete) [id] / Delete message ex: -u erkki -p esim -d 1 tai -d 1\n-l (list all) / List all messages ex: -u erkki -p esim -l tai -l\n-du (delete user) / Delete own account ex:: -u erkki -p esim -du tai -du\n";
string failloginmsg = "Wrong username or password";
string createfailmsg = "Username already exists";
string createsuccessmsg = "Account was succesfully created";
string registeryerrormsg = "Registry error";
string logoffmsg = "Logged off";
string deleteusrsuccess = "User deleted";
string deleteusrerror = "Failed to delete user";
string writemsgsuccess = "Message written";
string writemsgerror = "Failed to write message";
string deletemsgsuccess = "Message deleted";
string deletemsgerror = "Failed to delete message";
string errorreadmsg = "Failed to read message";
string errorlistmsgs = "Failed to list all messages";
#else
string helpmsg = "-u (user) -p (password) //Ensimmaisen syoton jalkeen tallentuu rekisteriin\n- lo(logout) /Kirjaudu ulos\n- h(hjalp) / Tama hjalpviesti\n- nu(new user) /Uuden kayttajan luonti esim: -u erkki -p esim -nu\n- w(write)[string] / Kirjoita uusi viesti esim: -u erkki -p esim -w viesti tai -w viesti\n- r(read)[id] / Lue viesti esim: -u erkki -p esim -r 1 tai -r 1\n- d(delete)[id] / Poista viesti esim: -u erkki -p esim -d 1 tai -d 1\n- l(list all) / Listaa kaikki viestit esim: -u erkki -p esim -l tai -l\n- du(delete user) / Poista oma kayttajatili esim: -u erkki -p esim -du tai -du\n";
string failloginmsg = "Vaara kayttajanimi tai salasana";
string createfailmsg = "Kayttajanimi on jo olemassa";
string createsuccessmsg = "Kayttajatilin luonti onnistui";
string registeryerrormsg = "Rekisterivirhe";
string logoffmsg = "Kirjauduttu ulos";
string deleteusrsuccess = "Kayttaja poistettu";
string deleteusrerror = "Kayttajan poisto epaonnistui";
string writemsgsuccess = "Viesti kirjoitettu";
string writemsgerror = "Viestin kirjoitus epaonnistui";
string deletemsgsuccess = "Viesti poistettu";
string deletemsgerror = "Viestin poisto epaonnistui";
string errorreadmsg = "Viestin luku epaonnistui";
string errorlistmsgs = "Viestien luku epaonnistui";
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

	//luodaan user olio rekisteritiedoista tai 0,0 (tyhjä)
	User* user = new User(uname, pw);
	if (argc > 1 && string(argv[1]) == "-u" && string(argv[3]) == "-p"){
		//jos käyttäjä syöttää tunnuksen ja salasanan, korvataan user olion tiedot niillä
		uname = string(argv[2]);
		pw = string(argv[4]);
		user = new User(uname, pw);
		offset = 4;
		if (argc > 1 + offset && string(argv[offset + 1]) == "-nu"){
			//create user
			if (user->createMe() != 0){
				cout << createsuccessmsg << endl;
				//kirjoita rekisteriin tunnarit
				RegSetValueExA(key, "muistio_password", 0, REG_SZ, (const BYTE*)pw.c_str(), pw.length() + 1);
				RegSetValueExA(key, "muistio_username", 0, REG_SZ, (const BYTE*)uname.c_str(), uname.length() + 1);
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
		cout << logoffmsg << endl;
		return 0;
	}
	else if (argc > 1 && string(argv[1]) == "-h"){
		//hjap
		printHelp();
		return 0;
	}
	int userId = user->authenticate();
	
	if (userId != 0){
		//kirjoita rekisteriin tunnarit
		RegSetValueExA(key, "muistio_password", 0, REG_SZ, (const BYTE*)pw.c_str(), pw.length() + 1);
		RegSetValueExA(key, "muistio_username", 0, REG_SZ, (const BYTE*)uname.c_str(), uname.length() + 1);
		user->setUserId(userId);
		if (argc > 1 + offset && string(argv[offset + 1]) == "-du"){
			//delete user
			int error = user->deleteMe();
			RegSetValueExA(key, "muistio_password", 0, REG_SZ, (const BYTE*)"0", 1);
			RegSetValueExA(key, "muistio_username", 0, REG_SZ, (const BYTE*)"0", 1);
			if (error == 1){
				cout << deleteusrsuccess << endl;
			}
			else{
				cout << deleteusrerror << endl;
			}
		}
		else if (argc > 1 + offset && string(argv[offset + 1]) == "-w"){
			//write new
			int error = user->writeNew(string(argv[offset + 2]));
			if (error == 1){
				cout << writemsgsuccess << endl;
			}
			else{
				cout << writemsgerror << endl;
			}
		}
		else if (argc > 1 + offset && string(argv[offset + 1]) == "-r"){
			//read id
			string msg = user->readMsg(atoi(argv[offset + 2]));
			if (!strcmp("0", msg.c_str())){
				cout << errorreadmsg << endl;
			}
			else{
				cout << msg << endl;
			}
			
		}
		else if (argc > 1 + offset && string(argv[offset + 1]) == "-d"){
			//delete id
			int error = user->deleteMsg(atoi(argv[offset + 2]));
			if (error == 1){
				cout << deletemsgsuccess << endl;
			}
			else{
				cout << deletemsgerror << endl;
			}
		}
		else if (argc > 1 + offset && string(argv[offset + 1]) == "-l"){
			//list all msgs of usr
			
			string messages = user->listAllMsgs();
			if (!strcmp("0", messages.c_str())){
				cout << errorlistmsgs << endl;
			}
			else{
				char buf[sizeof(messages)+1];
				strncpy(buf, messages.c_str(), sizeof(buf));
				buf[sizeof(buf)-1] = 0;
				char* token = strtok(buf, ";");
				while (token != NULL){
					cout << token << endl;
					token = strtok(NULL, ";");
				}
			}
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
}