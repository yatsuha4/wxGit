setlocal
set CURDIR=%~dp0
set TMPDIR=%CURDIR%build_libgit2
set DSTDIR=%CURDIR%libgit2

rmdir /s /q "%DSTDIR"
mkdir "%TMPDIR%"
pushd "%TMPDIR%"
cmake "%CURDIR%..\..\libgit2" -G "Visual Studio 16 2019" -A x64 -DCMAKE_INSTALL_PREFIX="%DSTDIR%" -DBUILD_SHARED_LIBS=off
cmake --build . --config Release --target install
popd
rmdir /s /q "%TMPDIR%"
