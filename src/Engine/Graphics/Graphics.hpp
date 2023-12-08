// Author: Henry Morales
// File: Skeptx/Kestus/src/Engine/Graphics/Graphics.hpp
// Source: <https://github.com/Skeptx/Kestus/blob/main/src/Engine/Graphics/Graphics.hpp>

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

#ifndef _ENGINE_GRAPHICS_GRAPHICS
#define _ENGINE_GRAPHICS_GRAPHICS

#ifdef _WIN32

#include "_Core/SuperWindows.h"
#include "Instance.hpp"

namespace Kestus {
	
	class _Graphics {
		
	public:
		
		virtual void draw(Kestus::Instance *instance) = 0;
		virtual void resize(void) = 0;
		
	protected:
		
		HMONITOR monitor;
		LPPAINTSTRUCT paint;
		UINT32 height;
		UINT32 width;
		
	};
	
}

#endif

#endif
