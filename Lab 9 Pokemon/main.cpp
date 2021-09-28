#include <string>
#include "Set.h"
#include "Map.h"
#include <ostream>
#include <fstream>
#include <sstream>
using namespace std;


//battle function here, print lots of stuff with strings
std::string battle(std::string pokemon1, std::string pokemon1Attack, std::string pokemon2, std::string pokemon2Attack,
        HashMap<string, string> pokemonMap, HashMap<string, string> movesMap, HashMap<string, Set<string>> effectiveMap,
        HashMap<string, Set<string>> ineffectiveMap) {

    std::string strToReturn;
    strToReturn += pokemon1 + " (" + pokemon1Attack + ") vs " + pokemon2 +  " (" + pokemon2Attack + ")\n";
    strToReturn += pokemon1 +" is a " + pokemonMap.getPair(pokemon1) + " type Pokemon.\n";
    strToReturn += pokemon2 + " is a " + pokemonMap.getPair(pokemon2) + " type Pokemon.\n";
    strToReturn += pokemon1Attack + " is a " + movesMap.getPair(pokemon1Attack) + " type move.\n";
    strToReturn += pokemon2Attack + " is a " + movesMap.getPair(pokemon2Attack) + " type move.\n";

    //get winner function here, compute damages
    int damage1To2 = 0;
    int damage2To1 = 0;

    damage1To2 = effectiveMap.getSet(movesMap.getPair(pokemon1Attack)).count(pokemonMap.getPair(pokemon2))
                 - ineffectiveMap.getSet(movesMap.getPair(pokemon1Attack)).count(pokemonMap.getPair(pokemon2));
    damage2To1 = effectiveMap.getSet(movesMap.getPair(pokemon2Attack)).count(pokemonMap.getPair(pokemon1))
                 - ineffectiveMap.getSet(movesMap.getPair(pokemon2Attack)).count(pokemonMap.getPair(pokemon1));

    strToReturn += pokemon1Attack + " is super effective against [" + effectiveMap.getPair(movesMap.getPair(pokemon1Attack))
                   + "] type Pokemon.\n";
    strToReturn += pokemon1Attack + " is ineffective against [" + ineffectiveMap.getPair(movesMap.getPair(pokemon1Attack))
                   + "] type Pokemon.\n";
    if (damage1To2 == 0) {
        strToReturn += pokemon1 + "'s " + pokemon1Attack + " is effective against " + pokemon2 + "\n";
    }
    if (damage1To2 == 1) {
        strToReturn += pokemon1 + "'s " + pokemon1Attack + " is super effective against " + pokemon2 + "\n";
    }
    if (damage1To2 == -1) {
        strToReturn += pokemon1 + "'s " + pokemon1Attack + " is ineffective against " + pokemon2 + "\n";
    }

    //repeat for pokemon2
    strToReturn += pokemon2Attack + " is super effective against [" + effectiveMap.getPair(movesMap.getPair(pokemon2Attack))
                   + "] type Pokemon.\n";
    strToReturn += pokemon2Attack + " is ineffective against [" + ineffectiveMap.getPair(movesMap.getPair(pokemon2Attack))
                   + "] type Pokemon.\n";
    if (damage2To1 == 0) {
        strToReturn += pokemon2 + "'s " + pokemon2Attack + " is effective against " + pokemon1 + "\n";
    }
    if (damage2To1 == 1) {
        strToReturn += pokemon2 + "'s " + pokemon2Attack + " is super effective against " + pokemon1 + "\n";
    }
    if (damage2To1 == -1) {
        strToReturn += pokemon2 + "'s " + pokemon2Attack + " is ineffective against " + pokemon1 + "\n";
    }

    if ((damage1To2 - damage2To1) > 0) {//Pokemon1 Wins!
        strToReturn += "In the battle between " + pokemon1 + " and " + pokemon2 + ", " + pokemon1 +" wins!\n";
    }
    else if ((damage1To2 - damage2To1) < 0) { //Pokemon2 Wins!
        strToReturn += "In the battle between " + pokemon1 + " and " + pokemon2 + ", " + pokemon2 +" wins!\n";
    }
    else { //Tie!
        strToReturn += "The battle between " + pokemon1 + " and " + pokemon2 + " is a tie.\n";
    }
    return strToReturn;
}


int main(int argc, char* argv[]) {

    ifstream in(argv[1]);
    ofstream out;
    out.open(argv[2]);

    //initialize all sets and hashmaps necessary
    Set<string> mySet;
    HashMap<string, string> pokemonMap;
    HashMap<string, string> movesMap;
    HashMap<string, Set<string>> effectiveMap;
    HashMap<string, Set<string>> ineffectiveMap;

    for (string inputLine; getline(in, inputLine, '\n');) {
        string userCommand, inputText;
        if (inputLine.size() == 0) continue;
        istringstream iss(inputLine);
        if (!inputLine.empty() && inputLine[inputLine.size() - 1] == '\r') {
            inputLine.erase(inputLine.size() - 1);
        }
        string setMember = "";
        string command = "";
        iss >> command;

        if (command == "Set:") {
            out << inputLine;
            inputLine.erase(0, 5);
            do {
                iss >> setMember;
                if (isspace(setMember[setMember.size()])) {
                    setMember = setMember.substr(0, setMember.size() - 1);
                }
                mySet.insert(setMember);
                inputLine.erase(0, setMember.size() + 1);

            } while (inputLine.size() != 0);
            out << endl << "[" << mySet.toString() << "]" << endl;
            mySet.clear();
        }
        if (command == "Pokemon:") {
            out << inputLine << endl;
            string pokemonMember = "";
            string pokemonType = "";
            iss >> pokemonMember;
            iss >> pokemonType;
            if (!pokemonMap.isPresent(pokemonMember)) {
                pokemonMap[pokemonMember] = pokemonType;
            }
        }
        if (command == "Move:") {
            out << inputLine << endl;
            string pokemonMove = "";
            string moveType = "";
            iss >> pokemonMove;
            iss >> moveType;
            if (!movesMap.isPresent(pokemonMove)) {
                movesMap[pokemonMove] = moveType;
            }
        }
        if (command == "Effective:") {
            out << inputLine << endl;
            string moveType = "";
            Set<string> effectiveAgainst;
            iss >> moveType;
            string setMember;
            while (iss >> setMember) {
                effectiveAgainst.insert(setMember);
            }
            if (!effectiveMap.isPresent(moveType)) {
                effectiveMap[moveType] = effectiveAgainst;
            }
        }
        if (command == "Ineffective:") {
            out << inputLine << endl;
            string moveType = "";
            Set<string> ineffectiveAgainst;
            iss >> moveType;
            string setMember;
            while (iss >> setMember) {
                ineffectiveAgainst.insert(setMember);
            }
            if (!ineffectiveMap.isPresent(moveType)) {
                ineffectiveMap[moveType] = ineffectiveAgainst;
            }
        }


        if (command == "Pokemon") {
            out << endl <<  "Pokemon: " << pokemonMap.toString();
        }
        if (command == "Moves") {
            out << endl <<  "Moves: " << movesMap.toString();
        }
        if (command == "Effectivities") {
            out << endl <<  "Effectivities: " << effectiveMap.toString();
        }
        if (command == "Ineffectivities") {
            out << endl <<  "Ineffectivities: " << ineffectiveMap.toString();
        }
        if (command == "Battle:") {
            out << endl << inputLine << endl;
            string pokemon1 = "";
            string pokemon1Attack = "";
            string pokemon2 = "";
            string pokemon2Attack = "";
            iss >> pokemon1;
            iss >> pokemon1Attack;
            iss >> pokemon2;
            iss >> pokemon2Attack;
            out << battle(pokemon1, pokemon1Attack, pokemon2, pokemon2Attack, pokemonMap, movesMap, effectiveMap, ineffectiveMap);
        }
    }

    //clear all data structures to avoid memory leaks
    pokemonMap.clear();
    movesMap.clear();
    effectiveMap.clear();
    ineffectiveMap.clear();
    return 0;
}
