#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <Fracture.hpp>
#include "Hollow.hpp"
#include "Version.hpp"
#include "Color.hpp"
const hollow::Version testVersion(0, 0, 0, 0, hollow::ReleaseType::ALPHA);
const std::string testName = "Test";
const hollow::Color testColor(255, 255, 255);
const hollow::Hollow testHollow(testVersion, testName, testColor);
const hollow::Aurora testAurora = testHollow.getAurora();

class TestLogic : public fracture::Logic {
	private:
	public:
		TestLogic() = default;

		void init() override {
		}

		void update(int cycle) override {
		}

		void render(sf::RenderWindow& window) override {
			sf::CircleShape circle(100);
			circle.setFillColor(sf::Color::Red);
			circle.setPosition({static_cast<float>(0), static_cast<float>(0)});
			window.draw(circle);
		}

		void shutdown() override {
			testAurora.system("Test Shutting Down! :D");
		}
};

int main() {
	hollow::Aurora::setGlobalMinLevel(hollow::LogLevel::DEBUG);
	fracture::Fracture game("Test", 200, 200, 100);
	auto testLogic = std::make_unique<TestLogic>();
	game.addLogic(std::move(testLogic));
	game.run();
	return 0;
}
