@echo off

SET EXECUTABLE_CLIENT=rtype_client.exe
SET EXECUTABLE_SERVER=rtype_server.exe
SET BUILD_DIR=build

IF EXIST "%EXECUTABLE_CLIENT%" (
    del "%EXECUTABLE_CLIENT%"
)

IF EXIST "%EXECUTABLE_SERVER%" (
    del "%EXECUTABLE_SERVER%"
)

IF EXIST "%BUILD_DIR%" (
    rmdir /s /q "%BUILD_DIR%"
)

cmake -S . -B "%BUILD_DIR%"

cmake --build "%BUILD_DIR%"