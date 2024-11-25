#include "Plan.h"

// Constructor
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
    : plan_id(planId), settlement(settlement),
      selectionPolicy(selectionPolicy), facilityOptions(facilityOptions),
      status(PlanStatus::AVALIABLE),
      life_quality_score(0), economy_score(0), environment_score(0) {}

// Getters for scores
const int Plan::getlifeQualityScore() const
{
    return life_quality_score; // Placeholder
}

const int Plan::getEconomyScore() const
{
    return economy_score; // Placeholder
}

const int Plan::getEnvironmentScore() const
{
    return environment_score; // Placeholder
}

// Set selection policy
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy)
{
    this->selectionPolicy = selectionPolicy; // Placeholder
}

// Step function
void Plan::step()
{
    // Placeholder implementation
}

// Print status
void Plan::printStatus()
{
    // Placeholder implementation
}

// Get facilities
const vector<Facility *> &Plan::getFacilities() const
{
    return facilities; // Placeholder
}

// Add a facility
void Plan::addFacility(Facility *facility)
{
    facilities.push_back(facility); // Placeholder
}

// Convert to string
const string Plan::toString() const
{
    return ""; // Placeholder
}
