#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Facility.h"
#include "Auxiliary.h"
#include "Plan.h"
#include "SelectionPolicy.h"
#include "Settlement.h"
#include "Action.h"
using std::stoi;
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation
{
public:
    Simulation(const string &configFilePath);
    Simulation(const Simulation &other);
    Simulation &operator=(const Simulation &other);
    ~Simulation();
    void start();
    void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy);
    void addAction(BaseAction *action);
    bool isPlanExists(int planID);
    bool addSettlement(Settlement *settlement);
    bool addFacility(FacilityType facility);
    void printPlansStatuses() const;
    bool isSettlementExists(const string &settlementName);
    Settlement *getSettlement(const string &settlementName);
    Plan &getPlan(const int planID);
    void step();
    void close();
    void open();
    void printActionLog() const;
    void printSummary() const;

private:
    bool isRunning;
    int planCounter; // For assigning unique plan IDs
    vector<BaseAction *> actionsLog;
    vector<Plan> plans;
    vector<Settlement *> settlements;
    vector<FacilityType> facilitiesOptions;
    void readConfigFile(const string &configFilePath);
    void readPlanConfig(string settName, string policyName);
    bool isFacilityExists(const string &facilityName);
    void executeCommand(std::istringstream &commandStream, const string &action);
};
