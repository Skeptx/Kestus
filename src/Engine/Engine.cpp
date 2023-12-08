// Author: Henry Morales
// File: Kestus/src/Engine/Engine.cpp
// Source: <https://github.com/Skeptx/Kestus/blob/main/src/Engine/Engine.cpp>

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
#define _DLL_API __declspec(dllimport)

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")

#include <chrono>
#include <cstdlib>
#include <thread>
#include "_Core/SuperWindows.h"
#include "Instance.hpp"
#include "Engine/Graphics/Graphics.hpp"

Kestus::Instance *game;

typedef Kestus::Instance *(WINAPI *_Start)(void);
typedef void (WINAPI *_Start2)(int a);
typedef void (WINAPI *_Update)(double deltaTime);
typedef void (WINAPI *_KeyDown)(WPARAM key);
typedef void (WINAPI *_KeyUp)(WPARAM key);
typedef Kestus::_Graphics *(WINAPI *_NewGraphics)(HWND window);
typedef void (WINAPI *_DeleteGraphics)(Kestus::_Graphics *graphics);

HMODULE hGame;
HMODULE hGraphics;
HWND hWindow;

_Update Update;
_KeyDown KeyDown;
_KeyUp KeyUp;
_DeleteGraphics DeleteGraphics;

std::chrono::steady_clock::time_point oldFrame;
std::chrono::steady_clock::time_point newFrame;
Kestus::_Graphics *graphics;
double deltaTime;

LRESULT CALLBACK WindowProcedure(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
void ExitPoint(int code);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ INT nShowCmd) {
	if (__argc != 2) {
		return EXIT_FAILURE;
	}
	hGame = LoadLibraryA(__argv[1]);
	if (hGame == nullptr) {
		return EXIT_FAILURE;
	}
	graphics = nullptr;
	_Start Start = (_Start)GetProcAddress(hGame, "_Start");
	Update = (_Update)GetProcAddress(hGame, "_Update");
	KeyDown = (_KeyDown)GetProcAddress(hGame, "_KeyDown");
	KeyUp = (_KeyUp)GetProcAddress(hGame, "_KeyUp");
	game = Start();
	oldFrame = std::chrono::steady_clock::now();
	WNDCLASSW windowClass = {0};
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hIcon = LoadIconA(nullptr, "..\\..\\Resources\\Images\\Kestus.ico");
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProcedure;
	windowClass.lpszClassName = L"Kestus";
	if (RegisterClassW(&windowClass) == 0) {
		return GetLastError();
	}
	RECT rect = {0L, 0L, 800L, 600L};
	AdjustWindowRect(&rect, WS_TILEDWINDOW | WS_VISIBLE, FALSE);
	hWindow = CreateWindowW(L"Kestus", L"Kestus", WS_TILEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);
	hGraphics = LoadLibraryA("..\\..\\Engine\\0.1\\Graphics\\DirectX_11_3.dll");
	_NewGraphics NewGraphics = (_NewGraphics)GetProcAddress(hGraphics, "_NewGraphics");
	DeleteGraphics = (_DeleteGraphics)GetProcAddress(hGraphics, "_DeleteGraphics");
	graphics = NewGraphics(hWindow);
	graphics->draw(game);
	if (graphics) {
		graphics->resize();
	}
	MSG msg = {0};
	BOOL bRet;
	while ((bRet = GetMessage(&msg, nullptr, 0U, 0U)) > 0) {
		DispatchMessage(&msg);
	}
	ExitPoint(bRet ? (int)GetLastError() : msg.wParam);
	return EXIT_FAILURE;
}

LRESULT WINAPI WindowProcedure(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return (LRESULT)0L;
	case WM_DESTROY:
		PostQuitMessage(0);
		return (LRESULT)0L;
	case WM_GETMINMAXINFO:
		((MINMAXINFO *)lParam)->ptMinTrackSize.x = 800L;
		((MINMAXINFO *)lParam)->ptMinTrackSize.y = 600L;
		return (LRESULT)0L;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			ExitPoint(0);
		}
		KeyDown(wParam);
		return (LRESULT)0L;
	case WM_KEYUP:
		KeyUp(wParam);
		return (LRESULT)0L;
	case WM_PAINT:
		newFrame = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(newFrame - oldFrame).count();
		Update(deltaTime);
		oldFrame = newFrame;
		if (graphics) {
			graphics->draw(game);
		}
		InvalidateRect(hWindow, NULL, FALSE);
		std::this_thread::sleep_for((std::chrono::milliseconds)16LL);
		return (LRESULT)0L;
	case WM_SIZE:
		if (graphics) {
			graphics->resize();
		}
		return (LRESULT)0L;
	}
	return DefWindowProcW(hWnd, msg, wParam, lParam);
}

void ExitPoint(int code) {
	DeleteGraphics(graphics);
	graphics = nullptr;
	FreeLibrary(hGame);
	FreeLibrary(hGraphics);
	UnregisterClassW(L"Kestus", nullptr);
	exit(code);
}

#endif
