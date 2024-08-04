#!/usr/bin/bash

cat "${INPUT_FILENAME}" | tr -d '\r' | ./"${ZIP_NAME}"/"${EXECUTABLE_NAME}" &
bash ./scripts/run_test.sh 3 1 2
