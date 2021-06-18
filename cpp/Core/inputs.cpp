#include "Core.hpp"

std::ostream& operator<< (std::ostream &out, sf::Vector2i const& pos) {
    return out << "x:" << pos.x << " y:" << pos.y;
}

int Core::refreshMousePosition()
{
    // Get global mouse position in tiles
    _globalMousePos = sf::Mouse::getPosition(_screen) / TILE_SIZE;
    if (_globalMousePos.x < 0
        || _globalMousePos.y < 0
        || _globalMousePos.x > _mapTilesWidth
        || _globalMousePos.y > _mapTilesHeight
    ) {
        return false;
    }
    return true;
}

void Core::handleInputs()
{
    // Handle window events
    static sf::Event event;
    while (_screen.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _screen.close();
    }
    // Handle keyboard events
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        _is_paused = !_is_paused;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12))
        takeScreenshot();
    // Handle mouse events
    if (!refreshMousePosition())  // If mouse is out of bounds
        return;
    // Get the mouse position in the tiles chunk indexes
    sf::Vector2i cursorChunkIdx = {
        _globalMousePos.x / CHUNK_SIZE,
        _globalMousePos.y / CHUNK_SIZE
    };
    sf::Vector2i cursorTileIdx = {
        _globalMousePos.x % CHUNK_SIZE,
        _globalMousePos.y % CHUNK_SIZE
    };
    _mousePos[0] = CHUNK_SIZE * (cursorChunkIdx.y) + cursorChunkIdx.x;
    // _mousePos[0] = getIndexFromPos(cursorChunkIdx, CHUNK_SIZE);
    _mousePos[1] = (CHUNK_SIZE * cursorTileIdx.y) + cursorTileIdx.x;

    // Tiles drawing
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        std::cout << "-------------" << '\n';
        std::cout << "chunkPos: " << cursorChunkIdx << " tilePos: " << cursorTileIdx << '\n';
        std::cout << "chunkIdx: " << _mousePos[0] << " tileIdx: " << _mousePos[1] << '\n';
        setTileValue(_mousePos, true);
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        setTileValue(_mousePos, false);
    }
}
