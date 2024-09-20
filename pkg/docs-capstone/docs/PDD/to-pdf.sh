#!/bin/bash

set +x

# Convert PDF to individual images
convert -density 300 "$1" -quality 100 output%d.png

# Loop through each image file
for file in output*.png; do
    # Change background color
    echo "converting $file"
    convert "$file" -background "#1e1e2e" -alpha remove -alpha off "$file"
done

# Convert images back to PDF
convert output*.png output.pdf

# Remove temporary image files
# rm output*.png
