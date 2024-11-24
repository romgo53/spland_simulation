
#include "Action.h"

// BaseAction
BaseAction::BaseAction() {}
ActionStatus BaseAction::getStatus() const { return ActionStatus::ERROR; }
void BaseAction::complete() {}
void BaseAction::error(string errorMsg) {}
const string &BaseAction::getErrorMsg() const { return errorMsg; }

// SimulateStep
SimulateStep::SimulateStep(const int numOfSteps) : numOfSteps(numOfSteps) {}
void SimulateStep::act(Simulation &simulation) {}
const string SimulateStep::toString() const { return ""; }
SimulateStep *SimulateStep::clone() const { return new SimulateStep(*this); }

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
void AddFacility::act(Simulation &simulation) {}
AddFacility *AddFacility::clone() const { return new AddFacility(*this); }
const string AddFacility::toString() const { return ""; }

// PrintPlanStatus
PrintPlanStatus::PrintPlanStatus(int planId) : planId(planId) {}
void PrintPlanStatus::act(Simulation &simulation) {}
PrintPlanStatus *PrintPlanStatus::clone() const { return new PrintPlanStatus(*this); }
const string PrintPlanStatus::toString() const { return ""; }

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

