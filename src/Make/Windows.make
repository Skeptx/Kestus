## Author: Henry Morales
## File: Kestus/src/Make/Windows.make
## Source: <https://github.com/Skeptx/Kestus/blob/main/src/Make/Windows.make>

## Copyright 2023 Henry Morales.

## This file is part of Kestus.

## Kestus is free software: you can redistribute it and/or modify it under the
## terms of the GNU Affero General Public License as published by the Free Software
## Foundation, either version 3 of the License, or (at your option) any later
## version.

## Kestus is distributed in the hope that it will be useful, but WITHOUT ANY
## WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
## PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.

## You should have received a copy of the GNU Affero General Public License along
## with Kestus. If not, see <https://www.gnu.org/licenses/>.

include Common.make

CC = clang
CXX = clang++
archive = clang-cl -fuse-ld=llvm-lib

CPPFLAGS = \
	$(cppflags)
CFLAGS = \
	$(cflags) \
	-I "$(srcdir)" \
	-I "$(srcdir)\Include" \
	-target x86_64-pc-windows-msvc \
	-Wno-delete-abstract-non-virtual-dtor
CXXFLAGS = \
	-std=c++17

define config
$(shell node -p "require('./Config.json').$(1)")
endef

v = $(call config, "Version.Major").$(call config, "Version.Minor")

game_object_files = \
	$(libdir)\Engine\0.1\Color.obj \
	$(libdir)\Engine\0.1\Instance.obj \
	$(libdir)\Engine\0.1\Shape2D.obj \
	$(libdir)\Engine\0.1\Vector2D.obj

engine_object_files = \
	$(libdir)\Engine\0.1\Engine.obj

studio_object_files = \
	$(libdir)\Studio\0.1\Studio.obj

engine_dynamic_libraries = \
	$(bindir)\Windows\Kestus\Engine\0.1\Graphics\DirectX_11_3.dll

.PHONY: engine
engine: \
	$(engine_dynamic_libraries) \
	$(bindir)\Windows\Kestus\Engine\$(v)\Kestus.exe \
	$(bindir)\Windows\Kestus\Engine\Kestus\ Package\ Manager.exe \
	$(bindir)\Windows\Kestus\Install.lnk \
	$(bindir)\Windows\Kestus\Update.lnk \
	$(bindir)\Windows\Kestus\Uninstall.lnk

.PHONY: studio
studio: \
	include \
	$(bindir)\Windows\Kestus\Studio\0.1\Game\Windows.obj \
	$(bindir)\Windows\Kestus\Studio\$(v)\Game\Windows.lib \
	$(bindir)\Windows\Kestus\Studio\$(v)\Kestus\ Studio.exe \
	$(bindir)\Windows\Kestus\Kestus\ Studio.lnk

.PHONY: installer
installer: \
	$(bindir)\Windows\Kestus\ Installer.exe

.PHONY: resources
resources:
	ROBOCOPY "$(resdir)" "$(bindir)\Windows\Kestus\Resources" /IM /LOG:$(libdir)\$@.log /MIR /MT /TIMFIX | @BREAK

.PHONY: include
include:
	ROBOCOPY "$(srcdir)\Include" "$(bindir)\Windows\Kestus\Studio\Include" /IM /LOG:$(libdir)\$@.log /MIR /MT /TIMFIX /XF *.c *.cpp | @BREAK

$(bindir)\Windows\Kestus\\%.lnk: Shortcut.vbs
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	CSCRIPT /NOLOGO $< "$@" "$(@D)\Engine\Kestus Package Manager.exe" --$*
	@ECHO [0;92mCreated [96m$@[0m

$(bindir)\Windows\Kestus\Kestus\ Studio.lnk: Shortcut.vbs
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	CSCRIPT /NOLOGO $< "$@" "$(@D)\Studio\$(v)\Kestus Studio.exe" ""
	@ECHO [0;92mCreated [96m$@[0m

$(bindir)\Windows\Kestus\ Installer.exe:
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"

$(bindir)\Windows\Kestus\Engine\Kestus\ Package\ Manager.exe:
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"

$(bindir)\Windows\Kestus\Engine\$(v)\Kestus.exe: $(engine_object_files)
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -o "$@" $(engine_object_files)
	@ECHO [0;92mCreated [96m$@[0m

$(bindir)\Windows\Kestus\Studio\$(v)\Kestus\ Studio.exe: $(studio_object_files) $(studio_import_libraries)
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	Replace.bat "$(studio_import_libraries)" "$(libdir)\" "-l """ .lib """" | $(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -o "$@" $(studio_object_files) -L "$(libdir)"
	@ECHO [0;92mCreated [96m$@[0m

$(bindir)\Windows\Kestus\\%.dll: $(libdir)\%.dll
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	ROBOCOPY "$(<D)" "$(@D)" "$(<F)" /IM /TIMFIX | @BREAK
	@ECHO [0;92mCopied[0m   [96m$<[0m to [96m$@[0m

$(bindir)\Windows\Kestus\Studio\$(v)\Game\Windows.lib: $(game_object_files)
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	$(archive) -o "$@" $(game_object_files)
	@ECHO [0;92mCreated [96m$@[0m

$(libdir)\Engine\0.1\Graphics\DirectX_11_3.dll: $(libdir)\Engine\0.1\Graphics\DirectX_11_3.obj $(bindir)\Windows\Kestus\Studio\$(v)\Game\Windows.lib
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -shared -o "$(libdir)\Engine\0.1\Graphics\DirectX_11_3.dll" "$<" -l "$(bindir)\Windows\Kestus\Studio\$(v)\Game\Windows.lib" | @BREAK
	@ECHO [0;92mCreated [96m$@[0m

$(libdir)\Engine\0.1\Graphics\DirectX_11_3.lib: $(libdir)\Engine\0.1\Graphics\DirectX_11_3.obj $(bindir)\Windows\Kestus\Studio\$(v)\Game\Windows.lib
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -shared -o "$(libdir)\Engine\0.1\Graphics\DirectX_11_3.dll" "$<" -l "$(bindir)\Windows\Kestus\Studio\$(v)\Game\Windows.lib" | @BREAK
	@ECHO [0;92mCreated [96m$@[0m

$(bindir)\Windows\Kestus\Studio\0.1\Game\Windows.obj: $(libdir)\Game\0.1\Windows.obj
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	ROBOCOPY "$(<D)" "$(@D)" "$(<F)" /IM /TIMFIX | @BREAK
	@ECHO [0;92mCopied[0m   [96m$<[0m to [96m$@[0m

$(libdir)\Engine\0.1\Color.obj: $(srcdir)\Include\Color.cpp $(srcdir)\Include\Color.hpp
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -o "$@" -c "$<"
	@ECHO [0;92mCreated [96m$@[0m

$(libdir)\Engine\0.1\Instance.obj: $(srcdir)\Include\Instance.cpp $(srcdir)\Include\Instance.hpp
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -o "$@" -c "$<"
	@ECHO [0;92mCreated [96m$@[0m

$(libdir)\Engine\0.1\Shape2D.obj: $(srcdir)\Include\Shape2D.cpp $(srcdir)\Include\Shape2D.hpp $(srcdir)\Include\Instance.hpp
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -o "$@" -c "$<"
	@ECHO [0;92mCreated [96m$@[0m

$(libdir)\Engine\0.1\Vector2D.obj: $(srcdir)\Include\Vector2D.cpp $(srcdir)\Include\Vector2D.hpp
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -o "$@" -c "$<"
	@ECHO [0;92mCreated [96m$@[0m

$(libdir)\Game\0.1\Windows.obj: $(srcdir)\Game\Game.cpp $(srcdir)\Include\_Core\Game.hpp
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -o "$@" -c "$<"
	@ECHO [0;92mCreated [96m$@[0m

$(libdir)\Engine\0.1\Engine.obj: $(srcdir)\Engine\Engine.cpp
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -o "$@" -c "$<"
	@ECHO [0;92mCreated [96m$@[0m

$(libdir)\Studio\0.1\Studio.obj: $(srcdir)\Studio\Studio.cpp $(srcdir)\Engine\Graphics\Graphics.hpp $(srcdir)\Include\_Core\SuperWindows.h
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	Replace.bat | $(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -o "$@" -c "$<"
	@ECHO [0;92mCreated [96m$@[0m

$(libdir)\Engine\0.1\Graphics\DirectX_11_3.obj: $(srcdir)\Engine\Graphics\DirectX_11_3.cpp $(srcdir)\Engine\Graphics\DirectX_11_3.hpp $(srcdir)\Engine\Graphics\Graphics.hpp $(srcdir)\Include\_Core\SuperWindows.h
	IF NOT EXIST "$(@D)" MKDIR "$(@D)"
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -o "$@" -c "$<"
	@ECHO [0;92mCreated [96m$@[0m

.PHONY: clean
clean:
	IF EXIST "$(libdir)\" RD /Q /S "$(libdir)"
	IF EXIST "$(bindir)\" RD /Q /S "$(bindir)"
	@ECHO [0;91mRemoved [96m$(libdir)[0m
	@ECHO [0;91mRemoved [96m$(bindir)[0m
