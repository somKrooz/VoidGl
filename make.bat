@echo off
setlocal

set OUTDIR=build
set OUT=%OUTDIR%\KroozEngine.exe

set SRC=KroozMain.cpp Obj.cpp Renderer.cpp Scene.cpp Shader.cpp Buffer.cpp Camera.cpp


REM Compiler flags
set CFLAGS=/EHsc /W4 /std:c++17 /MD ^
    /I"./vendor/glfw/include" ^
    /I"./vendor/glew/include" ^
    /I"./include" ^
    /I"./vendor/glm" ^
    /I"./vendor/OBJ" ^
    /Fo%OUTDIR%/ ^
    /Fd%OUTDIR%/KroozEngine.pdb


set LIBS=opengl32.lib glew32.lib glfw3.lib user32.lib gdi32.lib shell32.lib

set LIBPATHS=/LIBPATH:"./vendor/glew/lib/Release/x64" /LIBPATH:"./vendor/glfw/lib-vc2022"

echo Trying To Build %OUT%...

REM Build the project
cl %CFLAGS% /Fe%OUT% %SRC% /link %LIBPATHS% %LIBS%

IF %ERRORLEVEL% NEQ 0 (
    echo Build Failed with errors.
) ELSE (
    echo Building Done...!
    echo We Are Wininng This Shit....
    echo Run the application with: %OUT%
)
