#include <Wt/WApplication.h>
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


Grid* grille;



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

		sb1->setCurrentIndex(1); // Select 'medium' by default.
		sb1->setMargin(10, Wt::Side::Right);

		Wt::WText* out = root()->addNew<Wt::WText>("");

		sb1->activated().connect([=] {
			out->setText(Wt::WString("You selected {1}.")
				.arg(sb1->currentText()));
			});

		Wt::WPushButton* SubscriptionButton = root()->addNew<Wt::WPushButton>("Valider");

		SubscriptionButton->clicked().connect([=] {
			if (editLogin->text().empty() || editPassword->text().empty()){
				root()->addWidget(std::make_unique<Wt::WText>("Veuillez remplir tous les champs"));
			}
			db->addUserToDatabase(editLogin->text().toUTF8(), editPassword->text().toUTF8());

		});
	}

	void afficherReglesJeu() {

		Wt::WLink link = Wt::WLink("http://localhost:8080/");
		link.setTarget(Wt::LinkTarget::NewWindow);
		root()->addNew<Wt::WAnchor>(link)->addNew<Wt::WImage>(Wt::WLink("https://www.emweb.be/css/emweb_small.png"));////////////////////////////////METTRE LOGO JEUU

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
		Wt::WImage* image = root()->addNew<Wt::WImage>(Wt::WLink("https://img1.freepng.fr/20171220/zcw/attention-png-5a3a85cd8fadc8.8287464015137847815885.jpg"));//////////////////////////////METTRE PHOTO ATTENTION
		image->setMaximumSize(30, 240);
		Wt::WText* textWarning = root()->addWidget(std::make_unique<Wt::WText>("Attention, votre robot ne pas s'arreter autre part que contre un mur ou contre un robot\n"));
		Wt::WFont fontWarning;
		fontWarning.setStyle(Wt::FontStyle::Italic);


		Wt::WImage* imageLogo = root()->addNew<Wt::WImage>(Wt::WLink("https://www.regledujeu.fr/wp-content/uploads/ricochet-robots-plateau.jpg"));//////////////////////////////METTRE PHOTO JEUU

	}
	
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

			if (db->checkConnection(k.toUTF8(), g.toUTF8())) {
				cout << "Okk connection" << endl;
				//displayUserStatistics(2);
			}
			else {
				root()->addWidget(std::make_unique<Wt::WText>("Login ou mot de passe incorrectes. Veuillez reessayer ou vous creer un compte\n"));
				editLogin->setText("The number must be in the range 0 to 150");
				editPassword->setText("The number must be in the range 0 to 150");
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
			"idUsers INTEGER PRIMARY KEY," //AUTO_INCREMENT NOT NULL
			"login VARCHAR(255),"
			"passwd VARCHAR(255),"
			"gameNb INT,"
			"wonGameNb INT,"
			"ratio FLOAT"
			");");

		db->addUserToDatabase("swan.frere", "passwordSwan");
		db->addUserToDatabase("mathilde.marza", "passwordMathilde");
		db->addUserToDatabase("simon.machado", "passwordSimon");
		db->addUserToDatabase("theo.escolano", "passwordTheo");
	}	
	

	void displayUserPage() {

	}

	
	void fctDisplayPath() {
		root()->clear();
		
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
				//root()->addWidget(std::make_unique<Wt::WText>("Right\n"))->setDecorationStyle(textRight);
				root()->addNew<Wt::WImage>(Wt::WLink("C:/Users/33660/Desktop/arrow.png"));
			}
		}
	}

private:
	Wt::WTable* table = root()->addWidget(std::make_unique<Wt::WTable>());
	Wt::WPushButton* btnPrecomputeMinMoves;
	Wt::WPushButton* btnSolutionPath;
	vector <char> path;
	Database* db;
};


HelloApplication::HelloApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env)
{
	Wt::WApplication::instance()->useStyleSheet("c:/Users/33660/Desktop/Template.css");
	initializeBd();
	connectionForm();
}


int main(int argc, char** argv) {

	grille = new Grid();
	vector <char> path;

	cout << "Chemin a suivre : " << endl;
	cout << grille->principalSearch(path) << endl;	

	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
	return std::make_unique<HelloApplication>(env);
	});
}