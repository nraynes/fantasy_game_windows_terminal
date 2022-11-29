#include ".\Screen.cpp"

class GameEngine {
	private:
		bool running = false;
		Game game;

	public:
		void start(Controller& controller, Screen& screen) {
			controller.listen();
			running = true;
			Field playingField;
			game.start(playingField, controller, running);
			screen.start(playingField);
			while (running) {
				Input command = controller.getInput();
				if (command == Input::ESCAPE) {
					running = false;
				}
			}
			controller.stopListening();
			screen.stop();
			game.stop();
			std::cout << "Game Engine stopped..." << "\n";
		}
};