//
// Created by verdant_moss on 2/20/26.
//
#include "Fracture.hpp"
#include "Hollow.hpp"
#include "Version.hpp"
#include "Color.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <utility>
#include <SFML/Graphics.hpp>

namespace fracture {
	const hollow::Version fractureVersion(0, 1, 0, 0, hollow::ReleaseType::STABLE);
	const hollow::Color fractureColor(240, 255, 0);
	const std::string fractureName = "Fracture";
	const hollow::Hollow fractureHollow(fractureVersion, fractureName, fractureColor);
	const hollow::Aurora fractureAurora = fractureHollow.getAurora();

	Fracture::Fracture(std::string name, const int width, const int height, const int ups) : projectName(
			std::move(name)),
		windowWidth(width),
		windowHeight(height),
		upsRate(ups),
		isRunning(false) {
		fractureWindow.create(sf::VideoMode({static_cast<unsigned>(width), static_cast<unsigned>(height)}),
			projectName);
		fractureWindow.setVerticalSyncEnabled(true);
		fractureAurora.system("Fracture engine initialized for project: " + projectName);
		fractureAurora.system(
			"WindowWidth: " + std::to_string(windowWidth) + " windowHeight: " + std::to_string(windowHeight));
		fractureAurora.system("UPS: " + std::to_string(upsRate));
	}

	Fracture::~Fracture() {
		stop();
	}

	void Fracture::addLogic(std::unique_ptr<Logic> logic) {
		if (logic) {
			logicComponents.push_back(std::move(logic));
			fractureAurora.info("Added logic component. Total components: " + std::to_string(logicComponents.size()));
		}
	}

	void Fracture::run() {
		if (isRunning) {
			fractureAurora.warning("Fracture is already running!");
			return;
		}
		isRunning = true;
		fractureAurora.info("Starting Fracture engine...");
		for (const auto& logic : logicComponents) {
			logic->init();
		}
		gameLoop();
	}

	void Fracture::stop() {
		if (!isRunning)
			return;
		fractureAurora.info("Stopping Fracture engine...");
		isRunning = false;
		for (auto& logic : logicComponents) {
			logic->shutdown();
		}
	}

	void Fracture::gameLoop() {
		const std::chrono::nanoseconds timePerUpdate(1000000000LL / upsRate);
		auto previousTime = std::chrono::high_resolution_clock::now();
		double deltaUpdates = 0;
		double deltaSeconds = 0;
		int cycle = 0;
		int updates = 0;
		int frames = 0;
		while (isRunning && fractureWindow.isOpen()) {
			while (const std::optional<sf::Event> event = fractureWindow.pollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					fractureWindow.close();
					isRunning = false;
				}
			}
			auto currentTime = std::chrono::high_resolution_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - previousTime);
			previousTime = currentTime;
			deltaUpdates += static_cast<double>(elapsed.count()) / timePerUpdate.count();
			deltaSeconds += static_cast<double>(elapsed.count()) / 1000000000.0;
			while (deltaUpdates >= 1) {
				for (const auto& logic : logicComponents) {
					logic->update(cycle);
				}
				updates++;
				cycle++;
				if (cycle > upsRate) {
					cycle = 0;
				}
				deltaUpdates--;
			}
			fractureWindow.clear();
			for (const auto& logic : logicComponents) {
				logic->render(fractureWindow);
			}
			fractureWindow.display();
			frames++;
			while (deltaSeconds >= 1) {
				fractureAurora.debug("UPS: " + std::to_string(updates) + " FPS: " + std::to_string(frames));
				updates = 0;
				frames = 0;
				deltaSeconds--;
			}
		}
	}
}
