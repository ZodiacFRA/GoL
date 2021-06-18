#include "Core.hpp"


void Core::takeScreenshot()
{
    static int screenNb = 0;
    sf::Vector2u windowSize = _screen.getSize();
    sf::Texture texture;
    texture.create(windowSize.x, windowSize.y);
    texture.update(_screen);
    sf::Image screenshot = texture.copyToImage();
    screenshot.saveToFile(std::string("screenshot") + std::to_string(screenNb) +".png");
    screenNb++;
}

void Core::initGrid()
{
    for (int xIdx = 0 ; xIdx < _mapTilesWidth ; xIdx++) {
        sf::VertexArray line(sf::LinesStrip, 2);
        line[0].position = sf::Vector2f(xIdx * TILE_SIZE, 0);
        line[0].color  = sf::Color(50, 50, 50);
        line[1].position = sf::Vector2f(xIdx * TILE_SIZE, _mapTilesHeight * TILE_SIZE);
        line[1].color  = sf::Color(50, 50, 50);
        _grid.push_back(line);
    }
    for (int yIdx = 0 ; yIdx < _mapTilesWidth ; yIdx++) {
        sf::VertexArray line(sf::LinesStrip, 2);
        line[0].position = sf::Vector2f(0, yIdx * TILE_SIZE);
        line[0].color  = sf::Color(50, 50, 50);
        line[1].position = sf::Vector2f(_mapTilesWidth * TILE_SIZE, yIdx * TILE_SIZE);
        line[1].color  = sf::Color(50, 50, 50);
        _grid.push_back(line);
    }
}

void Core::initMap()
{
    for (int xIdx = 0 ; xIdx < MAP_WIDTH ; xIdx++) {
        for (int yIdx = 0 ; yIdx < MAP_HEIGHT ; yIdx++) {
            _map[xIdx][yIdx] = false;
        }
    }
}
