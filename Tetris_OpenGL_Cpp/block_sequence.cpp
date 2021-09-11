#include "block_sequence.h"

BlockSequence::BlockSequence(blockType blockname, rotationType rotation) {
    if (blockname == Lshaped) {
        if (rotation == Up_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(0, -1);
            std::tuple<int, int> order3 = std::tuple< int, int >(0, 1);
            std::tuple<int, int> order4 = std::tuple< int, int >(1, 1);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
        else if (rotation == Right_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(0, -1);
            std::tuple<int, int> order3 = std::tuple< int, int >(1, -1);
            std::tuple<int, int> order4 = std::tuple< int, int >(2, -1);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
        else if (rotation == Down_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, -1);
            std::tuple<int, int> order2 = std::tuple< int, int >(1, -1);
            std::tuple<int, int> order3 = std::tuple< int, int >(1, 0);
            std::tuple<int, int> order4 = std::tuple< int, int >(1, 1);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
        else if (rotation == Left_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(1, -1);
            std::tuple<int, int> order3 = std::tuple< int, int >(1, 0);
            std::tuple<int, int> order4 = std::tuple< int, int >(-1, 0);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
    }
    else if (blockname == Oshaped) {
        std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
        std::tuple<int, int> order2 = std::tuple< int, int >(0, -1);
        std::tuple<int, int> order3 = std::tuple< int, int >(1, 0);
        std::tuple<int, int> order4 = std::tuple< int, int >(1, -1);
        this->created_sequence.push_back(order1);
        this->created_sequence.push_back(order2);
        this->created_sequence.push_back(order3);
        this->created_sequence.push_back(order4);
    }
    else if (blockname == Ishaped) {
        if (rotation == Up_rotation || rotation == Down_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(0, 1);
            std::tuple<int, int> order3 = std::tuple< int, int >(0, -1);
            std::tuple<int, int> order4 = std::tuple< int, int >(0, -2);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
        else if (rotation == Left_rotation || rotation == Right_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(-1, 0);
            std::tuple<int, int> order3 = std::tuple< int, int >(-2, 0);
            std::tuple<int, int> order4 = std::tuple< int, int >(1, 0);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
    }
    else if (blockname == Jshaped) {
        if (rotation == Up_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(0, -1);
            std::tuple<int, int> order3 = std::tuple< int, int >(0, 1);
            std::tuple<int, int> order4 = std::tuple< int, int >(-1, 1);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
        else if (rotation == Right_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(0, 1);
            std::tuple<int, int> order3 = std::tuple< int, int >(1, 1);
            std::tuple<int, int> order4 = std::tuple< int, int >(2, 1);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
        else if (rotation == Down_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(1, 0);
            std::tuple<int, int> order3 = std::tuple< int, int >(0, 1);
            std::tuple<int, int> order4 = std::tuple< int, int >(0, 2);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
        else if (rotation == Left_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(-1, 0);
            std::tuple<int, int> order3 = std::tuple< int, int >(1, 0);
            std::tuple<int, int> order4 = std::tuple< int, int >(1, 1);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
    }
    else if (blockname == Zshaped) {
        if (rotation == Up_rotation || rotation == Down_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(1, 0);
            std::tuple<int, int> order3 = std::tuple< int, int >(0, -1);
            std::tuple<int, int> order4 = std::tuple< int, int >(-1, -1);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
        else if (rotation == Right_rotation || rotation == Left_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(0, 1);
            std::tuple<int, int> order3 = std::tuple< int, int >(1, 0);
            std::tuple<int, int> order4 = std::tuple< int, int >(1, -1);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
    }
    else if (blockname == Sshaped) {
        if (rotation == Up_rotation || rotation == Down_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(-1, 0);
            std::tuple<int, int> order3 = std::tuple< int, int >(0, -1);
            std::tuple<int, int> order4 = std::tuple< int, int >(1, -1);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
        else if (rotation == Right_rotation || rotation == Left_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(0, 1);
            std::tuple<int, int> order3 = std::tuple< int, int >(-1, 0);
            std::tuple<int, int> order4 = std::tuple< int, int >(-1, -1);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
    }
    else if (blockname == Tshaped) {
        if (rotation == Up_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(-1, 0);
            std::tuple<int, int> order3 = std::tuple< int, int >(1, 0);
            std::tuple<int, int> order4 = std::tuple< int, int >(0, -1);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
        else if (rotation == Right_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(0, -1);
            std::tuple<int, int> order3 = std::tuple< int, int >(0, 1);
            std::tuple<int, int> order4 = std::tuple< int, int >(1, 0);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
        else if (rotation == Down_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(1, 0);
            std::tuple<int, int> order3 = std::tuple< int, int >(-1, 0);
            std::tuple<int, int> order4 = std::tuple< int, int >(0, 1);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
        else if (rotation == Left_rotation) {
            std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
            std::tuple<int, int> order2 = std::tuple< int, int >(0, 1);
            std::tuple<int, int> order3 = std::tuple< int, int >(0, -1);
            std::tuple<int, int> order4 = std::tuple< int, int >(-1, 0);
            this->created_sequence.push_back(order1);
            this->created_sequence.push_back(order2);
            this->created_sequence.push_back(order3);
            this->created_sequence.push_back(order4);
        }
    }
    else {
        std::tuple<int, int> order1 = std::tuple< int, int >(0, 0);
        std::tuple<int, int> order2 = std::tuple< int, int >(0, 0);
        std::tuple<int, int> order3 = std::tuple< int, int >(0, 0);
        std::tuple<int, int> order4 = std::tuple< int, int >(0, 0);
        this->created_sequence.push_back(order1);
        this->created_sequence.push_back(order2);
        this->created_sequence.push_back(order3);
        this->created_sequence.push_back(order4);
    }
}

std::vector<std::tuple <int, int> > BlockSequence::getSequence() {
    return this->created_sequence;
}

