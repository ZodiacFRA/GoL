#include "Core/Core.hpp"
#include "conf.hpp"


int main() {
    Core core = Core(MAP_WIDTH, MAP_HEIGHT, CHUNK_SIZE);
    while (core.run());
    core._screen.close();
    return 0;
}
