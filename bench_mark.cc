#include <iostream>
#include <chrono>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

int main() {
  //Create the variables for the program.                                                                                                                                                                                                     
  unsigned int bytes = 1024; //Number of bytes in each buffer.                                                                                                                                                                                
  unsigned int size = 256; //Number of idices in each buffer.                                                                                                                                                                                 
  std::vector<int> indices; //Buffer of indices.                                                                                                                                                                                              
  std::vector<int> buffer; //Buffer to be read from.                                                                                                                                                                                          
  for(int i = 0; i < size; i++) {
    indices.push_back(i);
    buffer.push_back(i);
  } //both buffer and indices are built like (0, 1, 2, ..., size - 1) now.                                                                                                                                                                    
  int x; //variable to be read into.                                                                                                                                                                                                          
  std::cout << "# of bytes.   Time." << std::endl; //Print title.                                                                                                                                                                             

  //Now we iterate through every buffer size.                                                                                                                                                                                                 
  for(int power = 0; power < 16; power++) {
    std::cout << std::to_string(bytes) << "   "; //Print byte amount.                                                                                                                                                                         
    double duration = 0.0; //Initial value for time.                                                                                                                                                                                          

    //Now we read the buffer 100 times and save the fastest run.                                                                                                                                                                              
    for(int test = 0; test < 100; test++)  {
      std::random_shuffle (indices.begin(), indices.end()); //Shuffle the indices.                                                                                                                                                            
      auto t1 = std::chrono::high_resolution_clock::now(); //Start the timer.                                                                                                                                                                 

      //The actual reading from the buffer.                                                                                                                                                                                                   
      for(unsigned int byte1 = 0; byte1 < size; byte1++) {
        x = buffer[indices[byte1]];
      }

      auto t2 = std::chrono::high_resolution_clock::now(); //Stop the timer.                                                                                                                                                                  
      auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count(); //Find current run time.                                                                                                                               

      //If current runtime is faster than the last record, save it as current record.                                                                                                                                                         
      if(static_cast<double>(t) < duration || duration == 0.0) {
        duration = t;
      }

    }

    double time = static_cast<double>(duration) * 1000.00 / static_cast<double>(bytes); //Get time in nanoseconds/byte.                                                                                                                       
    std::cout << time << "   'X' = " << std::to_string(x) << std::endl; //Print time and 'x' in order to maintain its necessity.                                                                                                              

    //Double the size of both vectors.                                                                                                                                                                                                        
    for(int j = 0; j < size; j++) {
      indices.push_back(j + size);
      buffer.push_back(j +size);
    }

    bytes *= 2; //Compute next number of bytes.                                                                                                                                                                                               
    size *= 2; //Compute next buffer size.                                                                                                                                                                                                    
  }
  return 0;
}

