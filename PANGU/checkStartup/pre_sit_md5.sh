#!/bin/bash

TARGET_SCRIPT="startup.sh"
PREVIOUS_MD5="e6a450c19f56eb66f115912edd90552e"

CURRENT_CHECKSUM=$(md5sum "$TARGET_SCRIPT" | awk '{ print $1 }')

if [ "$CURRENT_CHECKSUM" = "$PREVIOUS_MD5" ]; then
    echo "New content added by modify_script.sh at $(date)" >> "$TARGET_SCRIPT"
else
    echo "Current MD5: $CURRENT_CHECKSUM"
    echo "Stored  MD5: $PREVIOUS_MD5"
    echo "MD5 mismatch. Please confirm changes and update PREVIOUS_MD5 to: $CURRENT_CHECKSUM"
    exit 1
fi