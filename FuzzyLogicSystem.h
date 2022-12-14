//
// Created by Mariam Khaled on 12/13/2022.
//

#ifndef SOLUTION_FUZZYLOGICSYSTEM_H
#define SOLUTION_FUZZYLOGICSYSTEM_H
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Rules
{

    // Input
    vector<pair<string, string>> input;

    // Output
    vector<pair<string, string>> output;

    // operator
    vector<string> operation;

    Rules() {}
    Rules(vector<pair<string, string>>& i, vector<pair<string, string>>& o, vector<string>& op)
    :input(i), output(o), operation(op){}

};

struct FuzzySetData
{

    string variableName;
    string type;
    vector<long double> fuzzySetValues;

    FuzzySetData(string& vName, string& vType, vector<long double>& fuzzSet){
        variableName = vName;
        type = vType;
        fuzzySetValues = fuzzSet;
    }


};

struct Variable
{
    string name;
    long double start;
    long double end;
};

class FuzzyLogicSystem {

public:
    string name;
    string description;
    map<string, long double> variableNames; // variable name => maps to its type: IN or OUT
    vector<Variable> variablesIn;
    vector<Variable> variablesOut;
    map<string, vector<FuzzySetData>> fuzzySet;
    vector<Rules> rules;

    void addVariables();
    void addFuzzySets();
    void addRules();
    void runSimulationOnCrisp();

};


#endif //SOLUTION_FUZZYLOGICSYSTEM_H
