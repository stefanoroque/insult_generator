/*
 * This is the implementation file for the program
 *
 *  Created on: Oct 1, 2018
 *      Author: stefanoroque
 */


#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <set>
#include "InsultGenerator.h"

using namespace std;
// Constructor for the FileException class
FileException::FileException(string message) : message(message){
}

string FileException::what(){
	return message;
}

// Constructor for the NumInsultsOutOfBounds class
NumInsultsOutOfBounds::NumInsultsOutOfBounds(string message) : message(message){
}

string NumInsultsOutOfBounds::what(){
	return message;
}

// Constructor for the InsultGenerator class
InsultGenerator::InsultGenerator() : source_file_len(0){
}

void InsultGenerator::initialize(){
	string line;
	ifstream fileIn(INSULTS_SOURCE_FILE.c_str());
	source_file_len = 0;  // Reset the source_file_len attribute to 0
	if (fileIn.fail()){
		throw FileException("Unable to open file: " + INSULTS_SOURCE_FILE);
		return;
	}
	else if (fileIn.is_open()){
		while (!fileIn.eof()){
			fileIn >> line;
			word1.push_back(line);

			fileIn >> line;
			word2.push_back(line);

			fileIn >> line;
			word3.push_back(line);

			source_file_len++;
		}
	fileIn.close();
	}
}

// Generates a single insult
string InsultGenerator::talkToMe(){
	string insult;
	insult = "Thou " + word1.at(rand() % (source_file_len)) + " " + word2.at(rand() % (source_file_len)) + " " + word3.at(rand() % (source_file_len)) + "!";

	return insult;
}

// Generates a vector filled with the specified number of unique insults
vector<string> InsultGenerator::generate(int num_insults){
	// Check if the supplied number of insults is legal
	if (num_insults < 1 || num_insults > MAX_NUM_INSULTS){
		throw NumInsultsOutOfBounds("This is not a legal number of insults. Number must be between 1 and 10000 (inclusive)");
	}

	// Store the generated insults in a set since sets store unique elements following a specific order
	// This means the insults will be stored in alphabetical order with no duplicates
	set<string> generated_insults;
	string single_insult;

	// Continue the loop until the set contains the specified number of insults
	while(num_insults > generated_insults.size()){
		single_insult = talkToMe();
		generated_insults.insert(single_insult);
	}

	vector<string> all_insults;
	// Copy all of the sorted insults into a vector of strings so it can be returned
	copy(generated_insults.begin(), generated_insults.end(), back_inserter(all_insults));

	return all_insults;
}


// Generates the requested number of unique insults and saves them to the file name
void InsultGenerator::generateAndSave(string file_name, int num_insults){
	vector<string> all_insults = generate(num_insults);
	ofstream output_file(file_name);

	if (output_file.fail()){
		throw FileException("Unable to write to file: " + file_name);
	}

	// Go through each insult in the vector and write it to the file
	for (string &insult : all_insults){
		output_file << insult << endl;
	}

	output_file.close();
}


