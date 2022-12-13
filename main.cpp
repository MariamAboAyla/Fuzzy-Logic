#include <iostream>
#include "FuzzyLogicSystem.h"
#include "FuzzyLogicSystem.cpp"
#include "Simulation.h"
#include "Simulation.cpp"
using namespace std;


/*
 * This function is used to read any
 * variable, so that we could change reading from terminal
 * to be read from file or anywhere else
 */
template <class T>
extern void read(T* memoryAllocated)
{
    /// todo not used yet
    cin >> memoryAllocated;
}

void mainMenu()
{
    FuzzyLogicSystem fuzzyLogicSystem;

    cout<<"Enter the system's name and a brief description:\n"
          "------------------------------------------------\n";

    string systemName;
    cin >> systemName;

    string next;
    cin >> next;
    string description = "";
    description += next;

    while( next[ next.size()-1] != '.')
    {
        cin >> next;
        description+=next;
    }


    string choice;

    while (true) {

        cout << "Main Menu:\n"
                "==========\n"
                "1- Add variables.\n"
                "2- Add fuzzy sets to an existing variable.\n"
                "3- Add rules.\n"
                "4- Run the simulation on crisp values.\n";

        cin >> choice;
        if (choice == "1") {
            fuzzyLogicSystem.addVariables();
        } else if (choice == "2") {
            fuzzyLogicSystem.addFuzzySets();
        } else if (choice == "3") {
            fuzzyLogicSystem.addRules();
        } else if (choice == "4") {
            fuzzyLogicSystem.runSimulationOnCrisp();
        } else if (choice == "Close" || choice == "close") {
            break;
        } else {
            cout << "Error => no such choice exists!\n";
        }

    }

}

void fuzzyLogicToolBox()
{
    int choice;
    while(true)
    {
        cout<<"Fuzzy Logic Toolbox\n"
              <<"===================\n"
              <<"1- Create a new fuzzy system\n"
              <<"2- Quit\n";
        cin >> choice;
        if(choice == 1)
            mainMenu();
        else
            break;
    }
}

int main() {

    fuzzyLogicToolBox();

    return 0;
}
