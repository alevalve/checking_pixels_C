# Checking Pixels (C Program)

This C program reads a raw RGB image file and analyzes the dominant color channel (Red, Green, Blue) for each pixel. It prints per-pixel RGB values and outputs the percentage of dominance for each color across the image.

---

## 📌 Features

- Reads raw image files (RGB format, no headers)
- Parses pixel-by-pixel RGB values
- Identifies dominant color channel per pixel
- Computes percentage of red/green/blue dominance
- Memory-efficient using dynamic allocation

---

## How It Works

1. Reads binary RGB image data from a `.rgb` file.
2. Iterates over each pixel:
   - Extracts red, green, and blue values.
   - Determines which channel is the strongest for each pixel.
3. Outputs:
   - RGB values for each pixel.
   - Overall percentage of red, green, or blue dominance.

---

## Compilation

Use `gcc` or any standard C compiler:

```bash
gcc -o color_analysis color_analysis.c
