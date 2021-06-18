#include "Core.hpp"
#include "../conf.hpp"


// mapSize and chunkSize are in Chunk units
Core::Core(int mapWidth, int mapHeight, int chunkSize)
    : _mapTilesWidth(mapWidth * CHUNK_SIZE), _mapTilesHeight(mapHeight * CHUNK_SIZE),
    _chunkSize(chunkSize), _totalChunksNumber((mapHeight / chunkSize) * (mapWidth / chunkSize)),
    _is_paused(false)
{
    for (int i = 0 ; i < _totalChunksNumber ; i++) {
        _chunksMap.push_back(Chunk(i, chunkSize));
    }
    _screen.create(
        sf::VideoMode(_mapTilesWidth * TILE_SIZE, _mapTilesHeight * TILE_SIZE, 32),
        "Game of Life",
        sf::Style::Titlebar | sf::Style::Close
    );
    _screen.setFramerateLimit(30);
    _screen.setKeyRepeatEnabled(false);
    // Center the window on the screen
    auto desktop = sf::VideoMode::getDesktopMode();
    _screen.setPosition(sf::Vector2i(
        desktop.width/2 - _screen.getSize().x/2,
        desktop.height/2 - _screen.getSize().y/2
    ));
    // Init grid VertexArray for drawing
    initGrid();
}

int Core::run()
{
    while (_screen.isOpen()) {
        handleInputs();
        draw();
    }
    return 0;
}

void Core::draw() {
    _screen.clear(sf::Color::Black);
    // Draw grid
    for (auto line: _grid)
        _screen.draw(line);
    _screen.display();
}
