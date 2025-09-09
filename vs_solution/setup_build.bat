@echo off
echo Setting up SDL2 Project build environment...

REM Create necessary directories
if not exist "..\Executables" mkdir "..\Executables"
if not exist "..\build" mkdir "..\build"

REM Copy DLLs to Executables folder
echo Copying DLL files...
if exist "..\DLLs\*.dll" (
    copy "..\DLLs\*.dll" "..\Executables\" >nul 2>&1
    echo DLLs copied successfully
) else if exist "..\bin\*.dll" (
    copy "..\bin\*.dll" "..\Executables\" >nul 2>&1
    echo DLLs copied from bin folder
) else (
    echo Warning: No DLL files found in DLLs or bin folders
)

REM Copy other assets
if exist "..\Fonts" copy "..\Fonts\*" "..\Executables\" >nul 2>&1
if exist "..\Images" xcopy "..\Images" "..\Executables\Images\" /E /I /H /Y >nul 2>&1
if exist "..\Files" xcopy "..\Files" "..\Executables\Files\" /E /I /H /Y >nul 2>&1

echo.
echo Build setup complete!
echo.
echo To build the project:
echo 1. Open SDL2_Project.sln in Visual Studio
echo 2. Select Release or Debug configuration
echo 3. Build the solution (F7)
echo 4. Executables will be in the Executables folder
echo.
echo Note: Make sure you have SDL2 development libraries installed
echo and the include/lib paths are correctly configured.
echo.
pause
