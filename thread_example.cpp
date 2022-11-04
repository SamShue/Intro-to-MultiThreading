#include <iostream>
#include <thread>
#include <fstream>
#include <stdio.h>

using namespace std;
  
// A dummy function
void foo(int Z)
{
    for (int i = 0; i < Z; i++) {
        cout << "Thread using function"
               " pointer as callable\n";
    }
}
  
int main() {
    
    thread th1(foo, 3);
    
    thread th2(foo, 2);
    
    thread th3(foo, 1);
  
    // Wait for the threads to finish
    // Wait for thread t1 to finish
    th1.join();
  
    // Wait for thread t2 to finish
    th2.join();
  
    // Wait for thread t3 to finish
    th3.join();
    
    return 0;
}