/*
 * This is the header file for the program
 *
 *  Created on: Oct 1, 2018
 *      Author: stefanoroque
 */

#ifndef INSULTGENERATOR_H_
#define INSULTGENERATOR_H_


using namespace std;
#include <vector>
#include <string>

// Since the number of insults is capped, we can express it as a constant
const int MAX_NUM_INSULTS(10000);
// Since the insults are coming from just a single file, we can express it as a constant too
const string INSULTS_SOURCE_FILE("InsultsSource.txt");


// This exception class is thrown if the insult source file can't be read, or the output file can't be written
class FileException{
	string message;
public:
	FileException(string);
	string what();
};  // End of FileException class


// This exception class is thrown if the number of insults that is supplied is not valid
// Not valid means not between 1 and 10000 inclusive
class NumInsultsOutOfBounds{
	string message;
public:
	NumInsultsOutOfBounds(string);
	string what();
};  // End of NumInsultsOutOfBounds class


// Class that will actually generate the insults
class InsultGenerator{
	int source_file_len; // Length of the source file (text file)
	vector<string> word1; // Words in the first column of the source file
	vector<string> word2; // Words in the second column of the source file
	vector<string> word3; // Words in the third column of the source file
public:
	InsultGenerator();  // Default constructor
	void initialize(); // Loads all the words from the source file into the attributes
	string talkToMe(); //Randomly generates a single insult
	vector<string> generate(int); // Generates the requested number of unique insults
	void generateAndSave(string, int); // Generates the requested number of unique insults and saves them to a file
};  // End of InsultGenerator class

#endif /* INSULTGENERATOR_H_ */
