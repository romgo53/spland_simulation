#include "SelectionPolicy.h"

// NaiveSelection Constructor
NaiveSelection::NaiveSelection() : lastSelectedIndex(0) {}

// NaiveSelection Methods
const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    // TODO: Implement selection logic
    return facilitiesOptions[lastSelectedIndex]; // Placeholder
}

const string NaiveSelection::toString() const {
    return "NaiveSelection";
}

NaiveSelection* NaiveSelection::clone() const {
    return new NaiveSelection(*this);
}

// BalancedSelection Constructor
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore)
    : LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}

// BalancedSelection Methods
const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    // TODO: Implement selection logic
    return facilitiesOptions[0]; // Placeholder
}

const string BalancedSelection::toString() const {
    return "BalancedSelection";
}

BalancedSelection* BalancedSelection::clone() const {
    return new BalancedSelection(*this);
}

// EconomySelection Constructor
EconomySelection::EconomySelection() : lastSelectedIndex(0) {}

// EconomySelection Methods
const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    // TODO: Implement selection logic
    return facilitiesOptions[lastSelectedIndex]; // Placeholder
}

const string EconomySelection::toString() const {
    return "EconomySelection";
}

EconomySelection* EconomySelection::clone() const {
    return new EconomySelection(*this);
}

// SustainabilitySelection Constructor
SustainabilitySelection::SustainabilitySelection() : lastSelectedIndex(0) {}

// SustainabilitySelection Methods
const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    // TODO: Implement selection logic
    return facilitiesOptions[lastSelectedIndex]; // Placeholder
}

const string SustainabilitySelection::toString() const {
    return "SustainabilitySelection";
}

SustainabilitySelection* SustainabilitySelection::clone() const {
    return new SustainabilitySelection(*this);
}

