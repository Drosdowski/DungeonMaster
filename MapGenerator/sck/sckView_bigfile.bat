%~d1
cd %~dp1
java -Xmx256m -jar "%~dp0sck.jar" view %1
pause