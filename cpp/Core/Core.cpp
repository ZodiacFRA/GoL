#include "Core.hpp"
#include "../conf.hpp"


Core::Core(std::vector<int> ruleBorn, std::vector<int> ruleSurvive)
    : _ruleBorn(ruleBorn), _ruleSurvive(ruleSurvive),
    _mapTilesWidth(MAP_WIDTH), _mapTilesHeight(MAP_HEIGHT), _is_paused(true),
    _rect(sf::Vector2f(TILE_SIZE, TILE_SIZE)), _perlin(RANDOM_SEED)
{
    _screen.create(
        sf::VideoMode(_mapTilesWidth * TILE_SIZE, _mapTilesHeight * TILE_SIZE, 32),
        "Game of Life",
        sf::Style::Titlebar | sf::Style::Close
    );
    _screen.setFramerateLimit(1000);
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
    int count = 0;
    while (_screen.isOpen()) {
        handleInputs();
        if (!_is_paused) {
            updateMap();
            count++;
        }
        draw();
        // if (count == 25)
        //     break;
    }
    return 0;
}

void Core::updateMap()
{
    int blockSize = MAP_WIDTH / 4;
    std::vector<std::thread> tmp;
    // Multithread by column
    // Give each thread {blockSize} columns to process
    // _map will only be read
    // _tmpMap will only be written to
    for (int xIdx = 0 ; xIdx < MAP_WIDTH ; xIdx += blockSize)
        tmp.push_back(std::thread(&Core::updateColumnRange, this, xIdx, xIdx + blockSize));
    for (int i = 0 ; i < tmp.size() ; i++)
        tmp[i].join();
    // when all threads are done, switch _tmpMap and _map
    // As we rewrite every tile value, previous values do not matter
    for (int xIdx = 0 ; xIdx < MAP_WIDTH ; xIdx++)
        _map[xIdx] = _tmpMap[xIdx];
}

void Core::updateColumnRange(int xIdxStart, int xIdxEnd)
{
    for (int xIdx = xIdxStart ; xIdx < xIdxEnd ; xIdx++)
        updateColumn(xIdx);
}

void Core::updateColumn(int xIdx)
{
    for (int yIdx = 0 ; yIdx < MAP_HEIGHT ; yIdx++) {
        int aliveNeighborsCount = getAliveNeighborsCount(xIdx, yIdx);
        if (std::count(_ruleBorn.begin(), _ruleBorn.end(), aliveNeighborsCount))
            _tmpMap[xIdx][yIdx] = true;
        else if (std::count(_ruleSurvive.begin(), _ruleSurvive.end(), aliveNeighborsCount))  // Do nothing
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

void Core::draw()
{
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
