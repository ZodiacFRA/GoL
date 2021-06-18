#include "Core/Core.hpp"
#include "conf.hpp"


int main() {
    Core core = Core();
    while (core.run());
    core._screen.close();
    return 0;
}
