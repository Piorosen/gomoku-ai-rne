@echo off
echo ##### Remove : Visual Studio Projecct #####

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
