//
// Created by Mariam Khaled on 12/13/2022.
//

#include "FuzzyLogicSystem.h"


void FuzzyLogicSystem:: addVariables()
{

    cout<<"Enter the variable’s name, type (IN/OUT) and range ([lower, upper]):\n"
          "(Press x to finish)\n"
          "--------------------------------------------------------------------\n";

    string next;
    while(true) {
        cin >> next;

        if (next == "x")
            break;

        string variableName = next;
        string word;
        char nextCh = ' ';
        bool in = false, out = false, error = false;
        int start, end;

        while (nextCh != ']') {

            if (error) {
                break;
            }

            cin >> nextCh;
            if (nextCh == ' ') {
                if (!word.empty() && !in && !out) {
                    if (word == "IN")
                        in = true;
                    else if (word == "OUT")
                        out = true;
                    else
                        error = true;
                } else if (nextCh == '[') {
                    word = "";
                    while (true) {
                        cin >> nextCh;
                        if (nextCh == ',')
                            break;

                        word += nextCh;

                    }

                    start = stoi(word);

                    word = "";
                    while (true) {
                        cin >> nextCh;
                        if (nextCh == ']')
                            break;

                        word += nextCh;

                    }

                    end = stoi(word);
                }

                word = "";

            } else {
                word += nextCh;
            }

        }

        // check boundaries error
        if (end < start)
        {
            cout<<"Error: Wrong boundaries! Lower should be smaller value than Upper! \n";
            continue;
        }


        // if not error-> add to variables list
        if(!error)
        {
            Variable variableData;
            variableData.name = variableName;
            variableData.start = start;
            variableData.end = end;

            if(in && !out)
            {
                variablesIn.push_back( variableData );
            }else if (out && !in)
            {
                variablesOut.push_back( variableData );
            }else
            {
                cout << "Error: each variable should be IN or OUT! can't be both!\n";
            }
        }


    }

}

void addFuzzySets();
void addRules();
void runSimulationOnCrisp();