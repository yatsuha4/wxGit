setlocal
set CURDIR=%~dp0
call "%CURDIR%..\..\wxEditor\external\build\vs2022\wxWidgets.bat"
call "%CURDIR%..\..\external\build\vs2022\libgit2.bat"
MSBuild "%CURDIR%wxGit.sln" /t:Build /p:Configuration=Release;Platform=x64
