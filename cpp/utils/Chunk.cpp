#include "Chunk.hpp"

Chunk::Chunk(int idx, int chunkSize)
    : _idx(idx), _chunkSize(chunkSize), _tiles(chunkSize*chunkSize, false)
{}
