// Author: Henry Morales
// File: Kestus/src/Include/_Core/Game.hpp
// Source: <https://github.com/Skeptx/Kestus/blob/main/src/Include/_Core/Game.hpp>

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

#ifndef _INCLUDE_GAME
#define _INCLUDE_GAME

#ifdef _WIN32

#ifdef _DLL_API
#undef _DLL_API
#endif
#define _DLL_API extern "C" __declspec(dllexport)

#include "_Core/SuperWindows.h"
#include "../Color.hpp"
#include "../Instance.hpp"
#include "../Shape2D.hpp"
#include "../Vector2D.hpp"

void Start(void);
void Update(double deltaTime);
void KeyDown(WPARAM key);
void KeyUp(WPARAM key);

extern Kestus::Shape2D *game;

#endif

#endif
