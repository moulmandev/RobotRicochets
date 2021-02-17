#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include<Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WPaintDevice.h>
#include <Wt/WPaintedWidget.h>
#include <Wt/WPainter.h>
#include <Wt/WSpinBox.h>
#include "Game.h"
#include "Grid.h"
#include "User.h"

#include <Wt/WTemplate.h>

#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WMenu.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WTextArea.h>

#include <Wt/WTable.h>
#include <Wt/WTableCell.h>
#include <Wt/WLineEdit.h>
#include <Wt/WText.h>
#include <Wt/WTableView.h>
#include <Wt/WCssDecorationStyle.h>

#include <Wt/WApplication.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WAbstractItemModel.h>
#include <Wt/WColor.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WFont.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WStandardItemModel.h>
#include <Windows.h>
#include <Wt/WHBoxLayout.h>
#include <cmath>


using namespace std;


Grid* grille;


class HelloApplication : public Wt::WApplication
{
public:
	HelloApplication(const Wt::WEnvironment& env);

	void menuPrincipalAlgorithmeResolution() {

		setTitle("Resolution algorithme");
		HWND hd = GetDesktopWindow();
		RECT rect;
		
		GetWindowRect(hd, &rect);
		int window_width = (rect.right - rect.left);
		int window_height = (rect.bottom - rect.top);

		root()->resize(window_width, window_height);//Mettre taille ecran
		Wt::WCssDecorationStyle decorationPage;
		decorationPage.setBackgroundColor(Wt::WColor::WColor(135, 233, 144, 255));
		//decorationPage.setBackgroundImage("C:/Users/33660/Desktop/technology.jpg");

		root()->setDecorationStyle(decorationPage);
		Wt::WText* pageTitle = root()->addWidget(std::make_unique<Wt::WText>(Wt::WString("<p>Resolution d'algorithme</p>")));
		Wt::WFont fontTitle;

		fontTitle.setFamily(Wt::FontFamily::Monospace, "'Courier New'");
		fontTitle.setSize(45);

		pageTitle->decorationStyle().setFont(fontTitle);

		Wt::WText* ExplanationsPage = root()->addWidget(std::make_unique<Wt::WText>(Wt::WString("<p>Choisissez l'action que vous souhaitez effectuer : </p>")));
		Wt::WFont fontExplanations;
		fontExplanations.setFamily(Wt::FontFamily::Fantasy, "'Western'");
		fontExplanations.setSize(12);
		ExplanationsPage->decorationStyle().setFont(fontExplanations);

		btnPrecomputeMinMoves = root()->addWidget(std::make_unique<Wt::WPushButton>("Precompute minimum moves"));		
		btnSolutionPath = root()->addWidget(std::make_unique<Wt::WPushButton>("Shortest path"));
		btnSolutionPath->decorationStyle().setBackgroundColor(Wt::WColor::WColor(220, 220, 220, 155));
		btnPrecomputeMinMoves->decorationStyle().setBackgroundColor(Wt::WColor::WColor(220, 220, 220, 155));


		auto precomputeMinimumMovesArray = [this] {
			btnPrecomputeMinMoves->setEnabled(false);
			btnSolutionPath->setEnabled(true);
			fctDisplayPrecomputeMinimumMoves();		
		};

		auto pathArray = [this]{
			btnSolutionPath->setEnabled(false);
			table->clear();
			btnPrecomputeMinMoves->setEnabled(true);
			fctDisplayPath();
		};

		btnPrecomputeMinMoves->clicked().connect(precomputeMinimumMovesArray);
		
		btnSolutionPath->clicked().connect(pathArray);
	}
	
	void fctDisplayPrecomputeMinimumMoves() {
		
		Wt::WCssDecorationStyle PrecomputeMinimumArrayStyle;
		PrecomputeMinimumArrayStyle.setBackgroundColor(Wt::WColor::WColor(220, 220, 220, 155));

		table->setDecorationStyle(PrecomputeMinimumArrayStyle);

		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {				
				if (grille->getPrecomputeMinimumMovesArray()[i * 16 + j] != INT_MAX && grille->getPrecomputeMinimumMovesArray()[i * 16 + j] != 0) {
					table->elementAt(i, j)->addNew<Wt::WText>(to_string(grille->getPrecomputeMinimumMovesArray()[i * 16 + j]));
				}
				else if (grille->getPrecomputeMinimumMovesArray()[i * 16 + j] ==0) {
					table->elementAt(i, j)->addNew<Wt::WText>("X");
				}
				else {
					table->elementAt(i, j)->addNew<Wt::WText>("");
				}
			}
		}
	
	}	

	void fctDisplayPath() {
		root()->refresh();///////////TROUVER AUTRE

		
		path.push_back('t');
		path.push_back('d');
		path.push_back('l');
		path.push_back('r');

		Wt::WCssDecorationStyle textTop;
		Wt::WCssDecorationStyle textDown;
		Wt::WCssDecorationStyle textLeft;
		Wt::WCssDecorationStyle textRight;

		textTop.setForegroundColor(Wt::WColor(255, 140, 0, 155));
		textDown.setForegroundColor(Wt::WColor(0, 255, 0, 155));
		textLeft.setForegroundColor(Wt::WColor(255, 0, 0, 155));
		textRight.setForegroundColor(Wt::WColor(0, 0, 255, 155));
	
		for (int i = 0; i < path.size(); i++){
			cout << "On rentre " << endl;
			if (path.at(i) == 't') {
				root()->addWidget(std::make_unique<Wt::WText>("Top\n"))->setDecorationStyle(textTop);
			}
			else if (path.at(i) == 'd') {
				root()->addWidget(std::make_unique<Wt::WText>("Down\n"))->setDecorationStyle(textDown);
			}
			else if (path.at(i) == 'l') {
				root()->addWidget(std::make_unique<Wt::WText>("Left\n"))->setDecorationStyle(textLeft);
			}
			else if (path.at(i) == 'r') {
				root()->addWidget(std::make_unique<Wt::WText>("Right\n"))->setDecorationStyle(textRight);
			}
		}
	}

private:
	
	Wt::WTable* table = root()->addWidget(std::make_unique<Wt::WTable>());
	Wt::WPushButton* btnPrecomputeMinMoves;
	Wt::WPushButton* btnSolutionPath;
	vector <char> path;
};


HelloApplication::HelloApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env)
{

	menuPrincipalAlgorithmeResolution();

}


int main(int argc, char** argv) {

	grille = new Grid();
	vector <char> path;
	grille->principalSearch(path);

	/*grille->afficherGrille();
	vector <char> path;
	grille->principalSearch(path);

	color selectColor;
	char selectColorC;*/

	/*while (1) {
		cout << "Choisir une couleur (r/g/b/y) :";
		cin >> selectColorC;
		switch (selectColorC)

		{

		case 'r':
			selectColor = red;
			break;

		case 'g':
			selectColor = green;
			break;

		case 'b':
			selectColor = blue;
			break;

		case 'y':
			selectColor = yellow;
			break;

		}
		char selectDir;
		cout << "Choisir une direction (z/q/s/d) :";
		cin >> selectDir;


		grille->deplacerRobot(selectColor, selectDir);
		cout << endl << endl;
		grille->afficherGrille();
		cout << endl << endl;
	}*/

	/*User* u = new User[2];
	u[0].setIdUser(1);
	u[0].setNom("Dupont");
	u[0].setPrenom("Paul");
	u[0].setInvite(0);
	u[0].setPseudo("PseudoPaul");

	u[1].setIdUser(2);
	u[1].setNom("Dupons");
	u[1].setPrenom("Jean");
	u[1].setInvite(1);
	u[1].setPseudo("PseudoJean");
	cout << "Tout fait " << endl;*/


	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
	return std::make_unique<HelloApplication>(env);
	});
}