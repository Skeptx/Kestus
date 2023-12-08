:: Author: Henry Morales
:: File: Kestus/Compile.bat
:: Source: <https://github.com/Skeptx/Kestus/blob/main/Compile.bat>

:: Copyright 2023 Henry Morales.

:: This file is part of Kestus.

:: Kestus is free software: you can redistribute it and/or modify it under the
:: terms of the GNU Affero General Public License as published by the Free Software
:: Foundation, either version 3 of the License, or (at your option) any later
:: version.

:: Kestus is distributed in the hope that it will be useful, but WITHOUT ANY
:: WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
:: PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.

:: You should have received a copy of the GNU Affero General Public License along
:: with Kestus. If not, see <https://www.gnu.org/licenses/>.

@ECHO OFF

SET RULE=

IF /I "%1" EQU "D" (
	SET DEBUG=%2
	GOTO :DEBUG
)
IF /I "%1" EQU "R" GOTO :RELEASE

SET RULE=%1

IF "%1" EQU "clean" GOTO :RELEASE
IF /I "%2" EQU "D" (
	SET DEBUG=%3
	GOTO :DEBUG
)
IF /I "%2" EQU "R" GOTO :RELEASE

:STATE
SET /P STATE=Compile for debug (D) or release (R)? 
IF /I "%STATE%" EQU "D" (
	SET DEBUG=5
	GOTO :DEBUG
)
IF /I "%STATE%" EQU "R" GOTO :RELEASE
GOTO :STATE

:DEBUG
make -C src/Make -O -f Windows.make %RULE% cppflags="-D DEBUG=%DEBUG%" cflags="-g -v" -S -d
GOTO :EOF

:RELEASE
make -C src/Make -O -f Windows.make %RULE% cppflags="-D NDEBUG" -S -s
