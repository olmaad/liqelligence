@echo off

set PROJECT_DIR=%~dp0..

cmake -S "%PROJECT_DIR%" -B "%PROJECT_DIR%/build"