#pragma once
#include <sqlite3.h>
#include "constants.h"

#include <iostream>
using namespace std;

class Database {
public:
	int checkConnection(std::string login, std::string mdp);
	static int callback(void* notUsed, int argc, char** argv, char** azColName) {
		cout << "DANS CALLBACK " << endl;
		for (int i = 0; i < argc; i++) {
			cout << azColName[i] << ": " << argv[i] << endl;
		}
		cout << endl;
		return 0;
	}

	int createDB();
	int addUserToDatabase(std::string, std::string, std::string);
	int createTable(std::string sql);

private:
	const char* dir = "c:/Users/33660/Desktop/databaseRicochetRobots.db";
};
