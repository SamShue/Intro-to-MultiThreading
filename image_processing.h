#ifndef IMAGE_PROCESSING
#define IMAGE_PROCESSING

#include <cstring>
#include <stdint.h>
#include <unistd.h>

char& get_value(char *arr, int row_len, int x, int y);
void gaussianBlur(char* image, unsigned int rows, unsigned int cols);
void laplacianEdgeDetection(char* image, unsigned int rows, unsigned int cols);

#endif