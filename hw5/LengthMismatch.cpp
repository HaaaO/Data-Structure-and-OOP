#include "LengthMismatch.h"


 LengthMismatch::LengthMismatch(int i,int j) 
  : msg("Input data structures have lengths [" + std::to_string(i) + "] and [" + std::to_string(j)+ "]"){

  }
  
 const char* LengthMismatch::what() const noexcept{
  	return msg.c_str();
  }