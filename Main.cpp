#include"AppWt.h"

using namespace std;


int main(int argc, char** argv) {

	//grille = new Grid();
	//vector <char> path;
	
	//cout << "Chemin a suivre : " << endl;
	//cout << grille->principalSearch(path) << endl;

	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
	return std::make_unique<AppWt>(env);
	});
}