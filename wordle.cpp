// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void wordleHelper(
		std::string input, 
		std::string floats, 
		const std::set<std::string>& dict, 
		std::set<std::string>& words, 
		unsigned int dashes);

unsigned int numDashes(std::string str);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    
		set<string> results;
		unsigned int dashNum = numDashes(in);
    wordleHelper(in, floating, dict, results, dashNum);
    return results;
}

// Define any helper functions here

void wordleHelper(
		std::string input, 
		std::string floats, 
		const std::set<std::string>& dict, 
		std::set<std::string>& words, 
		unsigned int dashes)
{
		unsigned int floatsSize = floats.size();
		unsigned int inputSize = input.size();

		// if there are less dashes than mandatory floating letters
		// left, it is not possible to form a valid word.
		if(dashes < floatsSize){
			return;
		}

		// if no dashes are left, compare the formed word against
		// the dictionary, and add to the set of results if it is
		// a valid word
		if(dashes == 0){
			if(dict.find(input) != dict.end()){
				words.insert(input);
			}
			return;
		}


		// Otherwise, find the first dash. At this point, increment
		// through the floating characters, then all characters, 
		// calling wordleHelper each time to recurse to the next 
		// dash. Recursing back up, the words set will include
		// all valid words.

		unsigned int dashLoc = -1;
		for(unsigned int k = 0; k < inputSize; k++){
			if(input[k] == '-'){
				dashLoc = k;
				break;
			}
		}
		for(unsigned int i = 0; i < floatsSize; i++){
			input[dashLoc] = floats[i];
			string newFloats = floats.substr(0, i) + floats.substr(i + 1);
			wordleHelper(input, newFloats, dict, words, dashes - 1);
		}
		for(unsigned int j = 97; j < 123; j++){
			input[dashLoc] = (char) j;
			wordleHelper(input, floats, dict, words, dashes - 1);
		}
}

// function used to find the number of dashes the word starts
// off with
unsigned int numDashes(std::string str){
	unsigned int count = 0;
	for(unsigned int i = 0; i < str.size(); i++){
		if(str[i] == '-'){
			count++;
		}
	}
	return count;
}
