/*
 * Fracture - A lightweight C++ game framework
 * Copyright (c) 2026 VerdantMoss
 *
 * Licensed under the MIT License. See LICENSE file for details.
 *
 * Code Style: Import style.xml for JetBrains IDE formatting
 */
#pragma once
#include <SFML/Graphics.hpp>

namespace fracture {
	class Logic {
		public:
			virtual ~Logic() = default;
			virtual void update(int update) = 0;
			virtual void render(sf::RenderWindow& window) = 0;
			virtual void shutdown() = 0;
			virtual void init() = 0;
	};
}
