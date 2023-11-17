#include <stdio.h>
#include <stdlib.h> 
 

typedef unsigned char byte;


void get_pixel(const byte *image, unsigned int w, unsigned int x, unsigned int y, byte *red, byte *green, byte *blue)
{
    const byte *pixel = image + w * y * 3 + 3 * x;
    *red = pixel[0];
    *green = pixel[1];
    *blue = pixel[2];
}
 
int main()
{
    FILE *image;
    unsigned int width, height;

    // Assuming width and height are provided or read from the image file
    char filename[256];
    printf("Enter the filename of the image: ");
    scanf("%255s", filename); // Get the filename from the user
    printf("Enter image width: ");
    scanf("%d", &width);
    printf("Enter image height: ");
    scanf("%d", &height);

    if ((image = fopen(filename, "rb")) == NULL)
    {
        puts("\n Cannot open the image\n");
        return 1;
    }

    // Allocate memory for the image data
    byte *imageData = (byte *)malloc(width * height * 3 * sizeof(byte));
    if (imageData == NULL)
    {
        puts("\n Memory allocation failed\n");
        fclose(image);
        return 1;
    }

    // Read image data from file
    fread(imageData, sizeof(byte), width * height * 3, image);
    fclose(image);

    // Process each pixel
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            byte red, green, blue;
            get_pixel(imageData, width, x, y, &red, &green, &blue);
            printf("Pixel [%u, %u] - Red: %d, Green: %d, Blue: %d\n", x, y, red, green, blue);
        }
    }

    // Free the allocated memory
    free(imageData);

    return 0;
}