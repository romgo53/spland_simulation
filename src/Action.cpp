
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
void AddPlan::act(Simulation &simulation) {
    if (!simulation.isSettlementExists(settlementName)) {
        error("Cannot create this plan: settlement does not exist.");
        return;
    }

    SelectionPolicy *policy = nullptr;
    if (selectionPolicy == "nve") {
        policy = new NaiveSelection();
    } else if (selectionPolicy == "bal") {
        policy = new BalancedSelection(0, 0, 0);
    } else if (selectionPolicy == "eco") {
        policy = new EconomySelection();
    } else if (selectionPolicy == "env") {
        policy = new SustainabilitySelection();
    } else {
        error("Cannot create this plan: invalid selection policy.");
        return;
    }

    try {
        Settlement* settlement = simulation.getSettlement(settlementName);
        simulation.addPlan(*settlement, policy);
        complete();
    } catch (const std::exception &e) {
        error("Cannot create this plan: " + string(e.what()));
        delete policy;
    }
}

const string AddPlan::toString() const {
    return "AddPlan: SettlementName = " + settlementName + ", SelectionPolicy = " + selectionPolicy;
}

AddPlan *AddPlan::clone() const { return new AddPlan(*this); }

// AddSettlement


AddSettlement::AddSettlement(const string &settlementName, SettlementType settlementType) 
    : settlementName(settlementName), settlementType(settlementType) {}

void AddSettlement::act(Simulation &simulation) {
    if (simulation.isSettlementExists(settlementName)) {
        error("Settlement already exists");
        return;
    }
    
    Settlement *newSettlement = new Settlement(settlementName, settlementType);
    
    try {
        if (simulation.addSettlement(newSettlement)) {
            complete();
        } else {
            error("Failed to add settlement");
            delete newSettlement;
        }
    } catch (const std::exception &e) {
        error("Failed to add settlement: " + string(e.what()));
        delete newSettlement;
    }
}


AddSettlement *AddSettlement::clone() const {
    return new AddSettlement(*this);
}

const string AddSettlement::toString() const {
    return "AddSettlement: " + settlementName + " (" + 
           (settlementType == SettlementType::VILLAGE ? "Village" :
           settlementType == SettlementType::CITY ? "City" : "Metropolis") + ")";
}


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

