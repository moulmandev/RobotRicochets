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
#include <Wt/WTableView.h>

#include <cmath>


using namespace std;


Grid* grille;


class HelloApplication : public Wt::WApplication
{
public:
	HelloApplication(const Wt::WEnvironment& env);

	void fct() {

		/*auto tableView = cpp14::make_unique<WTableView>();
		tableView->setModel(csvToModel(WApplication::appRoot() + "table.csv"));

		tableView->setColumnResizeEnabled(false);
		tableView->setColumnAlignment(0, AlignmentFlag::Center);
		tableView->setHeaderAlignment(0, AlignmentFlag::Center);
		tableView->setAlternatingRowColors(true);
		tableView->setRowHeight(28);
		tableView->setHeaderHeight(28);
		tableView->setSelectionMode(SelectionMode::Single);
		tableView->setEditTriggers(EditTrigger::None);*/


		/*cptClick++;
		table->setWidth(Wt::WLength("100%"));

		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				table->elementAt(i, j)->setColumnSpan());
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
		}*/
	}


private:
	Wt::WLineEdit* nameEdit;
	Wt::WText* greeting;
	Wt::WTable* table = root()->addWidget(std::make_unique<Wt::WTable>());
	Wt::WTableView* table2 = root()->addWidget(std::make_unique<Wt::WTableView>());

	int cptClick = 0;

};


HelloApplication::HelloApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env)
{
	setTitle("Resolution algorithme");

	

	Wt::WPushButton* btnPrecomputeMinMoves = root()->addWidget(std::make_unique<Wt::WPushButton>("Precompute minimum moves"));
	Wt::WPushButton* btnSolutionPath = root()->addWidget(std::make_unique<Wt::WPushButton>("Shortest path"));

	
	auto precomputeMinimumMovesArray = [this] {
		fct();
	};

	btnPrecomputeMinMoves->clicked().connect(precomputeMinimumMovesArray);
	btnSolutionPath->clicked().connect("Path le plus court");
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