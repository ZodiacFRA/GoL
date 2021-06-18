#include "Core.hpp"
#include "../conf.hpp"


Core::Core()
    : _mapTilesWidth(MAP_WIDTH), _mapTilesHeight(MAP_HEIGHT), _is_paused(true),
    _rect(sf::Vector2f(TILE_SIZE, TILE_SIZE))
{
    _screen.create(
        sf::VideoMode(_mapTilesWidth * TILE_SIZE, _mapTilesHeight * TILE_SIZE, 32),
        "Game of Life",
        sf::Style::Titlebar | sf::Style::Close
    );
    _screen.setFramerateLimit(120);
    _screen.setKeyRepeatEnabled(false);
    // Center the window on the screen
    auto desktop = sf::VideoMode::getDesktopMode();
    _screen.setPosition(sf::Vector2i(
        desktop.width/2 - _screen.getSize().x/2,
        desktop.height/2 - _screen.getSize().y/2
    ));
    initMap();
    initGrid();  // Init grid VertexArray for drawing
}

int Core::run()
{
    while (_screen.isOpen()) {
        handleInputs();
        if (!_is_paused)
            updateMap();
        draw();
    }
    return 0;
}

void Core::updateMap()
{
    // TODO: Multithread by column
    // _map will only be read
    // _tmpMap will only be written to
    for (int xIdx = 0 ; xIdx < MAP_WIDTH ; xIdx++)
        updateColumn(xIdx);
    // when all threads are done, switch _tmpMap and _map
    // As we rewrite every tile value, previous values do not matter
    for (int xIdx = 0 ; xIdx < MAP_WIDTH ; xIdx++)
        _map[xIdx] = _tmpMap[xIdx];
}

void Core::updateColumn(int xIdx)
{
    for (int yIdx = 0 ; yIdx < MAP_HEIGHT ; yIdx++) {
        int aliveNeighborsCount = getAliveNeighborsCount(xIdx, yIdx);
        if (aliveNeighborsCount == 3)  // Alive
            _tmpMap[xIdx][yIdx] = true;
        else if (aliveNeighborsCount == 4)  // Do nothing
            _tmpMap[xIdx][yIdx] = _map[xIdx][yIdx];
        else  // Dead
            _tmpMap[xIdx][yIdx] = false;
    }
}

int Core::getAliveNeighborsCount(int xIdx, int yIdx)
{
    // OOB neighbors count as dead
    int count = 0;
    for (int tmpX = xIdx - 1 ; tmpX < xIdx + 2 ; tmpX++) {
        for (int tmpY = yIdx - 1 ; tmpY < yIdx + 2 ; tmpY++) {
            if (isValidPos(tmpX, tmpY) && _map[tmpX][tmpY])
                count++;
        }
    }
    return count;
}

bool Core::isValidPos(int xIdx, int yIdx)
{
    if (xIdx < 0 || yIdx < 0 || xIdx > _mapTilesWidth || yIdx > _mapTilesHeight)
        return false;
    return true;
}

void Core::draw() {
    _screen.clear(sf::Color::Black);
    // Draw map
    for (int xIdx = 0 ; xIdx < MAP_WIDTH ; xIdx++) {
        for (int yIdx = 0 ; yIdx < MAP_HEIGHT ; yIdx++) {
            if (_map[xIdx][yIdx])
                _rect.setFillColor(sf::Color::White);
            else
                _rect.setFillColor(sf::Color::Black);
            _rect.setPosition(xIdx * TILE_SIZE, yIdx * TILE_SIZE);
            _screen.draw(_rect);
        }
    }
    // Draw grid
    for (auto line: _grid) {
        _screen.draw(line);
    }
    _screen.display();
}

void Core::setTileValue(int xIdx, int yIdx, bool value)
{
    _map[xIdx][yIdx] = value;
}
