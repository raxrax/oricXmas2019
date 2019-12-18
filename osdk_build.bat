@ECHO OFF

 
::
:: Initial check.
:: Verify if the SDK is correctly configurated
::
IF "%OSDK%"=="" GOTO ErCfg


::
:: Set the build paremeters
::
CALL osdk_config.bat

CALL %OSDK%\bin\make.bat %OSDKFILE%

echo %osdk%

%OSDK%\bin\taptap ren build\%OSDKNAME%.tap "xmass2019" 0

CALL %OSDK%\bin\execute.bat

GOTO End


::
:: Outputs an error message
::
:ErCfg
ECHO == ERROR ==
ECHO The Oric SDK was not configured properly
ECHO You should have a OSDK environment variable setted to the location of the SDK
IF "%OSDKBRIEF%"=="" PAUSE
GOTO End


:End
pause
