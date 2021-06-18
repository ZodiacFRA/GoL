#include "Core.hpp"

std::ostream& operator<< (std::ostream &out, sf::Vector2i const& pos) {
    return out << "x:" << pos.x << " y:" << pos.y;
}

int Core::refreshMousePosition()
{
    // Get global mouse position in tiles
    _mousePos = sf::Mouse::getPosition(_screen) / TILE_SIZE;
    return isValidPos(_mousePos.x, _mousePos.y);
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        _is_paused = !_is_paused;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12))
        takeScreenshot();
    // Handle mouse events
    if (!refreshMousePosition())  // If mouse is out of bounds
        return;
    // Tiles drawing
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        setTileValue(_mousePos.x, _mousePos.y, true);
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        setTileValue(_mousePos.x, _mousePos.y, false);
    }
}
