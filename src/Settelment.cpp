#include "Settlement.h"

Settlement::Settlement(const string &name, SettlementType type)
    : name(name), type(type) {}

const string &Settlement::getName() const
{
    return name;
}

SettlementType Settlement::getType() const
{
    return type;
}
int Settlement::getConstructionLimit() const
{
    switch (type)
    {
    case SettlementType::VILLAGE:
        return 1;
    case SettlementType::CITY:
        return 2;
    case SettlementType::METROPOLIS:
        return 3;
    default:
        return 0;
    }
}

const string Settlement::getTypename(SettlementType type) const
{
    switch (type)
    {
    case SettlementType::VILLAGE:
        return "Village";
    case SettlementType::CITY:
        return "City";
    case SettlementType::METROPOLIS:
        return "Metropolis";

        break;

    default:
        break;
    }
}
const string Settlement::toString() const
{
    return "SettlementName: " + name;
}
