#!/bin/bash

EXECUTABLE_CLIENT="rtype_client"

EXECUTABLE_SERVER="rtype_server"

BUILD_DIR="build"

if [ -f "$EXECUTABLE_CLIENT" ]; then
    rm -f "$EXECUTABLE_CLIENT"
fi

if [ -f "$EXECUTABLE_SERVER" ]; then
    rm -f "$EXECUTABLE_SERVER"
fi

if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
fi

cmake -S . -B "$BUILD_DIR"

cmake --build "$BUILD_DIR"