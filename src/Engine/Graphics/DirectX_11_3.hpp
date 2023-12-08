// Author: Henry Morales
// File: Skeptx/Kestus/src/Engine/Graphics/DirectX_11_3.hpp
// Source: <https://github.com/Skeptx/Kestus/blob/main/src/Engine/Graphics/DirectX_11_3.hpp>

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

#ifndef _ENGINE_GRAPHICS_DIRECTX_11_3
#define _ENGINE_GRAPHICS_DIRECTX_11_3

#ifdef _WIN32

#include "Graphics.hpp"
#include <d2d1.h>
#include "_Core/SuperWindows.h"

namespace Kestus {
	
	_DLL_API _Graphics *(WINAPI _NewGraphics)(HWND window);
	_DLL_API void (WINAPI _DeleteGraphics)(_Graphics *graphics);
	
	class _DirectX_11_3: public _Graphics {
		
	public:
		
		_DirectX_11_3(HWND window);
		void draw(Kestus::Instance *instance);
		void resize(void);
		
	protected:
		
		HWND window;
		ID2D1HwndRenderTarget *target;
		ID2D1Factory *factory;
		ID2D1SolidColorBrush *brush;
		
		void drawRecursive(Kestus::Instance *instance);
		
	};
	
}

#endif

#endif
