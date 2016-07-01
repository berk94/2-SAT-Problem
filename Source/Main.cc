#include <cstdio>
#include <string>

#include "SatSolver.h"

/*  ! DO NOT MODIFY THIS FILE  !  */

std::string ExtractFilenameFromPath(std::string path){  
  size_t start_pos = path.find_last_of("\\/") +1;
  size_t num_chars = path.find_last_of(".") - start_pos;
  return path.substr(start_pos, num_chars);
}

int main(int argc, char*argv[]) {

  if(argc < 2){
    printf("Usage: ./project3 <input file>\n");
    return 0;
  }
  std::string filename = ExtractFilenameFromPath(argv[1]);

  SatSolver solver(argv[1]);
  solver.Part1(filename + "_part1.txt");
  solver.Part2(filename + "_part2.txt");
  solver.Part3(filename + "_part3.txt");

  return 0;
}
