#include "Settlement.h"
#include <iostream>

int main(int argc, char **argv)
{
    Settlement *settlement = new Settlement("Village1", SettlementType::VILLAGE);
    std::cout << settlement->toString() << std::endl;
    return 0;
};
