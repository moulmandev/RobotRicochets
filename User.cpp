#include "User.h"

User::User(int id, std::string l, std::string p, std::string ps): idUser(id), gameNb(0), login(l), password(p), country(""), ratio(0){
	std::cout << "User Constructor" << std::endl;
}
User::User(): idUser(0), password(""), login(""), gameNb(0), country(""), ratio(0){
	std::cout << "User Constructor by default" << std::endl;
}

int User::getIdUser(){
	return idUser;
}


std::string User::getLogin() {
	return login;
}

std::string User::getPassword() {
	return password;
}

std::string User::getCountry() {
	return country;
}

void User::setCountry(std::string c) {
	country = c;
}

void User::setIdUser(int id) {
	idUser = id;
}

void User::setLogin(std::string l) {
	login = l;
}
void User::setPassword(std::string p) {
	password = p;
}

User::~User() {
	std::cout << "User destructor" << std::endl;
}