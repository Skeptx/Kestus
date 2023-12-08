// Author: Henry Morales
// File: Kestus/src/Examples/Pong.cpp
// Source: <https://github.com/Skeptx/Kestus/blob/main/src/Examples/Pong.cpp>

// Copyright 2023 Henry Morales.

// This file is part of Kestus.

// Kestus is free software: you can redistribute it and/or modify it under the
// terms of the GNU Affero General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.

// Kestus is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License along
// with Kestus. If not, see <https://www.gnu.org/licenses/>.

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <thread>

uint8_t input;
int16_t lVelocity;
int16_t rVelocity;
uint32_t lScore;
uint32_t rScore;
short xDirection;
short yDirection;

Kestus::Shape2D ping;
Kestus::Shape2D pong;
Kestus::Shape2D ball;
Kestus::Shape2D net;

void Reset() {
	
	ping.position = Kestus::Vector2D(50.0F, 275.0F);
	pong.position = Kestus::Vector2D(740.0F, 275.0F);
	ball.position = Kestus::Vector2D(395.0F, 295.0F);
	
	xDirection = 200 * (std::rand() % 2 << 1) - 200;
	yDirection = std::rand() % 201 - 100;
	
}

void Start() {
	
	input = 0;
	lVelocity = 0;
	rVelocity = 0;
	lScore = 0;
	rScore = 0;
	
	ping.setParent(game);
	pong.setParent(game);
	ball.setParent(game);
	net.setParent(game);
	
	ping.size = Kestus::Vector2D(10.0F, 50.0F);
	pong.size = Kestus::Vector2D(10.0F, 50.0F);
	ball.size = Kestus::Vector2D(10.0F, 10.0F);
	net.size = Kestus::Vector2D(10.0F, 600.0F);
	
	game->color = Kestus::Color(0.2F, 0.6F, 0.2F);
	
	ping.color = Kestus::Color(1.0F, 0.6F, 0.6F);
	pong.color = Kestus::Color(0.4F, 0.8F, 1.0F);
	ball.color = Kestus::Color(1.0F, 1.0F, 1.0F);
	net.color = Kestus::Color(1.0F, 1.0F, 1.0F);
	
	net.position = Kestus::Vector2D(395.0F, 0.0F);
	
	Reset();
	
}

void Update(double deltaTime) {
	
	if (ball.position.x <= -10.0F && xDirection < 0) {
		++rScore;
	} else if (ball.position.x >= 800.0F && xDirection > 0) {
		++lScore;
	} else {
		
		ball.position.y += yDirection * deltaTime;
		ball.position.x += xDirection * deltaTime;
		
		if (ball.position.y < 0.0F) {
			ball.position.y *= -1;
			yDirection *= -1;
		} else if (ball.position.y > 590.0F) {
			ball.position.y = 1180.0F - ball.position.y;
			yDirection *= -1;
		}
		
		ping.position.y = std::clamp(ping.position.y + lVelocity * deltaTime, 25.0, 525.0);
		pong.position.y = std::clamp(pong.position.y + rVelocity * deltaTime, 25.0, 525.0);
		
		if (xDirection < 0 && ball.position.x >= 40.0F && ball.position.x <= 60.0F && ball.position.y >= ping.position.y - 10.0F && ball.position.y <= ping.position.y + 50.0F) {
			xDirection = 200;
			yDirection = ((int)(ball.position.y - ping.position.y - 20.0F) << 3) + (lVelocity >> 2);
		} else if (xDirection > 0 && ball.position.x >= 730.0F && ball.position.x <= 750.0F && ball.position.y >= pong.position.y - 10.0F && ball.position.y <= pong.position.y + 50.0F) {
			xDirection = -200;
			yDirection = ((int)(ball.position.y - pong.position.y - 20.0F) << 3) + (rVelocity >> 2);
		}
		
		return;
		
	}
	
	ball.position.x = -20.0F;
	Reset();
	
}

void KeyDown(WPARAM key) {
	switch (key) {
	case 'W':
		input |= 0x1;
		lVelocity = input & 0x2 ? 0 : -400;
		return;
	case 'S':
		input |= 0x2;
		lVelocity = input & 0x1 ? 0 : 400;
		return;
	case VK_UP:
		input |= 0x4;
		rVelocity = input & 0x8 ? 0 : -400;
		return;
	case VK_DOWN:
		input |= 0x8;
		rVelocity = input & 0x4 ? 0 : 400;
		return;
	}
}

void KeyUp(WPARAM key) {
	switch (key) {
	case 'W':
		input &= 0xE;
		lVelocity = input & 0x2 ? -400 : 0;
		return;
	case 'S':
		input &= 0xD;
		lVelocity = input & 0x1 ? -400 : 0;
		return;
	case VK_UP:
		input &= 0xB;
		rVelocity = input & 0x8 ? 400 : 0;
		return;
	case VK_DOWN:
		input &= 0x7;
		rVelocity = input & 0x4 ? -400 : 0;
		return;
	}
}
