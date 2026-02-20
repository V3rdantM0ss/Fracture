#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <Fracture.hpp>
#include "Hollow.hpp"
#include "Version.hpp"
#include "Color.hpp"

class TestLogic : public fracture::Logic {
	private:
		int counter;
		int x;
		int y;
		const hollow::Version testVersion;
		const std::string testName;
		const hollow::Color testColor;
		const hollow::Hollow testHollow;
		const hollow::Aurora testAurora;

	public:
		TestLogic() : counter(0),
			x(25),
			y(25),
			testVersion(0, 0, 0, 0, hollow::ReleaseType::ALPHA),
			testName("Test"),
			testColor(255, 255, 255),
			testHollow(testVersion, testName, testColor),
			testAurora(testHollow.getAurora()) {
		}

		void init() override {
		}

		void update(int update) override {
			if (x < 100) {
				x += 2;
				y = 25 + (update % 20 < 10 ? 5 : -5);
			}
			else if (x < 200) {
				x += 1;
				y += (update % 10 < 5 ? 3 : -1);
			}
			else if (x < 300) {
				x += 1;
				y = 100 + sin(update * 0.3f) * 20;
			}
			else if (x < 400) {
				x += 2;
				y += (update % 5 < 3 ? 8 : -8);
			}
			else if (x < 500) {
				x += 1;
				y = 200 + cos(update * 0.2f) * 30;
			}
			else if (x < 600) {
				x += 3;
				y = 150 + abs(sin(update * 0.5f)) * 50;
			}
			else if (x < 700) {
				x += 1;
				y = 300 + sin(update * 0.4f) * 40;
			}
			else {
				x = 25;
				y = 25;
			}
			if (y < 10)
				y = 10;
			if (y > 580)
				y = 580;
		}

		void render(sf::RenderWindow& window) override {
			sf::CircleShape circle(32);
			circle.setFillColor(sf::Color::Red);
			circle.setPosition({static_cast<float>(x), static_cast<float>(y)});
			window.draw(circle);
		}

		void shutdown() override {
			std::cout << "TestLogic shutting down!" << std::endl;
		}
};

int main() {
	hollow::Aurora::setGlobalMinLevel(hollow::LogLevel::TRACE);
	fracture::Fracture game("Test", 800, 600, 100);
	auto testLogic = std::make_unique<TestLogic>();
	game.addLogic(std::move(testLogic));
	game.run();
	return 0;
}
