@echo off
color 0a
echo Generating Project Files For MicrosoftVisualStudio2022.
cd ..\
Vendor\Premake\premake5.exe vs2022
pause