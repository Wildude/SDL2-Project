@echo off
REM Usage: clean.bat [project_dir] [objs|bin]

setlocal

REM Set project directory (default to current directory if not provided)
set TEST_DIR=tests
set TEST_OBJ=%TEST_DIR%\obj
set BIN_DIR=bin
set DLLS_DIR=DLLS

set CORE_DIR=core
set SDL_OBJ=%CORE_DIR%\SDL\obj
set BAS_OBJ=%CORE_DIR%\BAS\obj
REM List of directories to create
set CORE_OBJ=%SDL_OBJ% %BAS_OBJ% %OGL_OBJ%

REM Remove obj folders in core and tests
if "%~1"=="objs" (
    echo Removing obj folders in core and tests...
    call :CleanFolders "%CORE_OBJ%"
    rmdir /s /q "%TEST_OBJ%"
    goto :EOF
)
REM Remove obj folders in core
if "%~1"=="core" (
    echo Removing obj folders in core and tests...
    call :CleanFolders "%CORE_OBJ%"
    rmdir /s /q "%TEST_OBJ%"
    goto :EOF
)

REM Remove bin folder
if "%~1"=="bin" (
    echo Removing bin folder...
    rmdir /s /q "%CORE_DIR%\bin"
    goto :EOF
)

REM Remove test obj
if "%~1"=="test" (
    echo Removing test obj folder...
    rmdir /s /q "%TEST_OBJ%"
    goto :EOF
)

REM Remove SDL obj
if "%~1"=="sdl" (
    echo Removing SDL obj folder...
    rmdir /s /q "%SDL_OBJ%"
    goto :EOF
)

REM Remove BAS obj
if "%~1"=="bas" (
    echo Removing BAS obj folder...
    rmdir /s /q "%BAS_OBJ%"
    goto :EOF
)

REM If no second argument, remove all
if "%~1"=="" (
    echo Removing obj folders in core and tests...
    rmdir /s /q "%CORE_DIR%\core\obj"
    rmdir /s /q "%CORE_DIR%\tests\obj"
    echo Removing bin folder...
    rmdir /s /q "%CORE_DIR%\bin"
    goto :EOF
)

REM === Subroutine definition ===
:CleanFolders
REM %* contains all arguments passed to the subroutine
for %%D in (%*) do (
    if exist "%%D" (
        echo Removing folder %%D...
        rmdir /s /q "%%D"
    ) else (
        echo Folder %%D does not exist, skipping.
    )
)

echo Invalid argument: %~1
echo Usage: clean.bat [objs|bin]
endlocal