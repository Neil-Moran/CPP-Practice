@echo off

set COMMON_COMPILER_FLAGS=/nologo /EHsc- /GR- /fp:fast /Oi /W4 /Fm /FC

set DEBUG_FLAGS=/DDEBUG_BUILD /Od /MTd /Zi
set RELEASE_FLAGS =/O2

set COMPILER_FLAGS=%COMMON_COMPILER_FLAGS% %DEBUG_FLAGS%
REM set COMPILER_FLAGS=%COMMON_COMPILER_FLAGS% %RELEASE_FLAGS%

set LINKER_FLAGS=/INCREMENTAL:NO /opt:ref
REM set SYSTEM_LIBS=user32.lib gdi32.lib winmm.lib d3d11.lib

set BUILD_DIR=".\build"
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
pushd %BUILD_DIR%

cl %COMPILER_FLAGS% ../main.cpp ../DoubleLinkedList.cpp /link %LINKER_FLAGS% %SYSTEM_LIBS%

popd
echo Done