@echo off


set INCLUDE=C:\PellesC\Include\;C:\PellesC\Include\Win\;
set LIB=C:\PellesC\Lib\;C:\PellesC\Lib\Win\;
set name=BeaEngine

echo ____________________________________
echo *
echo *  		COMPILATION 
echo *
echo ____________________________________
\PellesC\bin\Pocc /Ze /W2  %name%.c
rem \MinGW\bin\gcc -c %name%.c -std=c99 -pedantic -o  %name%.obj 

echo ____________________________________
echo *
echo *   CREATE LIB with POLIB.EXE (Pelles C)
echo *
echo ____________________________________
\PellesC\bin\Polib /out:%name%.lib %name%.obj
pause





