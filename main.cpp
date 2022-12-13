#include <iostream>
#include "FuzzyLogicSystem.h"

using namespace std;


void mainMenu()
{
    FuzzyLogicSystem fuzzyLogicSystem;

    cout<<"Enter the system’s name and a brief description:\n"
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
    cin >> choice;

    while (true) {

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
