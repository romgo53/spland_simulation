#include "Simulation.h"
// Constructor

Simulation::Simulation(const string &configFilePath)
    : isRunning(false), planCounter(0), actionsLog(), plans(), settlements(), facilitiesOptions()
{
    readConfigFile(configFilePath);
}
// Copy constructor
Simulation::Simulation(const Simulation &other)
    : isRunning(other.isRunning), planCounter(other.planCounter), actionsLog(), plans(), settlements(), facilitiesOptions()
{
    for (const auto *settlement : other.settlements)
    {
        settlements.push_back(new Settlement(*settlement));
    }
    for (const auto &facility : other.facilitiesOptions)
    {
        facilitiesOptions.push_back(facility);
    }
    for (auto plan : other.plans)
    {
        for (const auto *settlement : settlements)
        {
            if (settlement->getName() == plan.getSettlement().getName())
            {
                plans.push_back(Plan(std::move(plan), *settlement));
                break;
            }
        }
    }
    for (const auto *action : other.actionsLog)
    {
        actionsLog.push_back(action->clone());
    }
}
// Assignment operator
Simulation &Simulation::operator=(const Simulation &other)
{
    if (this != &other)
    {
        isRunning = other.isRunning;
        planCounter = other.planCounter;
        vector<Settlement *> tempSettlements = settlements;
        for (auto *action : actionsLog)
        {
            delete action;
        }
        settlements.clear();
        actionsLog.clear();
        facilitiesOptions.clear();
        plans.clear();
        for (const auto *settlement : other.settlements)
        {
            settlements.push_back(new Settlement(*settlement));
        }
        for (const auto &facility : other.facilitiesOptions)
        {
            facilitiesOptions.push_back(facility);
        }
        for (auto plan : other.plans)
        {
            for (const auto *settlement : settlements)
            {
                if (settlement->getName() == plan.getSettlement().getName())
                {
                    plans.push_back(Plan(std::move(plan), *settlement));
                    break;
                }
            };
        }
        for (const auto *action : other.actionsLog)
        {
            actionsLog.push_back(action->clone());
        }
        for (auto *settlement : tempSettlements)
        {
            delete settlement;
        }
        for (auto plan : plans)
        {
        }
    }
    return *this;
}
// Destructor
Simulation::~Simulation()
{
    for (auto *settlement : settlements)
    {
        delete settlement;
    }
    for (auto *action : actionsLog)
    {
        delete action;
    }
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
    file.close();
}

// Read the plan configuration
void Simulation::readPlanConfig(string settName, string policyName)
{
    Settlement *settlement = getSettlement(settName);
    SelectionPolicy *policy = nullptr;
    if (policyName == "nve")
    {
        policy = new NaiveSelection();
    }
    else if (policyName == "bal")
    {
        policy = new BalancedSelection(0, 0, 0);
    }
    else if (policyName == "eco")
    {
        policy = new EconomySelection();
    }
    else if (policyName == "env")
    {
        policy = new SustainabilitySelection();
    }
    else
    {
        delete policy;
        return;
    }

    addPlan(*settlement, policy);
}
// execute a command
void Simulation::executeCommand(std::istringstream &commandStream, const string &action)
{
    if (action == "close")
    {
        BaseAction *close = new Close();
        addAction(close);
        close->act(*this);
    }
    else if (action == "step")
    {
        int steps;
        commandStream >> steps;
        BaseAction *step = new SimulateStep(steps);
        addAction(step);
        step->act(*this);
    }
    else if (action == "log")
    {
        BaseAction *printLog = new PrintActionsLog();
        addAction(printLog);
        printLog->act(*this);
    }
    else if (action == "plan")
    {
        string settlementName, policyName;
        commandStream >> settlementName >> policyName;
        BaseAction *addPlan = new AddPlan(settlementName, policyName);
        addAction(addPlan);
        addPlan->act(*this);
    }
    else if (action == "settlement")
    {
        string settlementName;
        int settlementType;
        commandStream >> settlementName >> settlementType;
        SettlementType type = static_cast<SettlementType>(settlementType);
        BaseAction *addSettlement = new AddSettlement(settlementName, type);
        addAction(addSettlement);
        addSettlement->act(*this);
    }
    else if (action == "changePolicy")
    {
        int planId = -1;
        string newPolicy;
        commandStream >> planId >> newPolicy;
        BaseAction *changePolicy = new ChangePlanPolicy(planId, newPolicy);
        addAction(changePolicy);
        changePolicy->act(*this);
    }
    else if (action == "planStatus")
    {
        int planId = -1;
        commandStream >> planId;
        BaseAction *printPlan = new PrintPlanStatus(planId);
        addAction(printPlan);
        printPlan->act(*this);
    }
    else if (action == "facility")
    {
        string facilityName;
        int facilityCategory, price, lifeQualityScore, economyScore, environmentScore;
        commandStream >> facilityName >> facilityCategory >> price >> lifeQualityScore >> economyScore >> environmentScore;
        BaseAction *addFacility = new AddFacility(facilityName, FacilityCategory(facilityCategory), price, lifeQualityScore, economyScore, environmentScore);
        addAction(addFacility);
        addFacility->act(*this);
    }
    else if (action == "backup")
    {
        BaseAction *backup = new BackupSimulation();
        addAction(backup);
        backup->act(*this);
    }
    else if (action == "restore")
    {
        BaseAction *restore = new RestoreSimulation();
        restore->act(*this);
        addAction(restore);
    }
    else
    {
        cout << "Invalid command!" << endl;
    }
}
// Start the simulation??
void Simulation::start()
{
    isRunning = true;
    while (isRunning)
    {
        string command;
        cout << "> ";
        std::getline(std::cin, command);
        std::istringstream commandStream(command);
        string action;
        commandStream >> action;
        executeCommand(commandStream, action);
    }
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
    delete selectionPolicy;
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
    throw "Plan does not exist";
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
void Simulation::printActionLog() const
{
    for (auto *action : actionsLog)
    {
        std::cout << action->toString() << std::endl;
    }
}

void Simulation::printPlansStatuses() const
{
    for (const auto &plan : plans)
    {
        plan.printStatus();
    }
}
