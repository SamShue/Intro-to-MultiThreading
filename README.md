# Intro-to-MultiThreading
A tutorial on multithreading in C++ using an image processing example.

## Overview

This repository contains a tutorial for basic thread management in C++. Slides 
which cover the basic concepts are included along with 4 example applications.

The first application, "main_linear.cpp" is a simple application that prompts 
the user to enter a file name for a grayscale bitmap image. This image is then 
loaded and an edge detection algorithm is performed and the file is written back 
with the name "edges" appended to the file name. This process is linearly 
repeated 3 times. The goal of the tutorial is to enhance this application by 
utilizing threads to operate on the data while still prompting the user for 
inputs simultaneously.

The second application, thread_example.cpp, is a simple C++ thread demo. A dummy 
function is defined that will be executed by the thread objects. Each thread 
object will concurrently run 3 calls to the function. The application will then 
wait for those functions to resolve and exit the program.

The third application, main_threaded.cpp, utilizes thread objects to concurrently
process the images while the user enters in file names for additional images to 
process. If the user enters in file names before the first thread can resolve, 
a race condition occurs and a shared buffer is overwritten, ruining the results. 
This is intentional to visual demonstrate the effects of unmanaged shared 
resources amongst multiple concurrently running threads.

The fouth application, main_threaded_mutex.cpp, utilizes mutexes to lock the 
shared resource used in the previous application. The mutex will prevent the 
race condition from occurring by blocking access to the resource until the first 
thread has finished using it.

## How to Run

From a linux terminal, use the following g++ commands to build each application:
- main_linear.cpp

`g++ main_linear.cpp image_processing.cpp -o exe -std=c++11`

- thread_example.cpp

`g++ thread_example.cpp -o exe -std=c++11 -pthread`

- main_threaded.cpp

`g++ main_threaded.cpp image_processing.cpp -o exe -std=c++11 -pthread`

- main_threaded_mutex.cpp

`g++ main_threaded_linear.cpp image_processing.cpp -o exe -std=c++11 -pthread`

Once built, you can use the following command to run the executable:
`./exe`


