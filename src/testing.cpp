#include <iostream>
#include <cassert>
#include "Simulation.h"
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include "Action.h"

void testProject() {
    Simulation simulation("");

    Settlement *settlement1 = new Settlement("Jerusalem", SettlementType::CITY);
    Settlement *settlement2 = new Settlement("Haifa", SettlementType::VILLAGE);
    assert(simulation.addSettlement(settlement1));
    assert(simulation.addSettlement(settlement2));
    assert(simulation.isSettlementExists("Jerusalem"));
    assert(simulation.isSettlementExists("Haifa"));

    FacilityType school("School", FacilityCategory::LIFE_QUALITY, 200, 3, 2, 1);
    FacilityType hospital("Hospital", FacilityCategory::ECONOMY, 500, 5, 3, 2);
    assert(simulation.addFacility(school));
    assert(simulation.addFacility(hospital));
   

    SelectionPolicy *policy1 = new EconomySelection();
    SelectionPolicy *policy2 = new SustainabilitySelection();
    simulation.addPlan(*settlement1, policy1);
    simulation.addPlan(*settlement2, policy2);
    assert(simulation.isPlanExists(0));
    assert(simulation.isPlanExists(1));

    ChangePlanPolicy changePolicyAction(0, "bal");
    changePolicyAction.act(simulation);
    assert(simulation.getPlan(0).toString().find("BalancedSelection") != std::string::npos);

    simulation.step();
    simulation.printPlansStatuses();

    vector<BaseAction *> actionLog = simulation.getActionLog();
    assert(!actionLog.empty());

    simulation.close();
    std::cout << "Simulation successfully closed." << std::endl;

    const Plan &plan1 = simulation.getPlan(0);
    assert(!plan1.getFacilities().empty());
    std::cout << "Plan 0 facilities after simulation step: " << plan1.getFacilities().size() << std::endl;

    delete settlement1;
    delete settlement2;

    std::cout << "All tests passed successfully!" << std::endl;
}

int main() {
    try {
        testProject();
    } catch (const std::exception &e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with an unknown exception." << std::endl;
        return 1;
    }
    return 0;
}


