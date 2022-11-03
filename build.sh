#!/bin/bash
cmake -B build -Wno-dev -DCMAKE_BUILD_TYPE=Release
cmake --build build -j 2