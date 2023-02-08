/*
 Author: Michael Mathews
 Project: Wordle Solver
 Description: Need help with your wordle? This will help.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
    char anotherGuess = 'y', anotherWordle = 'y';
    string word, id, fileName = "wordleWords.txt";
    ifstream inputFile;
    vector<string> possibilies;
    inputFile.open(fileName);
    
    //populate possibilies
    if(inputFile){
        while(inputFile >> word){
            possibilies.push_back(word);
        }
    }
    else {
        cerr << "Failed to open file" << endl;
        return 1;
    }
    
    cout << "Welcome to Wordle Solver!" << endl;
    cout << "Enter the word you guessed followed by 5 "
            "corresponding identifiers (example below)" << endl;
    cout << "Identifiers:" << endl;
    cout << "   Enter a \"b\" for a black box" << endl;
    cout << "   Enter a \"g\" for a green green" << endl;
    cout << "   Enter a \"y\" for a yellow box" << endl;
    cout << "Ex. hello 10112" << endl << endl;
    
    while(anotherWordle == 'y'){
        while(anotherGuess == 'y'){
            cout << "Input: ";
            cin >> word;
            cin >> id;
            cout << endl;
            if(word.size() != 5 || id.size() != 5){
                cerr << "Invalid Input" << endl;
                return 1;
            }
            //narrow down possibilies one letter at a time
            for(int currLetter = 0; currLetter < 5; currLetter++){
                auto i = possibilies.begin();
                while(i < possibilies.end()){
                    if(id[currLetter] == 'b'){
                        //remove word if word has letter
                        if(i->find(word[currLetter]) != string::npos){
                            possibilies.erase(i);
                        } else {i++;}
                    }
                    else if(id[currLetter] == 'g'){
                        //remove word if letter not in current location
                        if((*i)[currLetter] != word[currLetter]){
                            possibilies.erase(i);
                        } else {i++;}
                    }
                    else if(id[currLetter] == 'y'){
                        //remove word if word has letter in location
                        if((*i)[currLetter] == word[currLetter]){
                            possibilies.erase(i);
                        }
                        //remove word if letter not in another location
                        else if(i->find(word[currLetter]) == string::npos){
                            possibilies.erase(i);
                        } else {i++;}
                    }
                    else {
                        cout << "Invalid Input" << endl;
                        break;
                    }
                }
            }
            
            //Output possibilies
            cout << "Possibilies:" << endl;
            for(int i = 0; i < possibilies.size(); i++){
                cout << possibilies[i] << endl;
            }
            cout << endl;
            
            cout << "Another guess? (y/n)" << endl;
            cin >> anotherGuess;
            cout << endl;
        }
        cout << "New Wordle? (y/n)" << endl;
        cin >> anotherWordle;
        cout << endl;
    }
    cout << "Happy Wordling!" << endl << endl;
    return 0;
}
