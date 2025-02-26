#!/bin/bash

# Check if version is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <version>"
    exit 1
fi

VERSION="$1"
ROOT_FOLDER="qalmari_boards_${VERSION}"

# List of folders to backup (modify this list)
FOLDERS=(
	"cores"
	"libraries"
	"scripts"
    "tools"
	"variants"
	"boards.txt"
	"changelog.md"
	"CODE_OF_CONDUCT.md"
	"keywords.txt"
	"LICENCE"
	"platform.txt"
	"programmers.txt"
	"README.md"
)

# Create a temporary root directory
mkdir -p "$ROOT_FOLDER"

# Copy the folders into the root directory
for folder in "${FOLDERS[@]}"; do
    cp -r "$folder" "$ROOT_FOLDER/"
done

# Output archive name
BACKUP_NAME="${ROOT_FOLDER}.tar.gz"

# Create the tar.gz archive with the root folder
tar -czvf "$BACKUP_NAME" "$ROOT_FOLDER"

# Remove the temporary root folder
rm -rf "$ROOT_FOLDER"

# Print success message
echo "Release completed: $BACKUP_NAME"
