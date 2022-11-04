// Build command: g++ main_threaded.cpp image_processing.cpp -o test -std=c++11 -pthread
#include <iostream>
#include <thread>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include "image_processing.h"

using namespace std;

const unsigned int BITMAP_HEADER_BYTES = 54;

unsigned int totalThreadNum = 0;

bool readGrayscaleBmp(const string& fileName, char*& image, 
                      unsigned int& fileSize, unsigned int& rows, 
                      unsigned int& cols, unsigned int& dataIndex);
bool writeBmp(const string& fileName, const char* buffer, const int& fileSize);

void processImage(string fileName){
    int threadNum = ++totalThreadNum;
    
    cout << "Processing image " << threadNum << "..." << endl;
    
    char* buffer;
    unsigned int fileSize, rows, cols, dataIndex;
    
    if(readGrayscaleBmp(fileName, buffer, fileSize, rows, cols, dataIndex)){
            
        gaussianBlur(&buffer[dataIndex], rows, cols);
        
        laplacianEdgeDetection(&buffer[dataIndex], rows, cols);
        
        // Make new file name to write to
        std::string::size_type pos = fileName.find('.');
        writeBmp(fileName.substr(0, pos) + "_edges" + fileName.substr(pos, fileName.size()), buffer, fileSize);
    } else {
        cout << "Unable to open file" << endl;
    }
    
    cout << "Processing image " << threadNum << " complete!" << endl;
}
  
int main() {
    string fileName;

    cout << "Please input a file name:" << endl;
    cin >> fileName;
    
    thread th1(processImage, fileName);
    
    cout << "Please input a file name:" << endl;
    cin >> fileName;
    
    thread th2(processImage, fileName);
    
    cout << "Please input a file name:" << endl;
    cin >> fileName;
    
    thread th3(processImage, fileName);
    
    // wait for each thread to complete
    th1.join();
    th2.join();
    th3.join();
    
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