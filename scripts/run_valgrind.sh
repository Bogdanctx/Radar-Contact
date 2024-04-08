cat "${INPUT_FILENAME}" | valgrind --leak-check=full --track-origins=yes --error-exitcode=0 ./"${ZIP_NAME}"/"${EXECUTABLE_NAME}" &
sleep 10 && xdotool search --name "${APP_WINDOW}" key X &&
sleep 1 && xdotool search --name  "${APP_WINDOW}" key Y &&
sleep 1 && xdotool search --name  "${APP_WINDOW}" key X &&
sleep 1 && xdotool search --name  "${APP_WINDOW}" key Z &&
sleep 2 && xdotool search --name  "${APP_WINDOW}" key Alt+F4
