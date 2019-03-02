#include "AppDesc.h"
#include "App.h"

int main() {

	AppDesc desc;
	desc.AppTitle = "You gay";
	desc.Fullscreen = false;
	desc.WindowWidth = 1280;
	desc.WindowHeight = 720;

	App app;
	app.init(desc);
	app.run();


	return 0;
}
