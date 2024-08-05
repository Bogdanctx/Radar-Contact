#!/usr/bin/bash

# remove --show-leak-kinds=all (and --track-origins=yes) if there are many leaks in external libs
cat "${INPUT_FILENAME}" | tr -d '\r' | valgrind --leak-check=full --track-origins=yes --error-exitcode=0 ./"${ZIP_NAME}"/"${EXECUTABLE_NAME}" &
bash ./scripts/run_test.sh 10 1 2
