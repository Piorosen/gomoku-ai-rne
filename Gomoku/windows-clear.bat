@echo off
echo ##### Remove : Visual Studio Projecct #####

cmd.exe /C .\ThirdParty\cmake\cmake-3.21.3-windows-x86_64.msi
cmd.exe /C .\ThirdParty\vcpkg\vcpkg integrate remove

echo ##### Remove : Visual Studio Project #####


IF "%1" == "EXEC" (
	goto END
) ELSE (
	goto PARAM
)

:PARAM
PAUSE
goto END

:END
