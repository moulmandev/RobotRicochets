#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include<Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
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
#include <Wt/WText.h>
#include <Wt/WTableView.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WImage.h>
#include <Wt/WApplication.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WAbstractItemModel.h>
#include <Wt/WColor.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WFont.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WFlags.h>
#include <Wt/WStandardItemModel.h>
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



using namespace std;


Grid* grille;


class HelloApplication : public Wt::WApplication
{
public:
	HelloApplication(const Wt::WEnvironment& env);

	void menuAccueil() {

		auto container = Wt::cpp14::make_unique<Wt::WContainerWidget>();

		// Create a navigation bar with a link to a web page.
		Wt::WNavigationBar* navigation = root()->addNew<Wt::WNavigationBar>();
		navigation->setTitle("Ricochet Robots",	"http://localhost:8080/");
		navigation->setResponsive(true);

		Wt::WStackedWidget* contentsStack = root()->addNew<Wt::WStackedWidget>();
		contentsStack->addStyleClass("contents");

		// Setup a Left-aligned menu.
		auto leftMenu = Wt::cpp14::make_unique<Wt::WMenu>(contentsStack);
		auto leftMenu_ = navigation->addMenu(std::move(leftMenu));

		leftMenu_->addItem("Accueil", Wt::cpp14::make_unique<Wt::WText>("There is no better place!"));
		leftMenu_->addItem("Regles du jeu", Wt::cpp14::make_unique<Wt::WText>("Layout contents"))
			->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/layout"));
		leftMenu_->addItem("Jouer", Wt::cpp14::make_unique<Wt::WText>("There is no better place!"));


		// Setup a Right-aligned menu.
		auto rightMenu = Wt::cpp14::make_unique<Wt::WMenu>();
		auto rightMenu_ = navigation->addMenu(std::move(rightMenu), Wt::AlignmentFlag::Right);

		// Create a popup submenu for the Help menu.
		auto popupPtr = Wt::cpp14::make_unique<Wt::WPopupMenu>();
		auto popup = popupPtr.get();
		popup->addItem("Contents");
		popup->addItem("Index");
		popup->addSeparator();
		popup->addItem("About");

		popup->itemSelected().connect([=](Wt::WMenuItem* item) {
			auto messageBox = popup->addChild(
				Wt::cpp14::make_unique<Wt::WMessageBox>
				("Help", Wt::WString("<p>Showing Help: {1}</p>").arg(item->text()),
					Wt::Icon::Information,
					Wt::StandardButton::Ok));

			messageBox->buttonClicked().connect([=] {
				popup->removeChild(messageBox);
				});

			messageBox->show();
		});

		auto item = Wt::cpp14::make_unique<Wt::WMenuItem>("Help");
		item->setMenu(std::move(popupPtr));
		rightMenu_->addItem(std::move(item));

		// Add a Search control.
		auto editPtr = Wt::cpp14::make_unique<Wt::WLineEdit>();
		auto edit = editPtr.get();
		edit->setPlaceholderText("Enter a search item");

		navigation->addSearch(std::move(editPtr), Wt::AlignmentFlag::Right);

	}

	void afficherReglesJeu() {
		Wt::WText* pageTitle = root()->addWidget(std::make_unique<Wt::WText>(Wt::WString("<h1>Regles du jeu</h1>")));
		Wt::WFont fontTitle;
		fontTitle.setFamily(Wt::FontFamily::Monospace, "'Courier New'");
		fontTitle.setSize(45);

		Wt::WText* pageTitle = root()->addWidget(std::make_unique<Wt::WText>(Wt::WString("<h1>Regles du jeu</h1>\n <p Faire parvenir le robot objectif a la case objectif en utilisant tous les robots disponibles")));
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

		
		//root()->setPadding(12, Wt::WFlags<Wt::Side::CenterX>);
		
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
};


HelloApplication::HelloApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env)
{
	afficherReglesJeu();
	//menuPrincipalAlgorithmeResolution();
	//menuAccueil();

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