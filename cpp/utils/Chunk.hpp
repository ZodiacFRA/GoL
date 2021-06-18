#pragma once

#include <vector>


class Chunk {
public:
    Chunk (int idx, int chunkSize);
    virtual ~Chunk () {};

    int _idx;
    int _chunkSize;
    std::vector<bool> _tiles;
};
