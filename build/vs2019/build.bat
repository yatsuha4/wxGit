setlocal
set CURDIR=%~dp0
call "%CURDIR%..\..\wxEditor\external\build\vs2019\build.bat"
call "%CURDIR%..\..\external\build\vs2019\libgit2.bat"
MSBuild "%CURDIR%wxGit\wxGit.sln" /t:Build /p:Configuration=Release;Platform=x64
