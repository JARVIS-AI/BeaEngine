@echo off


set INCLUDE=C:\PellesC\Include\;C:\PellesC\Include\Win\;
set LIB=C:\PellesC\Lib\;C:\PellesC\Lib\Win\;
set name=BeaEngine

echo ____________________________________
echo *
echo *  		COMPILATION 
echo *
echo ____________________________________
rem \PellesC\bin\Pocc /Ze /W2  %name%.c
\MinGW\bin\gcc -c %name%.c -std=c99  -Wall -W -Wextra -Wconversion -Wno-long-long -Wshadow -Wpointer-arith -Wcast-qual  -Wcast-align -Wwrite-strings -pedantic -ansi -pipe -fno-common -fshort-enums  -o  %name%.obj 
rem -std=c99  -Wall -W -Wextra -Wconversion -Wno-long-long -Wshadow -Wpointer-arith -Wcast-qual  -Wcast-align -Wwrite-strings -pedantic -ansi -pipe -fno-common -fshort-enums
echo ____________________________________
echo *
echo *   CREATE LIB with POLIB.EXE (Pelles C)
echo *
echo ____________________________________
\PellesC\bin\Polib /out:%name%.lib %name%.obj
pause





