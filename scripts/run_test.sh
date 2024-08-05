#!/usr/bin/bash

startup_sleep=$1
command_sleep=$2
exit_sleep=$3

sleep "${startup_sleep}" && xdotool search --name "${APP_WINDOW}" key X &&
sleep "${command_sleep}" && xdotool search --name "${APP_WINDOW}" key Y &&
sleep "${command_sleep}" && xdotool search --name "${APP_WINDOW}" key X &&
sleep "${command_sleep}" && xdotool search --name "${APP_WINDOW}" key Z &&
sleep "${exit_sleep}" && xdotool search --name "${APP_WINDOW}" key Alt+F4
