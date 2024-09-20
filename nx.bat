@ECHO OFF
SETLOCAL
SET path_to_root=%~dp0
WHERE node >nul 2>nul
IF %ERRORLEVEL% NEQ 0 (ECHO Nx requires NodeJS to be available. To install NodeJS and PNPM, see: https://pnpm.io/installation . & GOTO exit)
WHERE npm >nul 2>nul
IF %ERRORLEVEL% NEQ 0 (ECHO Nx requires pnpm to be available. To install NodeJS and PNPM, see: https://pnpm.io/installation . & GOTO exit)
node %path_to_root%\.nx\nxw.js %*
:exit
  cmd /c exit /b %ERRORLEVEL%
