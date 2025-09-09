@echo off
REM =========================================
REM Project build helper for Windows
REM Creates directories, copies DLLs, then runs make
REM =========================================

REM Define directories
set CORE_DIR=core
set SDL_OBJ=%CORE_DIR%\SDL\obj
set BAS_OBJ=%CORE_DIR%\BAS\obj
REM List of directories to create
set CORE_OBJ=%SDL_OBJ% %BAS_OBJ% %OGL_OBJ%

REM Iterate over each directory and create it if it doesn't exist
for %%d in (%CORE_OBJ%) do (
    if not exist "%%d" (
        echo Creating %%d
        mkdir "%%d"
    )
)

set TEST_DIR=tests
set TEST_OBJ=%TEST_DIR%\obj
set BIN_DIR=bin
set DLLS_DIR=DLLS
set BAT_DIR=batch
REM Create directories if they don't exist
for %%d in ("%TEST_OBJ%" "%BIN_DIR%") do (
    if not exist "%%d" (
        echo Creating directory %%d
        mkdir "%%d"
    )
)

REM Copy all DLLs to BIN_DIR
for %%f in ("%DLLS_DIR%\*.dll") do (
    echo Copying %%f to %BIN_DIR%
    copy /Y "%%f" "%BIN_DIR%" >nul
)
echo Copying %BAT_DIR%\runbuild.bat to %BIN_DIR%
copy /Y "%BAT_DIR%\runbuild.bat" "%BIN_DIR%" >nul



REM Call make
echo Running make...
make %*
