#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include "Game.h"
#include "Grid.h"
#include "User.h"

using namespace std;
//MODIF
class HelloApplication : public Wt::WApplication
{
public:
	HelloApplication(const Wt::WEnvironment& env);

private:
	Wt::WLineEdit* nameEdit_;
	Wt::WText* greeting_;
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env)
{
	setTitle("Hello world");

	root()->addWidget(std::make_unique<Wt::WText>("Your name, please? "));
	nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
	Wt::WPushButton* button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
	root()->addWidget(std::make_unique<Wt::WBreak>());
	greeting_ = root()->addWidget(std::make_unique<Wt::WText>());
	auto greet = [this] {
		greeting_->setText("Hello there, " + nameEdit_->text());
	};
	button->clicked().connect(greet);
}





int main(int argc, char** argv){

	Grid* grille = new Grid();
	grille->afficherGrille();

	//User* u = new User[2];
	//u[0].setIdUser(1);
	//u[0].setNom("Dupont");
	//u[0].setPrenom("Paul");
	//u[0].setInvite(0);
	//u[0].setPseudo("PseudoPaul");

	//u[1].setIdUser(2);
	//u[1].setNom("Dupons");
	//u[1].setPrenom("Jean");
	//u[1].setInvite(1);
	//u[1].setPseudo("PseudoJean");

	//Game g(u, 5, 2);

	////g.drawBoard();

	//cout << "Display user identity : " << endl;
	//u[0].displayUserIdentity();

	//return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
	//	return std::make_unique<HelloApplication>(env);
	//});
}