#include "Database.h"

using namespace std;



int Database::checkConnection(string login, string mdp) {

	sqlite3* DB;
	int exit = sqlite3_open(dir, &DB);

	string sql = "SELECT idUsers FROM Users WHERE login =";
	sql += "'";
	sql += login;
	sql += "'AND passwd =";
	sql += "'";
	sql += mdp;
	sql += "';";

	struct sqlite3_stmt* selectstmt;
	int result = sqlite3_prepare_v2(DB, sql.c_str(), -1, &selectstmt, NULL);
	if (result == SQLITE_OK)
	{
		if (sqlite3_step(selectstmt) == SQLITE_ROW)
		{
			int rc = sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
			cout << "RECORD FOUNDED::::::::::::::::::::::::::" << rc << endl;
			return 1;
		}
		else
		{
			cout << "RECORD NOT FOUNDED" << endl;
			return -1;
		}
	}
	sqlite3_finalize(selectstmt);
}

int Database::createDB() {
	sqlite3* DB;
	int exit = 0;

	exit = sqlite3_open(dir, &DB);
	sqlite3_close(DB);

	return 0;
}

int Database::addUserToDatabase(string login, string password, string country) {

	sqlite3* DB;
	char* messageError;
	int exit = sqlite3_open(dir, &DB);

	string sql = "INSERT INTO Users (login, passwd, country, gameNb, ratio) VALUES (";
	sql += "'";
	sql += login;
	sql += "','";
	sql += password;
	sql += "','";
	sql += country;
	sql += "',0, 1.0";
	sql += ");";

	//cout << "SQL vaut " << sql << endl;

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error create new user" << endl;
		sqlite3_free(messageError);
	}
	else {
		cout << "User added to the database" << endl;
	}
	return 0;
}


int Database::createTable(string sql) {
	sqlite3* DB;

	try {
		int exit = 0;
		exit = sqlite3_open(dir, &DB);

		char* messageErreur;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageErreur);

		if (exit != SQLITE_OK) {
			cerr << "Error create the table" << endl;
			sqlite3_free(messageErreur);
		}
		else {
			cout << "Table created " << endl;
		}
		sqlite3_close(DB);
	}
	catch (const exception& e) {
		cerr << e.what();
	}
	return 0;
}
