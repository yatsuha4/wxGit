setlocal
set CURDIR=%~dp0
devenv.com "%CURDIR%wxGit.sln" /Project wxGitSetup\wxGitSetup.vdproj /Rebuild Release
