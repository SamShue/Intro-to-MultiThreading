#include <iostream>
#include <thread>
#include <fstream>
#include <stdio.h>
#include "image_processing.h"

using namespace std;

const unsigned int BITMAP_HEADER_BYTES = 54;

bool readGrayscaleBmp(const string& fileName, char*& image, 
                      unsigned int& fileSize, unsigned int& rows, 
                      unsigned int& cols, unsigned int& dataIndex);
bool writeBmp(const string& fileName, const char* buffer, const int& fileSize);
  
int main() {
    char* buffer;
    unsigned int fileSize, rows, cols, dataIndex;
    string fileName;
        
    bool loop = true;
    while(loop){
        cout << "Please input a file name (file needs to be .bmp):" << endl;
        cin >> fileName;
        
        if(readGrayscaleBmp(fileName, buffer, fileSize, rows, cols, dataIndex)){
        
            gaussianBlur(&buffer[dataIndex], rows, cols);
            
            laplacianEdgeDetection(&buffer[dataIndex], rows, cols);
            
            // Make new file name to write to
            std::string::size_type pos = fileName.find('.');
            writeBmp(fileName.substr(0, pos) + "_blurred" + fileName.substr(pos, fileName.size()), buffer, fileSize);
        } else {
            cout << "Unable to open file" << endl;
        }
        
        cout << "Process another image? (Y = yes)" << endl;
        char userIn;
        cin >> userIn;
        loop = (userIn == 'Y') || (userIn == 'y');
    }
    
    return 0;
}

bool readGrayscaleBmp(const string& fileName, char*& image, 
                      unsigned int& fileSize, unsigned int& rows, 
                      unsigned int& cols, unsigned int& dataIndex) {
    std::ifstream file(fileName);

    if (file) {
        // Get length of file
        file.seekg(0,std::ios::end);
        unsigned int length = file.tellg();
        file.seekg(0,std::ios::beg);

        char* buffer = new char[length];
        file.read(buffer, length);

        fileSize = (unsigned int)((buffer[5] << 24) | 
                                (buffer[4] << 16) | (buffer[3] << 8) | 
                                buffer[2]);
        
        dataIndex = (unsigned int)((buffer[13] << 24) | 
                                 (buffer[12] << 16) | (buffer[11] << 8) | 
                                 buffer[10]);
        
        cols = (unsigned int)((buffer[13] << 21) | 
                             (buffer[20] << 16) | (buffer[19] << 8) | 
                             buffer[18]);
        
        rows = (unsigned int)((buffer[13] << 21) | 
                              (buffer[20] << 16) | (buffer[19] << 8) | 
                              buffer[18]);
        
        unsigned int bitsPerPixel = (unsigned int)((buffer[0x1D] << 8) | 
                                    buffer[0x1C]);
        
        image = buffer;
        
        return true;
    }
    
    return false;
}

bool writeBmp(const string& fileName, const char* buffer, const int& fileSize){
    std::ofstream file(fileName);

    if (file) {
        // Get length of file
        file.write(buffer, fileSize);
        
        return true;
    }
    
    return false;
}