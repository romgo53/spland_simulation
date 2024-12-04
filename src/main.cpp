#include "Simulation.h"
#include "Action.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Simulation *backup = nullptr;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }

    string configurationFile = argv[1];
    Simulation simulation(configurationFile);

    simulation.start(); // Start the simulation

    // string command;
    // while (true)
    // {
    //     cout << "> ";
    //     getline(cin, command);

    //     if (command == "close")
    //     {
    //         BaseAction *close = new Close();
    //         simulation.addAction(close);
    //         close->act(simulation);
    //         delete close;
    //         break;
    //     }

    //     istringstream commandStream(command);
    //     string action;
    //     commandStream >> action;

    //     try
    //     {
    //         if (action == "plan")
    //         {
    //             string settlementName, policyName;
    //             commandStream >> settlementName >> policyName;
    //             BaseAction *addPlan = new AddPlan(settlementName, policyName);
    //             simulation.addAction(addPlan);
    //             addPlan->act(simulation);
    //             delete addPlan;
    //         }
    //         else if (action == "settlement")
    //         {
    //             string settlementName;
    //             int settlementType;
    //             commandStream >> settlementName >> settlementType;
    //             SettlementType type = static_cast<SettlementType>(settlementType);
    //             BaseAction *addSettlement = new AddSettlement(settlementName, type);
    //             simulation.addAction(addSettlement);
    //             addSettlement->act(simulation);
    //             delete addSettlement;
    //         }
    //         else if (action == "changePolicy")
    //         {
    //             int planId;
    //             string newPolicy;
    //             commandStream >> planId >> newPolicy;
    //             BaseAction *changePolicy = new ChangePlanPolicy(planId, newPolicy);
    //             simulation.addAction(changePolicy);
    //             changePolicy->act(simulation);
    //             delete changePolicy;
    //         }

    //         else if (action == "step")
    //         {
    //             int steps;
    //             commandStream >> steps;
    //             BaseAction *simulateStep = new SimulateStep(steps);
    //             simulation.addAction(simulateStep);
    //             simulateStep->act(simulation);
    //             delete simulateStep;
    //         }
    //         else if (action == "log")
    //         {
    //             BaseAction *printLog = new PrintActionsLog();
    //             simulation.addAction(printLog);
    //             printLog->act(simulation);
    //             delete printLog;
    //         }
    //         else if (action == "planStatus")
    //         {
    //             int planId = -1;
    //             commandStream >> planId;
    //             cout << planId << endl;
    //             BaseAction *printStatus = new PrintPlanStatus(planId);
    //             simulation.addAction(printStatus);
    //             printStatus->act(simulation);
    //             delete printStatus;
    //         }
    //         else if (action == "backup")
    //         {
    //             BaseAction *backupAction = new BackupSimulation();
    //             simulation.addAction(backupAction);
    //             backupAction->act(simulation);
    //             delete backupAction;
    //         }
    //         else if (action == "restore")
    //         {
    //             BaseAction *restoreAction = new RestoreSimulation();
    //             simulation.addAction(restoreAction);
    //             restoreAction->act(simulation);
    //             delete restoreAction;
    //         }
    //         else
    //         {
    //             cout << "Invalid command!" << endl;
    //         }
    //     }
    //     catch (const exception &e)
    //     {
    //         cout << "Error: " << e.what() << endl;
    //     }
    // }

    if (backup != nullptr)
    {
        delete backup;
        backup = nullptr;
    }

    return 0;
}
