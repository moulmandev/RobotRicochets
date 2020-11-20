#include "User.h"

User::User(int id, bool i, std::string p, std::string n) : idUser(i), invite(i), firstName(p), lastName(n), userStatistics(){
	std::cout << "User Constructor" << std::endl;
}
User::User(): idUser(0), invite(0), firstName(""), lastName(""){
	std::cout << "User Constructor by default" << std::endl;
}

int User::getIdUser(){
	return idUser;
}

bool User::getInvite() {
	return invite;
}

std::string User::getLastName() {
	return lastName;
}

std::string User::getFirstName() {
	return firstName;
}

void User::setIdUser(int id) {
	idUser = id;
}
void User::setInvite(bool i) {
	invite = i;
}
void User::setPrenom(std::string p) {
	firstName = p;
}
void User::setNom(std::string n) {
	lastName = n;
}

void User::displayUserStatistics() {
	std::cout << "Statistiques de " << lastName << " " << firstName << " :" <<std::endl;
	userStatistics.displayStatistics();
}

User::~User() {
	std::cout << "User destructor" << std::endl;
}