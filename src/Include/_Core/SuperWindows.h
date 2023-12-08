// Author: Henry Morales
// File: Kestus/src/Include/_Core/SuperWindows.h
// Source: <https://github.com/Skeptx/Kestus/blob/main/src/Include/_Core/SuperWindows.h>

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

#ifndef _INCLUDE__CORE_SUPERWINDOWS
#define _INCLUDE__CORE_SUPERWINDOWS

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef __STDC_WANT_LIB_EXT1__
#undef __STDC_WANT_LIB_EXT1__
#endif
#define __STDC_WANT_LIB_EXT1__ 1

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

#endif
