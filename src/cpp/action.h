#ifndef ACTION_H
#define ACTION_H

#include "Board.hpp"
#include "Symmetry.hpp"

class Action {
protected:
  Action() {}

public:
  virtual ~Action() {}

public:
  virtual void operator()(queens::Board const &brd, queens::Symmetry sym) { this->process(brd, sym); }

public:
  virtual void process(queens::Board const &brd, queens::Symmetry sym) = 0;
  virtual void dump(std::ostream &out) const = 0;
};


#endif // ACTION_H
