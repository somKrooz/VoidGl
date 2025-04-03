@echo off
setlocal enabledelayedexpansion

rem Output directory and executable
set OUTDIR=build
set OUT=%OUTDIR%\KroozEngine.exe

rem Ensure output directory exists
if not exist %OUTDIR% mkdir %OUTDIR%

rem Collect all source files manually
set SRC=KroozMain.cpp Obj.cpp Renderer.cpp Scene.cpp Shader.cpp Buffer.cpp Camera.cpp

rem Expand all .cpp files in vendor/imgui
set IMGUI_SRC=
for %%f in (vendor\imgui\*.cpp) do set IMGUI_SRC=!IMGUI_SRC! "%%f"

rem Expand all .cpp files in vendor/imgui/backends
set IMGUI_BACKEND_SRC=vendor\imgui\backends\imgui_impl_glfw.cpp vendor\imgui\backends\imgui_impl_opengl3.cpp


rem Compiler flags
set CFLAGS=/EHsc /W4 /std:c++17 /MD ^
    /I"vendor/glfw/include" ^
    /I"vendor/glew/include" ^
    /I"include" ^
    /I"vendor/glm" ^
    /I"vendor/OBJ" ^
    /I"vendor/imgui" ^
    /I"vendor/imgui/backends" ^
    /Fo%OUTDIR%/ ^
    /Fd%OUTDIR%/KroozEngine.pdb

rem Library paths
set LIBS=opengl32.lib glew32.lib glfw3.lib user32.lib gdi32.lib shell32.lib
set LIBPATHS=/LIBPATH:"vendor/glew/lib/Release/x64" /LIBPATH:"vendor/glfw/lib-vc2022"

echo Trying To Build %OUT%...

rem Compile all sources
cl %CFLAGS% /Fe%OUT% %SRC% %IMGUI_SRC% %IMGUI_BACKEND_SRC% /link %LIBPATHS% %LIBS%

if %ERRORLEVEL% NEQ 0 (
    echo Build Failed with errors.
    exit /b %ERRORLEVEL%
) else (
    echo Build Successful!
    echo We Are Winning This Shit...
    echo Run the application with: %OUT%
)

endlocal
