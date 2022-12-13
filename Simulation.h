//
// Created by Zbook on 12/13/2022.
//

#ifndef SOLUTION_SIMULATION_H
#define SOLUTION_SIMULATION_H
#include <iostream>

using namespace std;

class Simulation{
public:

    map<string, long double> crispValues;

    void runSimulation(); // to run the start of simulation

    void fuzzification(); // do fuzzifictaion

    void inferenceRules(); // running rules and getting their consequences

    void defuzzification(); // defuzzifying output

    void printOutput(); // print the output and the data got from the defuzzification
    // each of these functions sequentially calls the next one to them

};


#endif //SOLUTION_SIMULATION_H
