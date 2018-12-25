#include "filewriter.h"

#include <iomanip>
#include <iostream>
#include <string>

FileWriter::FileWriter(unsigned N)
{
    for (queens::Symmetry s : queens::Symmetry::RANGE) {
        std::string name = std::string(s);
        pre[s] = 0;
        files[s].open("N_" + std::to_string(N) + "_" + name + ".dat2",
                      std::ios::binary | std::ios::out | std::ios::trunc);
        if(!files[s].is_open()) {
            std::cout << "Failed to open: " << name << std::endl;
        }
    }
}

void FileWriter::process(queens::Board const &brd, queens::Symmetry sym)
{
    pre[sym]++;

    // safe until N=254, 0xFF means empty
    uint8_t data[8] = {0};
    brd.getPacked(data);

    // check if columns A,B and E,F are occupied
    bool checked = false;

    if(data[0] != 0xFF && data[1] != 0xFF) {
        bool E = false;
        bool F = false;
        for(size_t i = 0; i < 4; i++) {
            if(data[i] == 0) {
                E = true;
            }
            if(data[i] == 1) {
                F = true;
            }
        }

        if(data[4] != 0xFF) {
            E = true;
        }

        if(data[5] != 0xFF) {
            F = true;
        }

        checked = E && F;
    }

    if(!checked) {
        std::cout << "Err" << std::endl;
    }

    files[sym].write((char*)data, 8);

} // process()

void FileWriter::dump(std::ostream &out) const
{
    uint64_t total_pre = 0;

    out << "Symmetry     Seeds";
    out << "\n-----\n";

    for (queens::Symmetry s : queens::Symmetry::RANGE) {
      out << (const char*)s << '\t' << std::right << std::setw(10) << pre[s];
      total_pre += pre[s];
      out << '\n';
    }
    out << "-----\nTOTAL\t" << std::right << std::setw(10) << total_pre;
    out << '\n';
}
