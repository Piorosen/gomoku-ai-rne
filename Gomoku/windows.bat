@echo off
echo ##### Make Visual Studio Projecct #####
cmd.exe /C ./ThirdParty/vcpkg/bootstrap-vcpkg.bat
cmd.exe /C ./ThirdParty/vcpkg/vcpkg install freeglut glew
cmd.exe /C ./ThirdParty/vcpkg/vcpkg integrate install
cmd.exe /C cmake -G "Visual Studio 16 2019" -A Win32