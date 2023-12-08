// Author: Henry Morales
// File: Kestus/src/Include/Vector2D.hpp
// Source: <https://github.com/Skeptx/Kestus/blob/main/src/Include/Vector2D.hpp>

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

#ifndef _INCLUDE_VECTOR2D
#define _INCLUDE_VECTOR2D

namespace Kestus {
	
	class Vector2D {
		
	public:
		
		float x;
		float y;
		
		Vector2D(void);
		Vector2D(float x, float y);
		
	};
	
}

#endif
