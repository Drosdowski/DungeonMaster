%~d1
cd %~dp1
java -Xmx192m -jar "%~dp0sck.jar" extract %1
pause