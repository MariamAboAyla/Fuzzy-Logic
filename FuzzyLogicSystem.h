//
// Created by Mariam Khaled on 12/13/2022.
//

#ifndef SOLUTION_FUZZYLOGICSYSTEM_H
#define SOLUTION_FUZZYLOGICSYSTEM_H
#include <iostream>
#include <vector>
using namespace std;

struct Rules
{
    // Input


    // Output


};

struct Variable
{
    string name;
    int start;
    int end;
};

class FuzzyLogicSystem {

public:
    string name;
    string description;
    vector<Variable> variablesIn;
    vector<Variable> variablesOut;
    vector<Rules> rules;

    void addVariables();
    void addFuzzySets();
    void addRules();
    void runSimulationOnCrisp();

};


#endif //SOLUTION_FUZZYLOGICSYSTEM_H
