//
// Created by Mariam Khaled on 12/13/2022.
//

#include "FuzzyLogicSystem.h"
#include "Simulation.h"
#include "Simulation.cpp"

/*
 * This function is used to add variables in the database
 * 2 types of variables each in a different array for its type:
 *    ( IN and OUT )
 */
void FuzzyLogicSystem:: addVariables()
{

    cout<<"Enter the variable's name, type (IN/OUT) and range ([lower, upper]):\n"
          "(Press x to finish)\n"
          "--------------------------------------------------------------------\n";

    string next;
    while(true) {
        // this loop is for getting the lines of variables data until user press-> x

        cin >> next;

        if (next == "x")
            break;

        string variableName = next; // saves the variable name
        string word; // for reading
        char nextCh = ' '; // for reading
        // to determine variable type (in, out), and (error) for error indication
        bool in = false, out = false, error = false;
        long double start = -1, end = -1; // to determine start and end ranges

        next = "";
        getline(cin, next);
        long double cnt = 1; // means now expected: IN or OUT
        for(int i =0;  i < (int)next.size(); i++)
        {
            if(next[i] == ' ')
            {
                if(word.empty()) continue;

                if(cnt == 1)
                {
                    if(word == "IN")
                        in  = true;
                    else if (word == "OUT")
                        out = true;
                    else error = true;
                    cnt++; // now expected '['

                }else if (cnt == 2)
                {
                    int siz = lower_bound(word.begin(), word.end(), ',') - lower_bound(word.begin(), word.end(), '[');

                    word = word.substr(1, siz-1);

                    start = stoi(word);

                    word = "";

                    //nextCh = next[i++]; // the space between common and upper range
                    i++;

                    while(i < (int)next.size())
                    {
                        nextCh = next[i++];
                        if(nextCh == ']')
                            break;
                        word+=nextCh;
                    }
                    end = stoi(word);
                    break;

                }
                word = "";

            }else
                word+=next[i];


        }


        // check boundaries error
        if (end < start || start == -1 || end == -1)
        {
            cout<<"Error: Wrong boundaries! Re-check the ranges! \n";
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
                variableNames.insert({variableName, 1});
            }else if (out && !in)
            {
                variablesOut.push_back( variableData );
                variableNames.insert({variableName, 2});
            }else
            {
                cout << "Error: each variable should be IN or OUT! can't be both!\n";
            }
        }else{
            cout<<"Error: Invalid Input!\n";
        }


    }

}



/*
 * This function is used for adding fuzzy sets to existing
 * variables
 */
void FuzzyLogicSystem:: addFuzzySets()
{
    cout << "Enter the variable’s name:\n"
            "--------------------------\n";

    string variableName;
    cin >> variableName;

    auto it = variableNames.find(variableName);
    if (it == variableNames.end())
    {
        cout << "Error: No such a variable name exists!\n";
        return;
    }

    cout << "Enter the fuzzy set name, type (TRI/TRAP) and values: (Press x to finish)\n"
            "-----------------------------------------------------\n";

    while(true)
    {
        string next;
        cin >> next;
        if (next == "x")
            break;

        string setName = next;
        next = "";

        string type;
        cin >> type;

        vector<long double> fuzzySetValues;
        long double first, second, third, fourth;
        if( type == "TRI")
        {
            cin >> first >> second >> third;
            if(second < first || third < first || third < second)
            {
                cout << "Error: Invalid values! Re-insert the input!\n";
                continue;
            }

            fuzzySetValues.emplace_back(first);
            fuzzySetValues.emplace_back(second);
            fuzzySetValues.emplace_back(third);


        }else if ( type == "TRAP")
        {
            cin >> first >> second >> third >> fourth;
            if(fourth < first || fourth < second || fourth < third || second < first || third < first || third < second)
            {
                cout << "Error: Invalid values! Re-insert the input!\n";
                continue;
            }

            fuzzySetValues.emplace_back(first);
            fuzzySetValues.emplace_back(second);
            fuzzySetValues.emplace_back(third);
            fuzzySetValues.emplace_back(fourth);

        }else
        {
            cout << "Error: Wrong type! Write valid input!\n";
            continue;
        }


        FuzzySetData fuzzySetData(setName, type, fuzzySetValues);
        fuzzySet[variableName].push_back( fuzzySetData ); // add this fuzzy set to that variable


    }


}

/*
 * function that checks whether the rules are written
 * in a correct way or not
 */
bool isValidRule(vector<pair<string,string>>& input, vector<pair<string,string>>& output, vector<string>operation)
{
    if (input.empty() || output.empty()) {
        cout << "Error: invalid rule! check input, output and a valid operator!\n";
        return false;
    }

    return true;
}


/*
 * function used to get the output variables of the rule
 */
void getOutputVariable(Rules* rulesList)
{
    string variableName;
    cin >> variableName;

    string setValue;
    cin >> setValue;

    rulesList->output.emplace_back(variableName, setValue);
    string op;
    while (true)
    {
        cin >> op;
        if (op == "\n" || op == "\r" || op == "\r\n")
            break;

        cin >> variableName;
        cin >>  setValue;

        rulesList->output.emplace_back(variableName, setValue);

    }


}


/*
 * Function that add the rules to the database/ inference system
 */
void FuzzyLogicSystem:: addRules()
{

    cout<<"Enter the rules in this format: (Press x to finish)\n"
          "IN_variable set operator IN_variable set => OUT_variable set\n"
          "------------------------------------------------------------\n";


    while(true)
    {
        // each iteration gets a single rule

        string variableName;
        cin >> variableName;
        if(variableName == "x")
            break;

        string setName;
        cin >> setName;

        string op;
        cin >> op;

        Rules rulesList;
        rulesList.input.emplace_back(variableName, setName);

        if(op == "=>")
        {

            // read output then break
            getOutputVariable(&rulesList);

        }else
        {
            // means more inputs and operations
            rulesList.operation.push_back(op);

            while(op != "=>")
            {
                cin >> variableName;
                cin >> setName;
                rulesList.input.emplace_back(variableName, setName);

                cin >> op;
                if(op == "=>")
                    break;

                rulesList.operation.push_back(op);

            }

            getOutputVariable(&rulesList); // get the output variables of the rule

        }


        // check on possible errors
        if(!isValidRule(rulesList.input, rulesList.output, rulesList.operation))
            continue;


        /// todo: check whether it is mandatory to handle or not
        if(variableNames.find(variableName) == variableNames.end())
        {
            cout<<"warning: this variable name doesn't exists!\n";
        }

        rules.emplace_back(rulesList.input, rulesList.output, rulesList.operation); // add the rule to the rule base

    }

}



/*
 * To call the function runSimulation from the simulation class
 * to make the steps of fuzzification till get the required result
 */
void FuzzyLogicSystem:: runSimulationOnCrisp()
{
//    Simulation simulation;
//    simulation.runSimulation();
}

