#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern void asmImgCvtGrayIntToDouble(int n, uint8_t* intImage, double* floatImage);

void printDoubleImage(double *image, int width, int height) {
    int i, j; 
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%.2f ", image[i * width + j]); 
        }
        printf("\n");
    }
}

void printIntImage(uint8_t *image, int width, int height) {
    int i, j; 
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%d ", image[i * width + j]);
        }
        printf("\n");
    }
}

int main() {
    int width, height;
    int i; 

    printf("Enter height and width of the image: ");
    scanf("%d %d", &height, &width);

    uint8_t *intImage = (uint8_t *)malloc(width * height * sizeof(uint8_t));
    double *floatImage = (double *)malloc(width * height * sizeof(double));

    if (!intImage || !floatImage) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the pixel values (%d integers):\n", width * height);
    for (i = 0; i < width * height; i++) {
        scanf("%hhu", &intImage[i]); 
    }

    printf("\nOriginal Integer Image:\n");
    printIntImage(intImage, width, height);

    asmImgCvtGrayIntToDouble(width * height, intImage, floatImage);

    printf("\nConverted Float Image:\n");
    printDoubleImage(floatImage, width, height);

    free(intImage);
    free(floatImage);

    return 0;
}

