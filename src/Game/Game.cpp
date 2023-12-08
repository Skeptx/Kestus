// Author: Henry Morales
// File: Kestus/src/Game/Game.cpp
// Source: <https://github.com/Skeptx/Kestus/blob/main/src/Game/Game.cpp>

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

#ifdef _WIN32

#ifdef _DLL_API
#undef _DLL_API
#endif
#define _DLL_API extern "C" __declspec(dllexport)

#include "_Core/Game.hpp"
#include <Process.h>

Kestus::Shape2D *game;

_DLL_API Kestus::Instance *(WINAPI _Start)(void);
_DLL_API void (WINAPI _Update)(double deltaTime);
_DLL_API void (WINAPI _KeyDown)(WPARAM key);
_DLL_API void (WINAPI _KeyUp)(WPARAM key);

_DLL_API BOOL (WINAPI DllMain)(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		game = new Kestus::Shape2D();
		game->size = Kestus::Vector2D(800, 600);
		return TRUE;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == nullptr) {
			delete game;
		}
	}
	return TRUE;
}

_DLL_API Kestus::Instance *(WINAPI _Start)(void) {
	Start();
	return game;
}

_DLL_API void (WINAPI _Update)(double deltaTime) {
	Update(deltaTime);
}

_DLL_API void (WINAPI _KeyDown)(WPARAM key) {
	KeyDown(key);
}

_DLL_API void (WINAPI _KeyUp)(WPARAM key) {
	KeyUp(key);
}

#endif
