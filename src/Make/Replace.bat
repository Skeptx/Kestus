:: Author: Henry Morales
:: File: Kestus/src/Make/Replace.bat
:: Source: <https://github.com/Skeptx/Kestus/blob/main/src/Make/Replace.bat>

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

SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION

SET STATE=0
SET STRING=%~1

FOR %%A IN (%*) DO (
	IF !STATE! EQU 1 (
		SET SUBSTRING=%%~A
		SET STATE=2
	) ELSE (
		IF !STATE! EQU 2 (
			FOR /F "DELIMS=" %%S IN (^""!SUBSTRING!=%%~A"^") DO (
				SET STRING=!STRING:%%~S!
			)
		)
		SET STATE=1
	)
)

IF !STATE! EQU 2 (
	ECHO !STRING:%SUBSTRING%=!
) ELSE (
	ECHO !STRING!
)
