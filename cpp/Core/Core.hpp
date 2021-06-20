#pragma once

#include <thread>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "../conf.hpp"
#include "../Perlin/PerlinNoise.hpp"


class Core {
    public:
        Core (std::vector<int> ruleBorn, std::vector<int> ruleSurvive);
        virtual ~Core () {};

        int run();
    private:
        int refreshMousePosition();
        void handleInputs();
        void draw();
        void takeScreenshot();
        void initGrid();
        void initMap();
        void setTileValue(int xIdx, int yIdx, bool value);
        void updateMap();
        void updateColumn(int xIdx);
        int getAliveNeighborsCount(int xIdx, int yIdx);
        bool isValidPos(int xIdx, int yIdx);
        void printMap();
        void updateColumnRange(int xIdxStart, int xIdxEnd);
    public:
        sf::RenderWindow _screen;
    private:
        // Rules
        std::vector<int> _ruleBorn;
        std::vector<int> _ruleSurvive;
        // Display
        std::vector<sf::VertexArray> _grid;
        sf::RectangleShape _rect;

        int _mapTilesWidth;
        int _mapTilesHeight;

        sf::Vector2i _mousePos;
        bool _is_paused;
        double _last_pause_change;

        std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _map;
        std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _tmpMap;

        siv::PerlinNoise _perlin;
};
