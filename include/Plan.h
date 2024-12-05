#pragma once
#include <vector>
#include <iostream>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::cout;
using std::endl;
using std::vector;

enum class PlanStatus
{
    AVALIABLE,
    BUSY,
};
class Plan
{
public:
    Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);
    Plan(const Plan &other);
    Plan(Plan &&other) noexcept;
    ~Plan();
    Plan &operator=(const Plan &other);
    Plan &operator=(Plan &&other) noexcept;
    const int getlifeQualityScore() const;
    const int getEconomyScore() const;
    const int getEnvironmentScore() const;
    void setSelectionPolicy(SelectionPolicy *selectionPolicy);
    void step();
    const int getPlanId() const;
    void printStatus() const;
    const vector<Facility *> &getFacilities() const;
    void addFacility(Facility *facility);
    const string toString() const;

private:
    int plan_id;
    const Settlement &settlement;
    SelectionPolicy *selectionPolicy; // What happens if we change this to a reference?
    PlanStatus status;
    vector<Facility *> facilities;
    vector<Facility *> underConstruction;
    const vector<FacilityType> &facilityOptions;
    int life_quality_score;
    int economy_score;
    int environment_score;
};