#include "Core.hpp"
#include "../conf.hpp"


Core::Core()
    : _mapTilesWidth(MAP_WIDTH), _mapTilesHeight(MAP_HEIGHT), _is_paused(false),
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
        draw();
    }
    return 0;
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
    for (auto line: _grid)
        _screen.draw(line);
    _screen.display();
}

void Core::setTileValue(sf::Vector2i pos, bool value)
{
    _map[pos.x][pos.y] = value;
}
