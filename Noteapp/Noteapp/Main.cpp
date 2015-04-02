#include <iostream>
#include "User.h"

using namespace std;
void printHelp();
#ifdef eng
string helpmsg = "help\nmsg\neng";
string failloginmsg = "Wrong username or password";
#else
string helpmsg = "help\nmsg\nfi";
string failloginmsg = "Vaara kayttajanimi tai salasana";
#endif

int main(int argc, char *argv[]) 
{
	if (argc >= 6 && string(argv[1]) == "-u" && string(argv[3]) == "-p"){
		User* user = new User(string(argv[2]), string(argv[3]));
		if (user->isLoggedIn() == 0){
			cout << failloginmsg << endl;
		}
		else{
			//kirjota uname,pw,id to registery
			if (argc == 6 && string(argv[5]) == "-nu"){
				//create user
				user->createMe();
			}
			else if (argc == 6 && string(argv[5]) == "-du"){
				//delete user
				user->deleteMe();
			}
			else if (argc == 7 && string(argv[5]) == "-w"){
				//write new
				user->writeNew(string(argv[6]));
			}
			else if (argc == 7 && string(argv[5]) == "-r"){
				//read id
				user->readMsg(atoi(argv[6]));
			}
			else if (argc == 7 && string(argv[5]) == "-d"){
				//delete id
				user->deleteMsg(atoi(argv[6]));
			}
			else if (argc == 6 && string(argv[5]) == "-l"){
				//list all
				user->listAllMsgs();
			}
			else{
				printHelp();
			}
		}
	}
	else if (argc == 2 && string(argv[1]) == "-lo"){
		//logout

	}
	else if (argc == 2 && string(argv[1]) == "-h"){
		printHelp();
	}
	else{
		printHelp();
	}



	getchar();
	return 0;
}

void printHelp(){
	cout << helpmsg << endl;
}