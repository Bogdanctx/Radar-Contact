cat "${INPUT_FILENAME}" | ./"${ZIP_NAME}"/"${EXECUTABLE_NAME}" &
sleep 3 && xdotool search --name "${APP_WINDOW}" key X &&
sleep 1 && xdotool search --name "${APP_WINDOW}" key Y &&
sleep 1 && xdotool search --name "${APP_WINDOW}" key X &&
sleep 1 && xdotool search --name "${APP_WINDOW}" key Z &&
sleep 2 && xdotool search --name "${APP_WINDOW}" key Alt+F4
