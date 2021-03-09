#pragma once
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include<string>
#include <Wt/WTable.h>
#include <Wt/WSelectionBox.h>

#include"Grid.h";
#include"Database.h"

using namespace Wt;

class AppWt : public WApplication
{
private:
	Wt::WContainerWidget* container;
	Database* db;
	Grid* grille;
public:

	AppWt(const WEnvironment& env);
	~AppWt();
	void showMenu();
	void startGame();
	void showRegles();
	void inscription();
	void login();
	void logout();
	void fctDisplayPrecomputeMinimumMoves(Grid* grille);
	void initializeBd();
	void resolutionAlgorithm(Grid* grille);
	void fctDisplayPath(vector<string> pathSolution);
	void displayUserStatistics(int id);
};

