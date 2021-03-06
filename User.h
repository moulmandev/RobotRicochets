#pragma once
#include <iostream>
#include <Wt/Dbo/Dbo.h>
#include "Statistics.h"

namespace dbo = Wt::Dbo;

class User {

public:
	User(int id, std::string l, std::string p, std::string ps);
	User();

	int getIdUser();
	std::string getLogin();
	std::string getPassword();
	std::string getCountry();

	void setIdUser(int);
	void setLogin(std::string);
	void setCountry(std::string);
	void setPassword(std::string);

	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a, login, "login");
		dbo::field(a, password, "password");
		dbo::field(a, gameNb, "gameNb");
		dbo::field(a, country, "country");
		dbo::field(a, ratio, "ratio");
	};

	~User();

private:
	int idUser;
	std::string password;
	std::string login;
	std::string country;
	int gameNb;
	float ratio;
};
