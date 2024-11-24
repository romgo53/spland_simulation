#include "Settlement.h"

// Constructor
Settlement::Settlement(const string &name, SettlementType type) 
    : name(name), type(type) {}

// Get the settlement's name
const string &Settlement::getName() const {
    return name; // Placeholder
}

// Get the settlement's type
SettlementType Settlement::getType() const {
    return type; // Placeholder
}

// Convert to string representation
const string Settlement::toString() const {
    return ""; // Placeholder
}
