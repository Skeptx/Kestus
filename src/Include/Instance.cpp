// Author: Henry Morales
// File: Kestus/src/Include/Instance.cpp
// Source: <https://github.com/Skeptx/Kestus/blob/main/src/Include/Instance.cpp>

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

#include "Instance.hpp"

Kestus::Instance::Instance(void): className("Instance"), parent(nullptr) {
}

Kestus::Instance::Instance(Kestus::Instance *parent): className("Instance"), parent(parent) {
	parent->children.push_back(this);
}

void Kestus::Instance::setParent(Instance *parent) {
	if (this->parent) {
		std::vector<Kestus::Instance *>::iterator iterator = std::find(this->parent->children.begin(), this->parent->children.end(), this); //(this->parent->children);
		if (iterator != this->parent->children.end()) {
			this->parent->children.erase(iterator);
		}
	}
	this->parent = parent;
	parent->children.push_back(this);
}

Kestus::Instance *Kestus::Instance::operator[](unsigned i) {
	return i < children.size() ? children[i] : nullptr;
}
