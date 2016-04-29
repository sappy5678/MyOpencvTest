@echo off & setlocal EnableDelayedExpansion
for /f "delims=" %%i in ('"dir /a/s/b/on *0_**.bmp*"') do (
set file=%%~fi
set file=!file:/=/!
set /a line =0
echo !file! >> Lt10knums.txt
echo !line! >>Lt10knums.txt
)
