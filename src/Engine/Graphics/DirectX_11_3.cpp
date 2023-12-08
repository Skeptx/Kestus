// Author: Henry Morales
// File: Skeptx/Kestus/src/Engine/Graphics/DirectX_11_3.cpp
// Source: <https://github.com/Skeptx/Kestus/blob/main/src/Engine/Graphics/DirectX_11_3.cpp>

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

#include "DirectX_11_3.hpp"
#include <cstdlib>
#include <vector>
#include "Shape2D.hpp"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "user32.lib")

_DLL_API Kestus::_Graphics *(WINAPI Kestus::_NewGraphics)(HWND window) {
	try {
		return new Kestus::_DirectX_11_3(window);
	} catch (int errnum) {
		return NULL;
	}
}

_DLL_API void (WINAPI Kestus::_DeleteGraphics)(Kestus::_Graphics *graphics) {
	delete graphics;
}

Kestus::_DirectX_11_3::_DirectX_11_3(HWND window): window(window) {
	if (D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory) != S_OK) {
		throw 1;
		return;
	}
	RECT rect;
	GetClientRect(window, &rect);
	height = (UINT32)rect.bottom;
	width = (UINT32)rect.right;
	D2D1_RENDER_TARGET_PROPERTIES properties = {
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		{DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_UNKNOWN},
		0.0F,
		0.0F,
		D2D1_RENDER_TARGET_USAGE_NONE,
		D2D1_FEATURE_LEVEL_DEFAULT
	};
	D2D1_HWND_RENDER_TARGET_PROPERTIES windowProperties = {
		window,
		{width, height},
		D2D1_PRESENT_OPTIONS_NONE
	};
	if (factory->CreateHwndRenderTarget(&properties, &windowProperties, &target) != S_OK) {
		throw 2;
		return;
	}
	POINT position = {0L};
	monitor = MonitorFromPoint(position, GetCursorPos(&position) ? MONITOR_DEFAULTTONEAREST : MONITOR_DEFAULTTOPRIMARY);
}

void Kestus::_DirectX_11_3::draw(Kestus::Instance *instance) {
	BeginPaint(window, paint);
	target->BeginDraw();
	drawRecursive(instance);
	target->EndDraw();
	EndPaint(window, paint);
}

void Kestus::_DirectX_11_3::resize(void) {
	RECT rect;
	GetClientRect(window, &rect);
	height = (UINT32)rect.bottom;
	width = (UINT32)rect.right;
	target->Resize({width, height});
	InvalidateRect(window, NULL, FALSE);
}

void Kestus::_DirectX_11_3::drawRecursive(Kestus::Instance *instance) {
	unsigned i = 0;
	if (instance->className == "Shape2D") {
		Kestus::Shape2D *shape = (Kestus::Shape2D *)instance;
		target->CreateSolidColorBrush(D2D1::ColorF(shape->color.r, shape->color.g, shape->color.b, shape->color.a), &brush);
		target->FillRectangle(D2D1::Rect(shape->position.x, shape->position.y, shape->position.x + shape->size.x, shape->position.y + shape->size.y), brush);
	}
	while ((*instance)[i]) {
		drawRecursive((*instance)[i]);
		++i;
	}
}

#endif
