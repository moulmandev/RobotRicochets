#include"AppWt.h"

using namespace std;

/*#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include<Wt/WLineEdit.h>
#include "Database.h"
#include <Wt/WSelectionBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
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
#include <Wt/WText.h>
#include <Wt/WTableView.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WApplication.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WAbstractItemModel.h>
#include <Wt/WColor.h>
#include <Wt/WFont.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WFlags.h>
#include <Windows.h>
#include <cmath>
#include <Wt/WLineEdit.h>
#include <Wt/WMenu.h>
#include <Wt/WMessageBox.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPopupMenuItem.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WText.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <Wt/WContainerwidget.h>
#include "stdio.h"
#include <Wt/WIntValidator.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTemplate.h>
#include <Wt/Chart/WPieChart.h>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WStandardItem.h>
#include <Wt/WTableView.h>

using namespace std;

class HelloApplication : public Wt::WApplication
{
public:
	HelloApplication(const Wt::WEnvironment& env);

	
	void SubscriptionForm() {
		root()->clear();

		Wt::WLineEdit* editLogin = root()->addNew<Wt::WLineEdit>();
		editLogin->setPlaceholderText("Login");

		Wt::WLineEdit* editPassword = root()->addNew<Wt::WLineEdit>();
		editPassword->setPlaceholderText("Mot de passe");


		Wt::WSelectionBox* sb1 = root()->addNew<Wt::WSelectionBox>();
		sb1->addItem("France");
		sb1->addItem("Belgique");
		sb1->addItem("Royaume-Unis");
		sb1->addItem("Espagne");
		sb1->addItem("Pays-bas");

		sb1->setCurrentIndex(1);
		sb1->setMargin(10, Wt::Side::Right);

		Wt::WPushButton* SubscriptionButton = root()->addNew<Wt::WPushButton>("Valider");

		SubscriptionButton->clicked().connect([=] {
			if (editLogin->text().empty() || editPassword->text().empty()){
				root()->addWidget(std::make_unique<Wt::WText>("Veuillez remplir tous les champs"));
			}
			else if (db->checkLogin(editLogin->text().toUTF8())){
				root()->addWidget(std::make_unique<Wt::WText>("Ce login est deja utilise, veuillez en choisir un autre"));
			}
			else {
				db->addUserToDatabase(editLogin->text().toUTF8(), editPassword->text().toUTF8(), sb1->currentText().toUTF8());
			}
		});
	}

	void afficherReglesJeu(){


		Wt::WText* pageTitle = root()->addWidget(std::make_unique<Wt::WText>(Wt::WString("<h1>Regles du jeu</h1>")));
		Wt::WFont fontTitle;

		fontTitle.setFamily(Wt::FontFamily::Monospace, "'Courier New'");
		fontTitle.setSize(12);

		pageTitle->decorationStyle().setFont(fontTitle); 
		Wt::WText* ExplanationsRules = root()->addWidget(std::make_unique<Wt::WText>("Trouvez le chemin le plus rapide pour emmener le robot objectif à la case object, en vous aidant des murs et de tous les autres robots\n Pour cela, cliquez sur l'un des robots, et indiquez là où vous souhaitez qu'il se dirige.\n"));
		Wt::WFont fontRules;
		fontRules.setFamily(Wt::FontFamily::Fantasy, "'Western'");
		fontRules.setSize(12);
		ExplanationsRules->decorationStyle().setFont(fontRules);		
		Wt::WText* textWarning = root()->addWidget(std::make_unique<Wt::WText>("Attention, votre robot ne pas s'arreter autre part que contre un mur ou contre un robot\n"));
		Wt::WFont fontWarning;
		fontWarning.setStyle(Wt::FontStyle::Italic);

		Wt::WImage* imageLogo = root()->addNew<Wt::WImage>(Wt::WLink("https://www.regledujeu.fr/wp-content/uploads/ricochet-robots-plateau.jpg"));//////////////////////////////METTRE PHOTO JEUU

	}
	
	
	void fctDisplayPrecomputeMinimumMoves(Grid* grille) {
		cout << "Dans fctDisplayPrecomputeMinimumMoves" << endl;

		Wt::WTable* table = root()->addWidget(std::make_unique<Wt::WTable>());		
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

	void displayUserStatistics(int id) {
		root()->clear();
		root()->addWidget(std::make_unique<Wt::WText>("Login\n"));
	}

	void connectionForm(){
		root()->clear();

		Wt::WLineEdit* editLogin = root()->addNew<Wt::WLineEdit>();
		editLogin->setPlaceholderText("Login");

		Wt::WLineEdit* editPassword = root()->addNew<Wt::WLineEdit>();
		editPassword->setPlaceholderText("Mot de passe");

		Wt::WPushButton* connectionButton = root()->addNew<Wt::WPushButton>();
		connectionButton->setText("Se connecter");

		Wt::WPushButton* subscriptionButton = root()->addNew<Wt::WPushButton>();
		subscriptionButton->setText("S'inscrire");

		Wt::WCssDecorationStyle connectionButtonDecoration;
		connectionButtonDecoration.setBackgroundColor(Wt::WColor::WColor(155,255,255,255));
		connectionButton->setDecorationStyle(connectionButtonDecoration);

		Wt::WCssDecorationStyle messageErreurConnectionDecoration;
		messageErreurConnectionDecoration.setBackgroundColor(Wt::WColor::WColor(255, 0, 0, 255));

		connectionButton->clicked().connect([=]{

			Wt::WString k = editLogin->text();
			Wt::WString g = editPassword->text();

			int idFounded = db->checkConnection(k.toUTF8(), g.toUTF8());

			if (idFounded !=-1) {
				cout << "Okk connection" << endl;
				cout << "On fait la connexion avec le user " << idFounded << endl;
				//displayUserPage(idFounded);
			}
			else {
				cout << "Login ou mot de passe incorrectes. Veuillez reessayer ou vous creer un compte\n" << endl;
				root()->addWidget(std::make_unique<Wt::WText>("Login ou mot de passe incorrectes. Veuillez reessayer ou vous creer un compte\n"));
			}
		});

		subscriptionButton->clicked().connect([=] {
			SubscriptionForm();
		});

	}

	void initializeBd() {

		db = new Database();
		db->createDB();
		db->createTable("DROP TABLE IF EXISTS Users;");

		db->createTable("CREATE TABLE IF NOT EXISTS Users("
			"idUsers INTEGER PRIMARY KEY,"
			"login VARCHAR(255),"
			"passwd VARCHAR(255),"
			"country VARCHAR(255),"
			"gameNb INT,"
			"ratio FLOAT"
			");");

		db->addUserToDatabase("swan.frere", "passwordSwan", "France");
		db->addUserToDatabase("mathilde.marza", "passwordMathilde", "Espagne");
		db->addUserToDatabase("simon.machado", "passwordSimon", "Royaume-Unis");
		db->addUserToDatabase("theo.escolano", "passwordTheo", "Pays-Bas");
	}	
	

	void displayUserPage(int idUser) {
		//Page statistics User
	}
	
	void resolutionAlgorithm(Grid* grille) {
		root()->clear();

		vector <char> path;
		vector <string> chemin = grille->principalSearch(path);

		cout << "ALGO FINI " << chemin.size() << endl;

		for (int i = 0; i< chemin.size(); i++) {
			cout << chemin[i] << endl;
		}

		setTitle("Resolution algorithme");
		HWND hd = GetDesktopWindow();
		RECT rect;

		GetWindowRect(hd, &rect);
		int window_width = (rect.right - rect.left);
		int window_height = (rect.bottom - rect.top);

		root()->resize(window_width, window_height);//Mettre taille ecran
		Wt::WCssDecorationStyle decorationPage;
		decorationPage.setBackgroundColor(Wt::WColor::WColor(135, 233, 144, 255));

		root()->setDecorationStyle(decorationPage);

		Wt::WText* pageTitle = root()->addWidget(std::make_unique<Wt::WText>(Wt::WString("<h1>Resolution d'algorithme</h1>")));
		Wt::WFont fontTitle;

		fontTitle.setFamily(Wt::FontFamily::Monospace, "'Courier New'");
		fontTitle.setSize(45);

		pageTitle->decorationStyle().setFont(fontTitle);

		Wt::WText* ExplanationsPage = root()->addWidget(std::make_unique<Wt::WText>(Wt::WString("<p>Choisissez l'action que vous souhaitez effectuer : </p>")));
		Wt::WFont fontExplanations;
		fontExplanations.setFamily(Wt::FontFamily::Fantasy, "'Western'");
		fontExplanations.setSize(12);
		ExplanationsPage->decorationStyle().setFont(fontExplanations);

		Wt::WPushButton* btnPrecomputeMinMoves = root()->addNew<Wt::WPushButton>("Precompute minimum moves");
		Wt::WPushButton* btnSolutionPath = root()->addNew<Wt::WPushButton>("Chemin le plus court");

		
		btnSolutionPath->decorationStyle().setBackgroundColor(Wt::WColor::WColor(220, 220, 220, 155));
		btnPrecomputeMinMoves->decorationStyle().setBackgroundColor(Wt::WColor::WColor(220, 220, 220, 155));

		btnSolutionPath->clicked().connect([=] {
			btnSolutionPath->setEnabled(false);
			btnPrecomputeMinMoves->setEnabled(true);
			fctDisplayPath(chemin);
		});

		btnPrecomputeMinMoves->clicked().connect([=] {
			btnPrecomputeMinMoves->setEnabled(false);
			btnSolutionPath->setEnabled(true);
			fctDisplayPrecomputeMinimumMoves(grille);
		});
	
	}

	void fctDisplayPath(vector<string> pathSolution) {

		root()->clear();

		Wt::WApplication::instance()->useStyleSheet("style/Template.css");
		root()->setStyleClass("CSS-example");
	
		for (int i = 0; i < pathSolution.size(); i++) {
			cout << pathSolution[i] << endl;
		}

		Wt::WCssDecorationStyle textColor;

		for (int i = pathSolution.size()-1; i >=0; i--){

			if (pathSolution.at(i).at(0) == 'B') {
				textColor.setForegroundColor(Wt::WColor(0, 0, 255, 255));
				root()->addWidget(std::make_unique<Wt::WText>("B"))->setStyleClass("code");
			}
			else if (pathSolution.at(i).at(0) == 'R') {
				textColor.setForegroundColor(Wt::WColor(255, 0, 0, 255));
				root()->addWidget(std::make_unique<Wt::WText>("R"))->setStyleClass("code");
			}
			else if (pathSolution.at(i).at(0) == 'G') {
				textColor.setForegroundColor(Wt::WColor(0, 0, 255, 255));
				root()->addWidget(std::make_unique<Wt::WText>("G"))->setStyleClass("code");
			}
			else if (pathSolution.at(i).at(0) == 'Y') {
				textColor.setForegroundColor(Wt::WColor(255, 165, 0, 255));
				root()->addWidget(std::make_unique<Wt::WText>("Y"))->setStyleClass("code");
			}
			if (pathSolution.at(i).at(1) == 'N') {
				root()->addWidget(std::make_unique<Wt::WText>("N"))->setStyleClass("code");
			}
			else if (pathSolution.at(i).at(1) == 'S') {
				root()->addWidget(std::make_unique<Wt::WText>("S"))->setStyleClass("code");
			}
			else if (pathSolution.at(i).at(1) == 'E') {
				root()->addWidget(std::make_unique<Wt::WText>("E"))->setDecorationStyle(textColor);
			}
			else if (pathSolution.at(i).at(1) == 'O') {
				root()->addWidget(std::make_unique<Wt::WText>("O"))->setDecorationStyle(textColor);
			}
			
		}
	}

private:
	Wt::WPushButton* btnPrecomputeMinMoves;
	Wt::WPushButton* btnSolutionPath;
	Database* db;
};


HelloApplication::HelloApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env)
{
	
	initializeBd();
	Grid* grille = new Grid();
	//connectionForm();
	resolutionAlgorithm(grille);
	vector <char> path;
	vector <string> chemin = grille->principalSearch(path);
	//fctDisplayPath(chemin);
	//fctDisplayPrecomputeMinimumMoves(grille);
	
}


int main(int argc, char** argv) {

	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
	return std::make_unique<HelloApplication>(env);
	});
}*/

int main(int argc, char** argv) {

	//grille = new Grid();
	//vector <char> path;

	//cout << "Chemin a suivre : " << endl;
	//cout << grille->principalSearch(path) << endl;

	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
		return std::make_unique<AppWt>(env);
		});
}