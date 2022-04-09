%~d1
cd %~dp1
javaw -Xmx256m -jar "%~dp0sck.jar" view -fs %1
pause