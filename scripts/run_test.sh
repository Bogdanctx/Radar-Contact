#!/usr/bin/bash

startup_sleep=$1
command_sleep=$2
exit_sleep=$3

sleep "${startup_sleep}" && xdotool search --name "${APP_WINDOW}" key T &&
sleep "${command_sleep}" && xdotool search --name "${APP_WINDOW}" key R &&
sleep "${exit_sleep}" && xdotool search --name "${APP_WINDOW}" key Alt+F4
