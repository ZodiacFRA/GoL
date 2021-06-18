#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "../utils/Chunk.hpp"
#include "../conf.hpp"


class Core {
    public:
        Core (int mapWidth, int mapHeight, int chunkSize);
        virtual ~Core () {};

        int run();
    private:
        int refreshMousePosition();
        void handleInputs();
        void draw();
        void takeScreenshot();
        void setTileValue(std::array<int, 2> indexes, bool value) {
            std::cout << _chunksMap.size() << '\n';
            std::cout << CHUNK_SIZE * CHUNK_SIZE << '\n';
            std::cout << "replacing " << indexes[0] << " " << indexes[1] << " with " << value << '\n';
            std::cout << _chunksMap[indexes[0]]._tiles.size() << '\n';
            _chunksMap[indexes[0]]._tiles[indexes[1]] = value;
        }
        bool getTileValue(std::array<int, 2> indexes) {
            return _chunksMap[indexes[0]]._tiles[indexes[1]];
        }

        int getIndexFromPos(sf::Vector2i p, int w) { return (w * p.y) + p.x; }
        sf::Vector2i getPosFromIdx(int i, int w) { return sf::Vector2i(i % w, i / w); }

        void initGrid();

    public:
        sf::RenderWindow _screen;
    private:
        // In pixels
        int _mapTilesWidth;
        int _mapTilesHeight;

        sf::RenderTexture _rawGameTexture;
        // In tiles, without accounting for chunks
        sf::Vector2i _globalMousePos;
        // In game coordinates (chunk + tiles)
        std::array<int, 2> _mousePos;

        // In Chunks
        int _mapChunkWidth;
        int _mapChunkHeight;
        int _chunkSize;
        int _totalChunksNumber;
        std::vector<Chunk> _chunksMap;

        bool _is_paused;

        // Grid
        std::vector<sf::VertexArray> _grid;

};
