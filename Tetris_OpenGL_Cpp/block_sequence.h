#ifndef BLOCKSEQUENCE_H
#define BLOCKSEQUENCE_H
#include "tetris_enums.h"
#include <tuple>
#include <vector>
class BlockSequence
{
public:
    std::vector< std::tuple <int, int> > created_sequence;
    BlockSequence(blockType blockname, rotationType rotation);
    std::vector<std::tuple <int, int> > getSequence();
};

#endif
