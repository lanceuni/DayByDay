#!/bin/bash

TARGET_SCRIPT="startup.sh"
LAST_KNOWN_COMMIT="54fdbf578ad4784b68e812547c9e443b7a09fc44"

# Get the current git commit hash for the target script
CURRENT_COMMIT=$(git log -n 1 --pretty=format:%H -- "$TARGET_SCRIPT")

# Compare current commit with stored commit
if [ "$CURRENT_COMMIT" = "$LAST_KNOWN_COMMIT" ]; then
    echo "No changes detected in $TARGET_SCRIPT. Proceeding with modification..."
    echo "# Modified by pre_sit.sh at $(date)" >> "$TARGET_SCRIPT"
else
    echo "Current $TARGET_SCRIPT commit: $CURRENT_COMMIT"
    echo "Last    $TARGET_SCRIPT commit: $LAST_KNOWN_COMMIT"
    echo "Please review changes and update LAST_KNOWN_COMMIT."
    exit 1
fi