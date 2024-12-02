
#include "Action.h"
extern Simulation *backup;
// BaseAction
BaseAction::BaseAction() {}
ActionStatus BaseAction::getStatus() const { return status; }
void BaseAction::complete()
{
    status = ActionStatus::COMPLETED;
}
void BaseAction::error(string errorMsg)
{
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;
    std::cout << errorMsg << std::endl;
}
const string &BaseAction::getErrorMsg() const { return errorMsg; }

// SimulateStep
SimulateStep::SimulateStep(const int numOfSteps) : numOfSteps(numOfSteps) {}
void SimulateStep::act(Simulation &simulation)
{
    for (int i = 0; i < numOfSteps; i++)
    {
        simulation.step();
    }
    complete();
}
const string SimulateStep::toString() const
{
    return "SimulateStep " + to_string(numOfSteps) + " COMPLETE";
}
SimulateStep *SimulateStep::clone() const
{
    return new SimulateStep(*this);
}

// AddPlan
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy)
    : settlementName(settlementName), selectionPolicy(selectionPolicy) {}
void AddPlan::act(Simulation &simulation)
{
    if (!simulation.isSettlementExists(settlementName))
    {
        error("Cannot create this plan: settlement does not exist.");
        return;
    }

    SelectionPolicy *policy = nullptr;
    if (selectionPolicy == "nve")
    {
        policy = new NaiveSelection();
    }
    else if (selectionPolicy == "bal")
    {
        policy = new BalancedSelection(0, 0, 0);
    }
    else if (selectionPolicy == "eco")
    {
        policy = new EconomySelection();
    }
    else if (selectionPolicy == "env")
    {
        policy = new SustainabilitySelection();
    }
    else
    {
        error("Cannot create this plan: invalid selection policy.");
        return;
    }

    simulation.addPlan(*simulation.getSettlement(settlementName), policy);
    complete();
}

const string AddPlan::toString() const
{
    return "AddPlan: SettlementName = " + settlementName + ", SelectionPolicy = " + selectionPolicy + (getStatus() == ActionStatus::ERROR ? " ERROR" : " COMPLETED");
}

AddPlan *AddPlan::clone() const { return new AddPlan(*this); }

// AddSettlement
AddSettlement::AddSettlement(const string &settlementName, SettlementType settlementType)
    : settlementName(settlementName), settlementType(settlementType) {}

void AddSettlement::act(Simulation &simulation)
{
    if (simulation.isSettlementExists(settlementName))
    {
        error("Settlement already exists");
        return;
    }

    Settlement *newSettlement = new Settlement(settlementName, settlementType);

    if (simulation.addSettlement(newSettlement))
    {
        complete();
    }
    else
    {
        error("Failed to add settlement");
        delete newSettlement;
    }
}

AddSettlement *AddSettlement::clone() const
{
    return new AddSettlement(*this);
}

const string AddSettlement::toString() const
{
    int type = static_cast<int>(settlementType);
    return "AddSettlement: " + settlementName + " " + to_string(type) + (getStatus() == ActionStatus::ERROR ? " ERROR" : " COMPLETED");
}

// AddFacility
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory,
                         const int price, const int lifeQualityScore, const int economyScore, const int environmentScore)
    : facilityName(facilityName), facilityCategory(facilityCategory),
      price(price), lifeQualityScore(lifeQualityScore),
      economyScore(economyScore), environmentScore(environmentScore) {}
void AddFacility::act(Simulation &simulation)
{
    FacilityType facilityType(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);

    bool res = simulation.addFacility(facilityType);
    if (!res)
    {
        error("Facility already exists");
        return;
    }
    else
    {
        complete();
    }
}
AddFacility *AddFacility::clone() const { return new AddFacility(*this); }
const string AddFacility::toString() const
{
    string rtn = "AddFacility " + facilityName + to_string(price) + to_string(lifeQualityScore) + to_string(economyScore) + to_string(environmentScore);

    if (getStatus() == ActionStatus::ERROR)
    {
        return rtn + " ERROR";
    }
    else
    {
        return rtn + " COMPLETED";
    }
}

// PrintPlanStatus
PrintPlanStatus::PrintPlanStatus(int planId) : planId(planId) {}
void PrintPlanStatus::act(Simulation &simulation)
{
    if (!simulation.isPlanExists(planId))
    {
        error("Plan does not exist");
        return;
    }

    (simulation.getPlan(planId)).printStatus();
}
PrintPlanStatus *PrintPlanStatus::clone() const { return new PrintPlanStatus(*this); }
const string PrintPlanStatus::toString() const
{
    if (getStatus() == ActionStatus::ERROR)
    {
        return "PrintPlanStatus " + to_string(planId) + " ERROR";
    }
    else
    {
        return "PrintPlanStatus " + to_string(planId) + " COMPLETED";
    }
}

// ChangePlanPolicy
ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy)
    : planId(planId), newPolicy(newPolicy) {}
void ChangePlanPolicy::act(Simulation &simulation)
{

    SelectionPolicy *policy = nullptr;
    if (newPolicy == "nve")
    {
        policy = new NaiveSelection();
    }
    else if (newPolicy == "bal")
    {
        policy = new BalancedSelection(0, 0, 0); // Adjust scores as needed
    }
    else if (newPolicy == "eco")
    {
        policy = new EconomySelection();
    }
    else if (newPolicy == "env")
    {
        policy = new SustainabilitySelection();
    }
    else
    {
        error("Cannot change selection policy: invalid policy.");
        return;
    }
    (simulation.getPlan(planId)).setSelectionPolicy(policy);
    complete();
}
ChangePlanPolicy *ChangePlanPolicy::clone() const { return new ChangePlanPolicy(*this); }
const string ChangePlanPolicy::toString() const
{
    return "ChangePlanPolicy " + to_string(planId) + " " + newPolicy + (getStatus() == ActionStatus::ERROR ? " ERROR" : " COMPLETED");
}

// PrintActionsLog
PrintActionsLog::PrintActionsLog() {}
void PrintActionsLog::act(Simulation &simulation)
{
    for (auto *action : simulation.getActionLog())
    {
        std::cout << action->toString() << std::endl;
    }
    complete();
}
PrintActionsLog *PrintActionsLog::clone() const { return new PrintActionsLog(*this); }
const string PrintActionsLog::toString() const { return "PrintActionLog COMPLETED"; }

// Close
Close::Close() {}
void Close::act(Simulation &simulation)
{
    simulation.close();
    simulation.printPlansStatuses();
    complete();
}
Close *Close::clone() const { return new Close(*this); }
const string Close::toString() const { return "Close COMPLETED"; }

// BackupSimulation
BackupSimulation::BackupSimulation() {}
void BackupSimulation::act(Simulation &simulation)
{
    backup = new Simulation(simulation);
    complete();
}
BackupSimulation *BackupSimulation::clone() const { return new BackupSimulation(*this); }
const string BackupSimulation::toString() const { return "BackupSimulation COMPLETED"; }

// RestoreSimulation
RestoreSimulation::RestoreSimulation() {}
void RestoreSimulation::act(Simulation &simulation)
{
    if (backup != nullptr)
    {
        simulation = Simulation(*backup);
        complete();
    }
    else
    {
        error("No backup available");
    }
}
RestoreSimulation *RestoreSimulation::clone() const { return new RestoreSimulation(*this); }
const string RestoreSimulation::toString() const
{
    if (getStatus() == ActionStatus::ERROR)
    {
        return getErrorMsg();
    }
    else
    {
        return "RestoreSimulation COMPLETED";
    }
}
