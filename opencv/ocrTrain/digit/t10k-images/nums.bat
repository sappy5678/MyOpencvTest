@echo off & setlocal EnableDelayedExpansion
for /f "delims=" %%i in ('"dir /a/s/b/on *0_**.bmp*"') do (
set file=%%~fi
set file=!file:/=/!
set /a line =0
echo !file! >> t10knums.txt
echo !line! >>t10knums.txt
)
for /f "delims=" %%i in ('"dir /a/s/b/on *1_**.bmp*"') do (
set file=%%~fi
set file=!file:/=/!
set /a line =1
echo !file! >> t10knums.txt
echo !line! >>t10knums.txt
)
for /f "delims=" %%i in ('"dir /a/s/b/on *2_**.bmp*"') do (
set file=%%~fi
set file=!file:/=/!
set /a line =2
echo !file! >> t10knums.txt
echo !line! >>t10knums.txt
)
for /f "delims=" %%i in ('"dir /a/s/b/on *3_**.bmp*"') do (
set file=%%~fi
set file=!file:/=/!
set /a line =3
echo !file! >> t10knums.txt
echo !line! >>t10knums.txt
)
for /f "delims=" %%i in ('"dir /a/s/b/on *4_**.bmp*"') do (
set file=%%~fi
set file=!file:/=/!
set /a line =4
echo !file! >> t10knums.txt
echo !line! >>t10knums.txt
)
for /f "delims=" %%i in ('"dir /a/s/b/on *5_**.bmp*"') do (
set file=%%~fi
set file=!file:/=/!
set /a line =5
echo !file! >> t10knums.txt
echo !line! >>t10knums.txt
)
for /f "delims=" %%i in ('"dir /a/s/b/on *6_**.bmp*"') do (
set file=%%~fi
set file=!file:/=/!
set /a line =6
echo !file! >> t10knums.txt
echo !line! >>t10knums.txt
)
for /f "delims=" %%i in ('"dir /a/s/b/on *7_**.bmp*"') do (
set file=%%~fi
set file=!file:/=/!
set /a line =7
echo !file! >> t10knums.txt
echo !line! >>t10knums.txt
)
for /f "delims=" %%i in ('"dir /a/s/b/on *8_**.bmp*"') do (
set file=%%~fi
set file=!file:/=/!
set /a line =8
echo !file! >> t10knums.txt
echo !line! >>t10knums.txt
)
for /f "delims=" %%i in ('"dir /a/s/b/on *9_**.bmp*"') do (
set file=%%~fi
set file=!file:/=/!
set /a line =9
echo !file! >> t10knums.txt
echo !line! >>t10knums.txt
)