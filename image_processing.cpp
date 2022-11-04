#include "image_processing.h"

char temp[512 * 512];

char& get_value(char *arr, int row_len, int x, int y) {
    return arr[x * row_len + y];
}

void gaussianBlur(char* image, unsigned int rows, unsigned int cols){
    //char* temp = new char[rows * cols];
    memcpy(temp, image, rows*cols);
    
    unsigned int kernel[5][5] = {{1, 4, 6, 4, 1},
                                 {4, 16, 24, 16, 4},
                                 {16, 24, 36, 24, 16},
                                 {4, 16, 24, 16, 4},
                                 {1, 4, 6, 4, 1}};
                          
                          
    unsigned int sum = 0;              
    for(unsigned int i = 0; i < 5; i++)
        for(unsigned int j = 0; j < 5; j++)
            sum += kernel[i][j];

    for(unsigned int i = 2; i < rows - 2; i++){
        for(unsigned int j = 2; j < cols - 2; j++){
            float newVal =  
                kernel[0][0]*(unsigned char)get_value(temp, cols, i-2, j-2) + 
                kernel[0][1]*(unsigned char)get_value(temp, cols, i-2, j-1) +
                kernel[0][2]*(unsigned char)get_value(temp, cols, i-2, j) +
                kernel[0][3]*(unsigned char)get_value(temp, cols, i-2, j+1) +
                kernel[0][4]*(unsigned char)get_value(temp, cols, i-2, j+2) +
                kernel[1][0]*(unsigned char)get_value(temp, cols, i-1, j-2) + 
                kernel[1][1]*(unsigned char)get_value(temp, cols, i-1, j-1) +
                kernel[1][2]*(unsigned char)get_value(temp, cols, i-1, j) +
                kernel[1][3]*(unsigned char)get_value(temp, cols, i-1, j+1) +
                kernel[1][4]*(unsigned char)get_value(temp, cols, i-1, j+2) +
                kernel[2][0]*(unsigned char)get_value(temp, cols, i, j-2) + 
                kernel[2][1]*(unsigned char)get_value(temp, cols, i, j-1) +
                kernel[2][2]*(unsigned char)get_value(temp, cols, i, j) +
                kernel[2][3]*(unsigned char)get_value(temp, cols, i, j+1) +
                kernel[2][4]*(unsigned char)get_value(temp, cols, i, j+2) +
                kernel[3][0]*(unsigned char)get_value(temp, cols, i+1, j-2) + 
                kernel[3][1]*(unsigned char)get_value(temp, cols, i+1, j-1) +
                kernel[3][2]*(unsigned char)get_value(temp, cols, i+1, j) +
                kernel[3][3]*(unsigned char)get_value(temp, cols, i+1, j+1) +
                kernel[3][4]*(unsigned char)get_value(temp, cols, i+1, j+2) +
                kernel[4][0]*(unsigned char)get_value(temp, cols, i+2, j-2) + 
                kernel[4][1]*(unsigned char)get_value(temp, cols, i+2, j-1) +
                kernel[4][2]*(unsigned char)get_value(temp, cols, i+2, j) +
                kernel[4][3]*(unsigned char)get_value(temp, cols, i+2, j+1) +
                kernel[4][4]*(unsigned char)get_value(temp, cols, i+2, j+2);
                            
                newVal = newVal / sum;
                get_value(image, cols, i, j) = newVal;
                
                // Delay to make processing take longer
                if(j % 10 == 0) usleep(1);
        }
    }
    
    //delete[] temp;
}

void laplacianEdgeDetection(char* image, unsigned int rows, unsigned int cols){
    //char* temp = new char[rows * cols];
    memcpy(temp, image, rows*cols);
    
    int kernel[3][3] = {{-1, -1, -1}, 
                        {-1, 8, -1},
                        {-1, -1, -1}};
            
    unsigned int sum = 0;              
    for(unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            sum += kernel[i][j];

    for(unsigned int i = 2; i < rows - 2; i++){
        for(unsigned int j = 2; j < cols - 2; j++){
            int newVal = 
                kernel[0][0]*(unsigned char)get_value(temp, cols, i-1, j-1) + 
                kernel[0][1]*(unsigned char)get_value(temp, cols, i-1, j) +
                kernel[0][2]*(unsigned char)get_value(temp, cols, i-1, j+1) +
                kernel[1][0]*(unsigned char)get_value(temp, cols, i, j-1) + 
                kernel[1][1]*(unsigned char)get_value(temp, cols, i, j) +
                kernel[1][2]*(unsigned char)get_value(temp, cols, i, j+1) +
                kernel[2][0]*(unsigned char)get_value(temp, cols, i+1, j-1) + 
                kernel[2][1]*(unsigned char)get_value(temp, cols, i+1, j) +
                kernel[2][2]*(unsigned char)get_value(temp, cols, i+1, j+1);
            
            newVal = newVal < 0 ? 0 : newVal;
            newVal = newVal > 255 ? 255 : newVal;
            get_value(image, cols, i, j) = newVal;
            
            // Delay to make processing take longer
            if(j % 10 == 0) usleep(1);
        }
    }
    
    //delete[] temp;
}