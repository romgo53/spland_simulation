#include "Plan.h"
#include <iostream>
using std::cout;
using std::endl;
// Constructor
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
    : plan_id(planId),
      settlement(settlement),
      selectionPolicy(selectionPolicy ? selectionPolicy->clone() : nullptr),
      status(PlanStatus::AVALIABLE),
      facilityOptions(facilityOptions),
      life_quality_score(0),
      economy_score(0),
      environment_score(0),
      facilities(),
      underConstruction() {}

Plan::Plan(const Plan &other)
    : plan_id(other.plan_id), 
      settlement(other.settlement), 
      selectionPolicy(other.selectionPolicy ? other.selectionPolicy->clone() : nullptr),
      facilityOptions(other.facilityOptions),
      life_quality_score(other.life_quality_score),
      economy_score(other.economy_score),
      environment_score(other.environment_score),
      status(other.status) {
    for (Facility* facility : other.facilities) {
        facilities.push_back(new Facility(*facility)); 
    }
    for (Facility* facility : other.underConstruction) {
        underConstruction.push_back(new Facility(*facility)); 
    }
}

Plan& Plan::operator=(const Plan &other) {
    if (this == &other) {
        return *this; 
    }
    delete selectionPolicy;
    for (Facility* facility : facilities) {
        delete facility;
    }
    for (Facility* facility : underConstruction) {
        delete facility;
    }

    plan_id = other.plan_id;
    selectionPolicy = other.selectionPolicy ? other.selectionPolicy->clone() : nullptr;
    life_quality_score = other.life_quality_score;
    economy_score = other.economy_score;
    environment_score = other.environment_score;
    status = other.status;

    for (Facility* facility : other.facilities) {
        facilities.push_back(new Facility(*facility));
    }
    for (Facility* facility : other.underConstruction) {
        underConstruction.push_back(new Facility(*facility));}

    return *this;
}

//destructor
Plan::~Plan() {
    delete selectionPolicy;
}


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
void Plan::step() {
    if (status == PlanStatus::AVALIABLE) {
        int constructionLimit = settlement.getConstructionLimit();
        while (underConstruction.size() < constructionLimit) {
            const FacilityType& nextFacility = selectionPolicy->selectFacility(facilityOptions);
            Facility* facility = new Facility(nextFacility, settlement.getName());
            underConstruction.push_back(facility);
        }
    }

    for (auto it = underConstruction.begin(); it != underConstruction.end();) {
        (*it)->step();
        if ((*it)->getStatus() == FacilityStatus::OPERATIONAL) {
            facilities.push_back(*it);
            it = underConstruction.erase(it);
        } else {
            ++it;
        }
    }

    if (underConstruction.size() == settlement.getConstructionLimit()) {
        status = PlanStatus::BUSY;
    } else {
        status = PlanStatus::AVALIABLE;
    }
}


// Print status
void Plan::printStatus()
{
    std::cout << "PlanID: " << plan_id << std::endl;
    std::cout << "SettlementName: " << settlement.getName() << std::endl;
    std::cout << "PlanStatus: " << (status == PlanStatus::AVALIABLE ? "AVAILABLE" : "BUSY") << std::endl;
    std::cout << "SelectionPolicy: " << selectionPolicy->toString() << std::endl;
    std::cout << "LifeQualityScore: " << life_quality_score << std::endl;
    std::cout << "EconomyScore: " << economy_score << std::endl;
    std::cout << "EnvironmentScore: " << environment_score << std::endl;

    std::cout << "Facilities under construction:" << std::endl;
    for (const Facility* facility : underConstruction)
    {
        std::cout << "FacilityName: " << facility->getName() << std::endl;
        std::cout << "FacilityStatus: " << (facility->getStatus() == FacilityStatus::UNDER_CONSTRUCTIONS ? "UNDER_CONSTRUCTIONS" : "OPERATIONAL") << std::endl;
    }

    std::cout << "Operational facilities:" << std::endl;
    for (const Facility* facility : facilities)
    {
        std::cout << "FacilityName: " << facility->getName() << std::endl;
        std::cout << "FacilityStatus: " << (facility->getStatus() == FacilityStatus::UNDER_CONSTRUCTIONS ? "UNDER_CONSTRUCTIONS" : "OPERATIONAL") << std::endl;
    }
}


// Get facilities
const vector<Facility *> &Plan::getFacilities() const
{
    return facilities; // Placeholder
}

// Add a facility
void Plan::addFacility(Facility *facility)
{
    facilities.push_back(facility); 
}

const string Plan::toString() const {
    string result = "PlanID: " + std::to_string(plan_id) + "\n";
    result += "SettlementName: " + settlement.getName() + "\n";
    result += "PlanStatus: " + std::string(status == PlanStatus::AVALIABLE ? "AVAILABLE" : "BUSY") + "\n";
    result += "SelectionPolicy: " + (selectionPolicy ? selectionPolicy->toString() : "None") + "\n";
    result += "LifeQualityScore: " + std::to_string(life_quality_score) + "\n";
    result += "EconomyScore: " + std::to_string(economy_score) + "\n";
    result += "EnvironmentScore: " + std::to_string(environment_score) + "\n";

    result += "Facilities:\n";
    for (const Facility* facility : facilities) {
        result += "  FacilityName: " + facility->getName() +
                  ", FacilityStatus: " +
                  (facility->getStatus() == FacilityStatus::UNDER_CONSTRUCTIONS ? "UNDER_CONSTRUCTIONS" : "OPERATIONAL") +
                  "\n";
    }

    result += "Facilities Under Construction:\n";
    for (const Facility* facility : underConstruction) {
        result += "  FacilityName: " + facility->getName() +
                  ", TimeLeft: " + std::to_string(facility->getTimeLeft()) +
                  "\n";
    }

    return result;
}

