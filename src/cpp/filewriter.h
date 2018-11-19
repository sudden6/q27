#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "action.h"
#include "Symmetry.hpp"
#include <iostream>
#include <fstream>

class FileWriter : public Action {
  uint64_t pre[4];
  std::ofstream files[4];
  // safe until N=28
  uint8_t data[22] = {0};

public:
  FileWriter(unsigned N);
  ~FileWriter() {}

public:
  void process(queens::Board const &brd, queens::Symmetry sym);
  void dump(std::ostream &out) const;
};

#endif // FILEWRITER_H
