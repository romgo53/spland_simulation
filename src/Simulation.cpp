#include "Simulation.h"
#include "Action.h"
#include "SelectionPolicy.h"

// Constructor
Simulation::Simulation(const string &configFilePath)
    : isRunning(false), planCounter(0)
{
    // TODO: Implement loading configuration from the file
}

// Start the simulation
void Simulation::start()
{
    isRunning = true; // Placeholder for starting logic
}

// Add a new plan
void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy)
{
    // TODO: Implement adding a plan
}

// Add an action to the log
void Simulation::addAction(BaseAction *action)
{
    actionsLog.push_back(action); // Placeholder for adding an action
}

// Add a new settlement
bool Simulation::addSettlement(Settlement *settlement)
{
    settlements.push_back(settlement); // Placeholder for adding a settlement
    return true;
}

// Add a new facility
bool Simulation::addFacility(FacilityType facility)
{
    facilitiesOptions.push_back(facility); // Placeholder for adding a facility
    return true;
}

// Check if a settlement exists
bool Simulation::isSettlementExists(const string &settlementName)
{
    for (const auto &settlement : settlements)
    {
        if (settlement->getName() == settlementName)
        {
            return true;
        }
    }
    return false;
}

// Get a plan by ID
Plan &Simulation::getPlan(const int planID)
{
    for (auto &plan : plans)
    {
        if (planID == plan.getlifeQualityScore())
        { // Placeholder condition
            return plan;
        }
    }
}

// Perform a simulation step
void Simulation::step()
{
    // TODO: Implement simulation step
}

// Close the simulation
void Simulation::close()
{
    isRunning = false; // Placeholder for close logic
}

// Open the simulation
void Simulation::open()
{
    isRunning = true; // Placeholder for open logic
}
