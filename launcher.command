#!/bin/sh
cd "$(dirname "${0}")" && ASAN_OPTIONS=detect_container_overflow=0 ./radar_contact
