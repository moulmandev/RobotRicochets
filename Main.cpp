#include"AppWt.h"

using namespace std;

int main(int argc, char** argv) {

	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
		return std::make_unique<AppWt>(env);
	});
}