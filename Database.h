#pragma once
#include <sqlite3.h>
#include "constants.h"

#include <iostream>

class Database {
public:
	int checkConnection(std::string login, std::string mdp);
	int callback(void* notUsed, int argc, char** argv, char** azColName);
	int createDB();
	int addUserToDatabase(std::string login, std::string password);
	int createTable(std::string sql);

private:
	const char* dir = "c:/Users/33660/Desktop/databaseRicochetRobots.db";
};
