#include <locale.h>
#include "Visualisation.h"

int main() {
	setlocale(LC_ALL, "RUS");
	srand(time(0));
	Settings settings;
	GameModel* model = new MenuModel(settings);
	Controller control(model);
	control.run();
	return 0;
}