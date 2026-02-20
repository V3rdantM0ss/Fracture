/*
* Fracture - A lightweight C++ game framework
 * Copyright (c) 2026 VerdantMoss
 *
 * Licensed under the MIT License. See LICENSE file for details.
 *
 * Code Style: Import style.xml for JetBrains IDE formatting
 */
#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Logic.hpp"
#include "Hollow.hpp"
#include "Version.hpp"
#include "Color.hpp"
#include <SFML/Graphics.hpp>

namespace fracture {
	extern const hollow::Version fractureVersion;
	extern const hollow::Color fractureColor;
	extern const std::string fractureName;
	extern const hollow::Hollow fractureHollow;
	extern const hollow::Aurora fractureAurora;

	class Fracture {
		private:
			std::string projectName;
			int windowWidth;
			int windowHeight;
			int upsRate;
			std::vector<std::unique_ptr<Logic>> logicComponents;
			bool isRunning;
			sf::RenderWindow fractureWindow;
			void gameLoop();

		public:
			Fracture(std::string name, int width, int height, int ups);
			~Fracture();
			void addLogic(std::unique_ptr<Logic> logic);
			void run();
			void stop();
	};
}
