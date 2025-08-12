#!/bin/bash

# Target script to monitor for changes
TARGET_SCRIPT="startup.sh"

# Store the last known git commit hash of the target script
# This should be manually updated when legitimate changes are made
LAST_KNOWN_COMMIT="HEAD"

# Get the current git commit hash for the target script
CURRENT_COMMIT=$(git log -n 1 --pretty=format:%H -- "$TARGET_SCRIPT")

# Check if git command succeeded
if [ -z "$CURRENT_COMMIT" ]; then
    echo "Error: Unable to get git commit hash. Ensure the file is tracked by git."
    exit 1
fi

echo "Current commit: $CURRENT_COMMIT"
echo "Last known commit: $LAST_KNOWN_COMMIT"

# Compare current commit with stored commit
if [ "$CURRENT_COMMIT" = "$LAST_KNOWN_COMMIT" ]; then
    echo "No changes detected in $TARGET_SCRIPT. Proceeding with modification..."
    
    # Add modification timestamp to target script
    echo "# Modified by pre_sit.sh at $(date)" >> "$TARGET_SCRIPT"
    
    echo "Modification complete!"
    echo "Note: To run again after legitimate changes, update LAST_KNOWN_COMMIT to: $CURRENT_COMMIT"
else
    echo "Changes detected in $TARGET_SCRIPT!"
    echo "Current commit: $CURRENT_COMMIT"
    echo "Last known commit: $LAST_KNOWN_COMMIT"
    echo "Please review changes and update LAST_KNOWN_COMMIT if changes are intentional."
    exit 1
fi