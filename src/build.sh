#!/bin/bash
# Build script for Hodgkin-Huxley simulator

echo "Building hh_sim..."
make clean >/dev/null 2>&1
make -j2
echo "Build completed successfully."
