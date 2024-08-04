#!/usr/bin/bash

# remove --show-leak-kinds=all (and --track-origins=yes) if there are many leaks in external libs
valgrind --leak-check=full --error-exitcode=0 ./"${ZIP_NAME}"/"${EXECUTABLE_NAME}" &
bash ./scripts/run_test.sh 10 1 2
