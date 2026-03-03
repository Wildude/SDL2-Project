@echo off
REM Usage: clean.bat [objs|bin|test|sdl|bas|core]

setlocal

REM === Define directories ===
set "TEST_DIR=tests"
set "TEST_OBJ=%TEST_DIR%\obj"
set "BIN_DIR=bin"
set "DLLS_DIR=DLLS"

set "CORE_DIR=core"
set "SDL_OBJ=%CORE_DIR%\SDL\obj"
set "BAS_OBJ=%CORE_DIR%\BAS\obj"
set "GUI_OBJ=%CORE_DIR%\GUI\obj"

REM List of directories to clean for "core"
set "CORE_OBJ_FOLDERS=%SDL_OBJ% %BAS_OBJ% %GUI_OBJ%"

REM === Conditional handling ===
if "%~1"=="objs" (
    echo Removing obj folders in core and tests...
    call :CleanFolders %CORE_OBJ_FOLDERS%
    call :CleanFolders "%TEST_OBJ%"
    goto :EOF
)

if "%~1"=="core" (
    echo Removing obj folders in core and tests...
    call :CleanFolders %CORE_OBJ_FOLDERS%
    goto :EOF
)

if "%~1"=="bin" (
    echo Removing bin folder...
    call :CleanFolders "%BIN_DIR%"
    goto :EOF
)

if "%~1"=="test" (
    echo Removing test obj folder...
    call :CleanFolders "%TEST_OBJ%"
    goto :EOF
)

if "%~1"=="sdl" (
    echo Removing SDL obj folder...
    call :CleanFolders "%SDL_OBJ%"
    goto :EOF
)

if "%~1"=="bas" (
    echo Removing BAS obj folder...
    call :CleanFolders "%BAS_OBJ%"
    goto :EOF
)

if "%~1"=="gui" (
    echo Removing GUI obj folder...
    call :CleanFolders "%GUI_OBJ%"
    goto :EOF
)

REM === Default: no argument, remove everything ===
if "%~1"=="" (
    echo Removing all folders...
    call :CleanFolders %CORE_OBJ_FOLDERS%
    call :CleanFolders "%TEST_OBJ%"
    call :CleanFolders "%BIN_DIR%"
    goto :EOF
)

REM Invalid argument
echo Invalid argument: %~1
echo "Usage: clean.bat [objs|bin|test|sdl|bas|gui|core]" 
goto :EOF

REM === Subroutine for cleaning folders ===
:CleanFolders
for %%D in (%*) do (
    if exist "%%~D" (
        echo Removing folder %%~D...
        rmdir /s /q "%%~D"
    ) else (
        echo Folder %%~D does not exist, skipping.
    )
)
exit /b
