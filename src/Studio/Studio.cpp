// Author: Henry Morales
// File: Kestus/src/Studio/Studio.cpp
// Source: <https://github.com/Skeptx/Kestus/blob/main/src/Studio/Studio.cpp>

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

#include <cstdlib>
#include <string>

int main(int argc, char **argv) {
	if (argc > 2) {
		std::string src = "clang++ -target x86_64-pc-windows-msvc -std=c++17 -shared -I ../Include -include _Core/Game.hpp -o \"";
		src += argv[1];
		src += ".dll\" -l Game/Windows.lib Game/Windows.obj";
		for (int i = 2; i < argc; ++i) {
			src += ' ';
			src += argv[i];
		}
		std::system(src.c_str());
	}
	return EXIT_SUCCESS;
}
