#include "filewriter.h"

#include <iomanip>
#include <iostream>
#include <string>

FileWriter::FileWriter(unsigned N)
{
    for (queens::Symmetry s : queens::Symmetry::RANGE) {
        std::string name = std::string(s);
        pre[s] = 0;
        files[s].open("N_" + std::to_string(N) + "_" + name + ".dat",
                      std::ios::binary | std::ios::out | std::ios::trunc);
        if(!files[s].is_open()) {
            std::cout << "Failed to open: " << name << std::endl;
        }
    }
}

void FileWriter::process(queens::Board const &brd, queens::Symmetry sym)
{
    pre[sym]++;

    // horizontal
    uint64_t h = brd.getBH();
    data[0] = h >> 3*8;
    data[1] = h >> 2*8;
    data[2] = h >> 1*8;
    data[3] = h >> 0*8;

    // vertical
    uint64_t v = brd.getBV();
    data[4] = v >> 3*8;
    data[5] = v >> 2*8;
    data[6] = v >> 1*8;
    data[7] = v >> 0*8;

    // up diagonal, only 7 bytes needed
    uint64_t u = brd.getBU();
    data[8]  = u >> 6*8;
    data[9]  = u >> 5*8;
    data[10] = u >> 4*8;
    data[11] = u >> 3*8;
    data[12] = u >> 2*8;
    data[13] = u >> 1*8;
    data[14] = u >> 0*8;

    // down diagonal, only 7 bytes needed
    uint64_t d = brd.getBD();
    data[15] = d >> 6*8;
    data[16] = d >> 5*8;
    data[17] = d >> 4*8;
    data[18] = d >> 3*8;
    data[19] = d >> 2*8;
    data[20] = d >> 1*8;
    data[21] = d >> 0*8;

    files[sym].write((char*)data, 22);

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
