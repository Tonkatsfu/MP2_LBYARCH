#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>

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

void generateRandomImage(uint8_t *image, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        image[i] = rand() % 256;  
    }
}

void timeFunction(int width, int height, uint8_t* intImage, double* floatImage) {
    LARGE_INTEGER start_time, end_time, frequency;
    QueryPerformanceFrequency(&frequency);
    double total_time = 0.0;
    int num_runs = 30;

    for (int i = 0; i < num_runs; i++) {
        QueryPerformanceCounter(&start_time);
        
        asmImgCvtGrayIntToDouble(width * height, intImage, floatImage);

        QueryPerformanceCounter(&end_time);
        
        total_time += (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;
    }
    
    printf("\nAverage execution time for %dx%d image (%d runs): %.9f seconds\n", height, width, num_runs, total_time / num_runs);
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

    timeFunction(width, height, intImage, floatImage);

    free(intImage);
    free(floatImage);

    // Calculate Average Execution Time for 10x10, 100x100, 1000x1000 Matrices
    int sizes[][2] = {{10, 10}, {100, 100}, {1000, 1000}};
    
    for (int i = 0; i < 3; i++) {
        width = sizes[i][0];
        height = sizes[i][1];

        uint8_t *intImage = (uint8_t *)malloc(width * height * sizeof(uint8_t));
        double *floatImage = (double *)malloc(width * height * sizeof(double));

        if (!intImage || !floatImage) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        generateRandomImage(intImage, width, height);

        timeFunction(width, height, intImage, floatImage);

        free(intImage);
        free(floatImage);
    }
    
    return 0;
}

