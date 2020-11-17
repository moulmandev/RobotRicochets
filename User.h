#pragma once
#include <iostream>

class User {

public:
	User(int, bool, std::string, std::string);
	User();

	int getIdUser();
	bool getInvite();
	std::string getFirstName();
	std::string getLastName();

	void setIdUser(int);
	void setInvite(bool);
	void setPrenom(std::string);
	void setNom(std::string);

	~User();

private:
	int idUser;
	bool invite;
	std::string firstName;
	std::string lastName;

};
