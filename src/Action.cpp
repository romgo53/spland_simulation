
#include "Action.h"

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
void AddPlan::act(Simulation &simulation) {}
const string AddPlan::toString() const { return ""; }
AddPlan *AddPlan::clone() const { return new AddPlan(*this); }

// AddSettlement
AddSettlement::AddSettlement(const string &settlementName, SettlementType settlementType)
    : settlementName(settlementName), settlementType(settlementType) {}
void AddSettlement::act(Simulation &simulation) {}
AddSettlement *AddSettlement::clone() const { return new AddSettlement(*this); }
const string AddSettlement::toString() const { return ""; }

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
    Plan &plan = simulation.getPlan(planId);
    plan.printStatus();
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
void ChangePlanPolicy::act(Simulation &simulation) {}
ChangePlanPolicy *ChangePlanPolicy::clone() const { return new ChangePlanPolicy(*this); }
const string ChangePlanPolicy::toString() const { return ""; }

// PrintActionsLog
PrintActionsLog::PrintActionsLog() {}
void PrintActionsLog::act(Simulation &simulation) {}
PrintActionsLog *PrintActionsLog::clone() const { return new PrintActionsLog(*this); }
const string PrintActionsLog::toString() const { return ""; }

// Close
Close::Close() {}
void Close::act(Simulation &simulation) {}
Close *Close::clone() const { return new Close(*this); }
const string Close::toString() const { return ""; }

// BackupSimulation
BackupSimulation::BackupSimulation() {}
void BackupSimulation::act(Simulation &simulation) {}
BackupSimulation *BackupSimulation::clone() const { return new BackupSimulation(*this); }
const string BackupSimulation::toString() const { return ""; }

// RestoreSimulation
RestoreSimulation::RestoreSimulation() {}
void RestoreSimulation::act(Simulation &simulation) {}
RestoreSimulation *RestoreSimulation::clone() const { return new RestoreSimulation(*this); }
const string RestoreSimulation::toString() const { return ""; }
