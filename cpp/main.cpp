#include "Core/Core.hpp"
#include "conf.hpp"


int main(int ac, char **av)
{
    // B3 S23
    // Take rules and add 1 to survive
    std::vector<int> born = { 3, 7 };
    std::vector<int> survive = { 4 };

    Core core = Core(born, survive);
    while (core.run());
    core._screen.close();
    return 0;
}
