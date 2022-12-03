#include "Screen.cpp"

class GameEngine {
	private:
		bool running = false;
		Game game;

	public:
		void start(Controller& controller, Screen& screen) {
			running = true;
			Field playingField;
			game.start(playingField, controller, running);
			screen.start(playingField);
			controller.listen();
			while (running) {
				if (controller.checkInput(Input::ESCAPE)) {
					running = false;
				}
			}
			controller.stopListening();
			screen.stop();
			game.stop();
			std::cout << "\nGame Engine stopped...\n";
		}
};