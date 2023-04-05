#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include "Genetic.h"
#include "Member.h"



//prototypes
void instructions();
void details();


int main(int argc, char** argv)
{
	std::cout << "Genetic Algorithm Cypher Problem" << std::endl;

	std::string correctp1209key = "OSJPEDQYVCRTZNBHKGALMUIFXW";
	std::string correctTestKey = "VQHIGLSUJDCTBFWOEYMNAZXPRK";

	//if there are less than 2 arguments or more than 3, an error messge is returned to the user
	if (argc < 3 || argc > 4)
	{
		std::cout << "Invalid number of arguments entered by command line" << std::endl;
		instructions();
	}
	else
	{
		std::string encryptedFile = argv[1];
		std::string contactTableFile = argv[2];
		std::string gaType = "none";
		bool gaDeclared = false;

		if (argc == 4)
		{
			gaType = argv[3];
			if (gaType == "s" || gaType == "g" || gaType == "test")
			{
				gaDeclared = true;
			}
		}

		if (gaDeclared == false)
		{
			//ask user if they want to run steady state "s" or generational "g"
			gaType = "whatever the user says";
		}


		//run the type of algorithm the user specified: generational or steady state
		if (gaType == "s")
		{
			steadystate cypherbuster = steadystate(encryptedFile, contactTableFile);
			if (cypherbuster.isPopulationSet())
			{
				cypherbuster.runSteadyStateGeneticAlgorithm();
				cypherbuster.displayBest();
			}

			else
				std::cout << "Population was not initialized properly" << std::endl;
		}
		else if (gaType == "g")
		{
			generational cypherbuster = generational(encryptedFile, contactTableFile);
			if (cypherbuster.isPopulationSet())
			{
				cypherbuster.runGenerationGeneticAlgorithm();
				cypherbuster.displayBest();
				if (encryptedFile == "p1209.code")
					std::cout << "Correct Key:   " << correctp1209key << std::endl << std::endl;
				if (encryptedFile == "test.code")
					std::cout << "Correct Key:   " << correctTestKey << std::endl << std::endl;
			}
			else
				std::cout << "Population was not initialized properly" << std::endl;
		}
		

		//also, if the user specifies test, the answer keys can be tested
		else if (gaType == "test")
		{
			Genetic testp1209 = Genetic();
			Member p1209key = Member(correctp1209key);
			testp1209.initializeCode("p1209.code");
			std::cout << p1209key.cipherKey << " yields a message "
				<< std::endl << testp1209.decipheredCode(p1209key) 
				<< std::endl << "Correct Key:   " << correctp1209key << std::endl << std::endl;;

			
			Genetic testClear = Genetic();
			Member testKey = Member(correctTestKey);
			testClear.initializeCode("test.code");
			std::cout << testKey.cipherKey << " yields a message "
				<< std::endl << testClear.decipheredCode(testKey) 
				<< std::endl << "Correct Key:   " << correctTestKey << std::endl << std::endl;
		}
		

		//otherwise, return list of instructions to run program properly
		else
		{
			instructions();
		}


		details();
	}
}


void instructions()
{
	using namespace std;

	cout << "Genetic Algorithm Cipher Buster Instructions"
		<< endl << "This program requires two command line parameters to run, with an optional third"
		<< endl << "The first parameter is the location of the file that contains the coded message that needs to be decyphered"
		<< endl << "The second parameter is the location of the file that contains the contact table"
		<< endl << "A third parameter can be used to run the program using the steady state algorithm or the generational algorithm"
		<< endl << "The steady state algorithm will be specified by an \"s\" and the generational algorithm specified by a \"g\""
		<< endl << "If no algorithm is specified, the user will be prompted to make a selection"
		<< endl << endl;
}


void details()
{
	using namespace std;

	cout << endl << "Genetic Algorithm Cipher Buster Result Details"
		<< endl << "Mutation Rate: 1 in 4"
		<< endl << "Crossover Rate: 1 in 4"
		<< endl << "Population size: 1000"
		<< endl << "Mutation technique: take two letters in a key and swap them"
		<< endl << "Crossover technique: partially mapped crossover"
		<< endl << "Successful with generational, rarely successful with steady state"
		//<< endl << "Fitness thresholds were predefined after repeated user tests (machine learning?)"
		<< endl << endl;

}