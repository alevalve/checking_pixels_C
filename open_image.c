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

int count_color(int *colorList, int length) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (colorList[i] == 1) {
            count++;
        }
    }
    return count;
}

void get_greater(const byte *imageData, unsigned int w, unsigned int h, float percentages[3]){
    int *list_red = (int *)malloc(w * h * sizeof(int));
    int *list_green = (int *)malloc(w * h * sizeof(int));
    int *list_blue = (int *)malloc(w * h * sizeof(int));

    if (!list_red || !list_green || !list_blue) {
        puts("\n Memory allocation for color lists failed\n");
        free(list_red);
        free(list_green);
        free(list_blue);
        return;
    }

    byte pixelRed, pixelGreen, pixelBlue;
    unsigned int index = 0;

    for (unsigned int y = 0; y < h; ++y) {
        for (unsigned int x = 0; x < w; ++x, ++index) {
            get_pixel(imageData, w, x, y, &pixelRed, &pixelGreen, &pixelBlue);

            if (pixelRed > pixelGreen && pixelRed > pixelBlue) {
                list_red[index] = 1;
            } else if (pixelGreen > pixelRed && pixelGreen > pixelBlue) {
                list_green[index] = 1;
            } else if (pixelBlue > pixelRed && pixelBlue > pixelGreen) {
                list_blue[index] = 1;
            }
        }
    }

    int redDominance = count_color(list_red, w * h);
    percentages[0] = ((float)redDominance / (w * h)) * 100;

    int greenDominance = count_color(list_green, w * h);
    percentages[1] = ((float)greenDominance / (w * h)) * 100;

    int blueDominance = count_color(list_blue, w * h);
    percentages[2] = ((float)blueDominance / (w * h)) * 100;

    free(list_red);
    free(list_green);
    free(list_blue);
}


int main()
{
    FILE *image;
    unsigned int width, height;

    
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

    float colorPercentages[3];
    
    get_greater(imageData, width, height, colorPercentages);
    
    printf("Percentage of dominant per color - Red: %.2f%%, Green: %.2f%%, Blue: %.2f%%\n", colorPercentages[0], colorPercentages[1], colorPercentages[2]);

    free(imageData);
    return 0;
}

