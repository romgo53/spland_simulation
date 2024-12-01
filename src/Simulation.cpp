#include "Simulation.h"
// TODO: figure out how to implament start, open, close
// Constructor

Simulation::Simulation(const string &configFilePath)
    : isRunning(false), planCounter(0)
{
    readConfigFile(configFilePath);
}

// Read the configuration file
void Simulation::readConfigFile(const string &configFilePath)
{
    std::ifstream file;
    file.open(configFilePath);
    string line;
    while (std::getline(file, line))
    {
        vector<string> arguments = Auxiliary::parseArguments(line);
        if (arguments[0] == "settlement")
        {
            const string &name = arguments[1];
            if (isSettlementExists(name))
            {
                // TODO: throw error?
            }
            addSettlement(new Settlement(name, SettlementType(stoi(arguments[2]))));
        }
        else if (arguments[0] == "facility")
        {
            const string &name = arguments[1];

            addFacility(FacilityType(name, FacilityCategory(stoi(arguments[2])), stoi(arguments[3]), stoi(arguments[4]), stoi(arguments[5]), stoi(arguments[6])));
        }
        else if (arguments[0] == "plan")
        {
            readPlanConfig(arguments[1], arguments[2]);
        }
    }
}

// Read the plan configuration
void Simulation::readPlanConfig(string settName, string policyName)
{
    Settlement *settlement = getSettlement(settName);
    SelectionPolicy *selectionPolicy;
    if (policyName == "nve")
    {
        selectionPolicy = new NaiveSelection();
    }
    else if (policyName == "bal")
    {
        selectionPolicy = new BalancedSelection(0, 0, 0);
    }
    else if (policyName == "eco")
    {
        selectionPolicy = new EconomySelection();
    }
    else if (policyName == "env")
    {
        selectionPolicy = new SustainabilitySelection();
    }
    else
    {
        // TODO: throw error?
    }
    addPlan(*settlement, selectionPolicy);
}

// Start the simulation??
void Simulation::start()
{
    isRunning = true;
}
// get a settlement by name
Settlement *Simulation::getSettlement(const string &settlementName)
{
    for (auto settlement : settlements)
    {
        if (settlement->getName() == settlementName)
        {
            return settlement;
        }
    }
    return nullptr;
}
// Add a new plan
void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy)
{
    plans.push_back(Plan(planCounter++, settlement, selectionPolicy, facilitiesOptions));
}

void Simulation::addAction(BaseAction *action)
{
    actionsLog.push_back(action);
}

// Add a new settlement
bool Simulation::addSettlement(Settlement *settlement)
{
    settlements.push_back(settlement);
    return true;
}

bool Simulation::isFacilityExists(const string &facilityName)
{
    for (const auto &facility : facilitiesOptions)
    {
        if (facility.getName() == facilityName)
        {
            return true;
        }
    }
    return false;
}

// Add a new facility
bool Simulation::addFacility(FacilityType facility)
{
    if (isFacilityExists(facility.getName()))
    {
        return false;
    }
    facilitiesOptions.push_back(facility);
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

// Check if a plan exists
bool Simulation::isPlanExists(int planID)
{
    for (const auto &plan : plans)
    {
        if (plan.getPlanId() == planID)
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
        if (planID == plan.getPlanId())
        {
            return plan;
        }
    }
}

// Perform a simulation step
void Simulation::step()
{
    for (Plan &plan : plans)
    {
        plan.step();
    }
}
// Close what? maybe it should call the destructor?
void Simulation::close()
{
    isRunning = false;
}

// Open the simulation??? maybe open backup?
void Simulation::open()
{
    isRunning = true;
}
