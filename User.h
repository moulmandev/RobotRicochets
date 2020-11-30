#pragma once
#include <iostream>
#include "Statistics.h"

class User {

public:
	User(int, bool, std::string, std::string, std::string);
	User();

	int getIdUser();
	bool getInvite();
	std::string getFirstName();
	std::string getLastName();

	void setIdUser(int);
	void setInvite(bool);
	void setPrenom(std::string);
	void setNom(std::string);
	void setPseudo(std::string);
	void displayUserStatistics();
	void displayUserIdentity();
	~User();

private:
	int idUser;
	bool invite;
	Statistics userStatistics;
	std::string firstName;
	std::string pseudo;
	std::string lastName;

};
