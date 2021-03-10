#include "AppWt.h"
#include <Wt/WVBoxLayout.h>

#include<iostream>
#include "WidgetGrilleMove.h"

AppWt::AppWt(const WEnvironment& env) : WApplication(env)
{
	
	initializeBd();
	setTitle("Robot Ricochets");
	container = root()->addWidget(cpp14::make_unique<WContainerWidget>());
	containerAlgo = root()->addWidget(cpp14::make_unique<WContainerWidget>());
	grille = new Grid();
	showMenu();
	//container->setStyleClass("classBody");
	//useStyleSheet("C:\\Users\\frere\\Desktop\\IUT\\PTUT\\RobotRicochets");

}

AppWt::~AppWt()
{
}

void AppWt::showMenu()
{
	container->clear();
	container->resize(150, 150);

	auto vbox = container->setLayout(Wt::cpp14::make_unique<Wt::WVBoxLayout>());


	WPushButton* boutonPlay = vbox->addWidget(std::make_unique<Wt::WPushButton>("JOUER"));
	WPushButton* boutonRegles = vbox->addWidget(std::make_unique<Wt::WPushButton>("REGLES"));
	WPushButton* boutonLogin = vbox->addWidget(std::make_unique<Wt::WPushButton>("SE CONNECTER"));
	WPushButton* boutonRegister = vbox->addWidget(std::make_unique<Wt::WPushButton>("S'INSCRIRE"));

	boutonPlay->decorationStyle().setBackgroundColor(Wt::WColor::WColor(220, 220, 220, 155));
	boutonRegles->decorationStyle().setBackgroundColor(Wt::WColor::WColor(220, 220, 220, 155));
	boutonLogin->decorationStyle().setBackgroundColor(Wt::WColor::WColor(220, 220, 220, 155));
	boutonRegister->decorationStyle().setBackgroundColor(Wt::WColor::WColor(220, 220, 220, 155));

	boutonPlay->clicked().connect(this, &AppWt::startGame);
	boutonRegles->clicked().connect(this, &AppWt::showRegles);
	boutonLogin->clicked().connect(this, &AppWt::login);
	boutonRegister->clicked().connect(this, &AppWt::inscription);
}

void AppWt::startGame()
{
	container->clear();

	WidgetGrille* wtGrid = container->addWidget(std::make_unique<WidgetGrille>());
	wtGrid->setGrid(grille);

	WPushButton* boutonMenu = container->addWidget(std::make_unique<Wt::WPushButton>("RETOUR MENU"));
	boutonMenu->clicked().connect(this, &AppWt::showMenu);

	WPushButton* boutonAlgo = containerAlgo->addWidget(std::make_unique<Wt::WPushButton>("Utiliser l'algorithme"));
	boutonAlgo->clicked().connect([=] {
		containerAlgo->clear();
		resolutionAlgorithm(grille);
	});

}

void AppWt::showRegles()
{
	container->clear();

	Wt::WText* pageTitle = container->addWidget(std::make_unique<Wt::WText>(Wt::WString("<h1>Regles du jeu</h1>")));
	Wt::WFont fontTitle;

	fontTitle.setFamily(Wt::FontFamily::Monospace, "'Courier New'");
	fontTitle.setSize(12);

	pageTitle->decorationStyle().setFont(fontTitle);
	Wt::WText* ExplanationsRules = container->addWidget(std::make_unique<Wt::WText>("Trouvez le chemin le plus rapide pour emmener le robot objectif � la case object, en vous aidant des murs et de tous les autres robots\n Pour cela, cliquez sur l'un des robots, et indiquez l� o� vous souhaitez qu'il se dirige.\n"));
	Wt::WFont fontRules;
	fontRules.setFamily(Wt::FontFamily::Fantasy, "'Western'");
	fontRules.setSize(12);
	ExplanationsRules->decorationStyle().setFont(fontRules);
	Wt::WText* textWarning = container->addWidget(std::make_unique<Wt::WText>("Attention, votre robot ne pas s'arreter autre part que contre un mur ou contre un robot\n"));
	Wt::WFont fontWarning;
	fontWarning.setStyle(Wt::FontStyle::Italic);

	Wt::WImage* imageLogo = container->addNew<Wt::WImage>(Wt::WLink("https://www.regledujeu.fr/wp-content/uploads/ricochet-robots-plateau.jpg"));//////////////////////////////METTRE PHOTO JEUU

	WPushButton* boutonMenu = container->addWidget(std::make_unique<Wt::WPushButton>("RETOUR MENU"));
	boutonMenu->clicked().connect(this, &AppWt::showMenu);
}


void AppWt::inscription()
{
	container->clear();

	WLineEdit* editLogin = container->addNew<WLineEdit>();
	editLogin->setPlaceholderText("Login");

	WLineEdit* editPassword = container->addNew<WLineEdit>();
	editPassword->setPlaceholderText("Mot de passe");


	WSelectionBox* sb1 = container->addNew<WSelectionBox>();
	sb1->addItem("France");
	sb1->addItem("Belgique");
	sb1->addItem("Royaume-Unis");
	sb1->addItem("Espagne");
	sb1->addItem("Pays-bas");

	sb1->setCurrentIndex(1); // Select 'medium' by default.
	sb1->setMargin(10, Side::Right);

	WPushButton* SubscriptionButton = container->addNew<WPushButton>("Valider");

	SubscriptionButton->clicked().connect([=] {
		if (editLogin->text().empty() || editPassword->text().empty()) {
			container->addWidget(std::make_unique<WText>("Veuillez remplir tous les champs"));
		}
		else {
			db->addUserToDatabase(editLogin->text().toUTF8(), editPassword->text().toUTF8(), sb1->currentText().toUTF8());
			showMenu();
		}
		});

	WPushButton* boutonMenu = container->addWidget(std::make_unique<Wt::WPushButton>("RETOUR MENU"));
	boutonMenu->clicked().connect(this, &AppWt::showMenu);
}

void AppWt::login()
{
	container->clear();

	auto vbox = container->setLayout(Wt::cpp14::make_unique<Wt::WVBoxLayout>());

	WLineEdit* editLogin = vbox->addWidget(std::make_unique<Wt::WLineEdit>("Login"));
	editLogin->setPlaceholderText("Login");

	WLineEdit* editPassword = vbox->addWidget(std::make_unique<Wt::WLineEdit>("Password"));
	editLogin->setPlaceholderText("Mot de passe");

	WPushButton* connectionButton = vbox->addWidget(std::make_unique<Wt::WPushButton>("Login"));
	connectionButton->setText("Se connecter");

	Wt::WCssDecorationStyle connectionButtonDecoration;
	connectionButtonDecoration.setBackgroundColor(Wt::WColor::WColor(155, 255, 255, 255));
	connectionButton->setDecorationStyle(connectionButtonDecoration);

	Wt::WCssDecorationStyle messageErreurConnectionDecoration;
	messageErreurConnectionDecoration.setBackgroundColor(Wt::WColor::WColor(255, 0, 0, 255));

	connectionButton->clicked().connect([=] {

		Wt::WString k = editLogin->text();
		Wt::WString g = editPassword->text();

		int idFounded = db->checkConnection(k.toUTF8(), g.toUTF8());

		if (idFounded != -1) {
			std::cout << "Okk connection" << std::endl;
			std::cout << "On fait la connexion avec le user " << idFounded << std::endl;
			displayUserStatistics(idFounded);
		}
		else {
			std::cout << "Login ou mot de passe incorrectes. Veuillez reessayer ou vous creer un compte\n" << std::endl;
			root()->addWidget(std::make_unique<Wt::WText>("Login ou mot de passe incorrectes. Veuillez reessayer ou vous creer un compte\n"));
		}
		});

	WPushButton* boutonMenu = container->addWidget(std::make_unique<Wt::WPushButton>("RETOUR MENU"));
	boutonMenu->clicked().connect(this, &AppWt::showMenu);
}

void AppWt::logout()
{
}


void AppWt::initializeBd()
{
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

void AppWt::resolutionAlgorithm(Grid* grille)
{
	vector <char> path;
	vector <string> chemin = grille->principalSearch(path);

	cout << "ALGO FINI " << chemin.size() << endl;

	for (int i = 0; i < chemin.size(); i++) {
		cout << chemin[i] << endl;
	}

	setTitle("Resolution algorithme");
	HWND hd = GetDesktopWindow();
	RECT rect;

	GetWindowRect(hd, &rect);
	int window_width = (rect.right - rect.left);
	int window_height = (rect.bottom - rect.top);

	container->resize(window_width, window_height);//Mettre taille ecran

	Wt::WText* pageTitle = container->addWidget(std::make_unique<Wt::WText>(Wt::WString("<h1>Resolution d'algorithme</h1>")));
	Wt::WFont fontTitle;

	fontTitle.setFamily(Wt::FontFamily::Monospace, "'Courier New'");
	fontTitle.setSize(45);

	pageTitle->decorationStyle().setFont(fontTitle);

	Wt::WText* ExplanationsPage = container->addWidget(std::make_unique<Wt::WText>(Wt::WString("<p>Choisissez l'action que vous souhaitez effectuer : </p>")));
	Wt::WFont fontExplanations;
	fontExplanations.setFamily(Wt::FontFamily::Fantasy, "'Western'");
	fontExplanations.setSize(12);
	ExplanationsPage->decorationStyle().setFont(fontExplanations);

	Wt::WPushButton* btnPrecomputeMinMoves = container->addNew<Wt::WPushButton>("Precompute minimum moves");
	Wt::WPushButton* btnSolutionPath = container->addNew<Wt::WPushButton>("Chemin le plus court");


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

void AppWt::fctDisplayPrecomputeMinimumMoves(Grid* grille)
{
	containerAlgo->clear();
	std::cout << "Dans fctDisplayPrecomputeMinimumMoves" << std::endl;

	WidgetGrilleMove* wtGrid = containerAlgo->addWidget(std::make_unique<WidgetGrilleMove>());
	wtGrid->setGrid(grille);

}


void AppWt::fctDisplayPath(vector<string> pathSolution)
{
	containerAlgo->clear();

	for (int i = 0; i < pathSolution.size(); i++) {
		cout << pathSolution[i] << endl;
	}

	Wt::WCssDecorationStyle textColor;

	for (int i = pathSolution.size() - 1; i >= 0; i--) {

		if (pathSolution.at(i).at(0) == 'B') {
			textColor.setForegroundColor(Wt::WColor(0, 0, 255, 255));
		}
		else if (pathSolution.at(i).at(0) == 'R') {
			textColor.setForegroundColor(Wt::WColor(255, 0, 0, 255));
		}
		else if (pathSolution.at(i).at(0) == 'G') {
			textColor.setForegroundColor(Wt::WColor(0, 0, 255, 255));
		}
		else if (pathSolution.at(i).at(0) == 'Y') {
			textColor.setForegroundColor(Wt::WColor(255, 165, 0, 255));
		}
		if (pathSolution.at(i).at(1) == 'N') {
			auto text = containerAlgo->addWidget(std::make_unique<Wt::WText>("N"));
			text->setDecorationStyle(textColor);
		}
		else if (pathSolution.at(i).at(1) == 'S') {
			containerAlgo->addWidget(std::make_unique<Wt::WText>("S"))->setDecorationStyle(textColor);
		}
		else if (pathSolution.at(i).at(1) == 'E') {
			containerAlgo->addWidget(std::make_unique<Wt::WText>("E"))->setDecorationStyle(textColor);
		}
		else if (pathSolution.at(i).at(1) == 'O') {
			containerAlgo->addWidget(std::make_unique<Wt::WText>("O"))->setDecorationStyle(textColor);
		}

	}
}


void AppWt::displayUserStatistics(int id)
{
	root()->clear();
	root()->addWidget(std::make_unique<Wt::WText>("Login\n"));
}
