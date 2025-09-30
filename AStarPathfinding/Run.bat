@echo off
setlocal
echo === A* Pathfinding Demo ===

::Where to put build files
set BUILD_DIR=build
set EXE_NAME=AStarPathfinding.exe

:: Step 1: does the exe already exist?
if exist %BUILD_DIR%\%EXE_NAME% (
	echo [INFO] Executable  found, skipping build.
) else (
	echo [INFO] Executable not found, building...

	:: Make sure build folder exists
	if not exist %BUILD_DIR% mkdir %BUILD_DIR%

	:: Run CMake to configure
	cmake -S . -B %BUILD_DIR% -DCMAKE_BUILD_TYPE=Release
	if %errorlevel% neq 0 (
		echo [ERROR] CMake configuration failed.
		pause
		exit /b %errorlevel%
	)
)
:: Step 2: run the executable
if exist %BUILD_DIR%\Release\%EXE_NAME% (
    %BUILD_DIR%\Release\%EXE_NAME%
) else if exist %BUILD_DIR%\%EXE_NAME% (
    %BUILD_DIR%\%EXE_NAME%
) else (
	ECHO [error] Executable not found even after build!
	PAUSE
	exit /b 1
)

echo.
pause