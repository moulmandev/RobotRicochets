#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include<Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include "Game.h"
#include "Grid.h"
#include "User.h"


using namespace std;
class HelloApplication : public Wt::WApplication
{
public:
	HelloApplication(const Wt::WEnvironment& env);

private:
	Wt::WLineEdit* nameEdit;
	Wt::WText* greeting;
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env)
{
	setTitle("Hello world");

	root()->addWidget(makeunique<Wt::WText>("Your name, please? "));
	nameEdit = root()->addWidget(std::make_unique<Wt::WLineEdit>());
	Wt::WPushButton* button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
	root()->addWidget(makeunique<Wt::WBreak>());
	greeting = root()->addWidget(makeunique<Wt::WText>());
	auto greet = [this] {
		greeting->setText("Hello there, " + nameEdit_->text());
	};
	button->clicked().connect(greet);
}


int main(int argc, char** argv) {

	Grid* grille = new Grid();
	grille->afficherGrille();

	color selectColor;
	char selectColorC;

	while (1) {
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
	}

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

	Robot* r = new Robot(2);
	Game* g = new Game(u, 4, 2);
	g->getMap()->oneDtoTwoD();*/



	/*return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
	return std::make_unique<HelloApplication>(env);
	});*/
}