#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "Member.h"

Member::Member() 
{

}


Member::Member(std::string input)
{
	cipherKey = input;
}


//array of values that can be mutated or crossed over
//input key
//output key


void Member::mutate()
{
	//mutates elements from the member
	

	//mutate test
	//randomly select two letters, then swap places
	//these letters are swapped because if they were truly random, duplicates would occur
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(0, 25);
	int randomOne = distribution(generator);
	int randomTwo = distribution(generator);

	char elementOne = english[randomOne];
	char elementTwo = english[randomTwo];

	while (elementOne == elementTwo)
	{
		//if they are the same rerandomize and reassign values
		randomOne = distribution(generator);
		randomTwo = distribution(generator);
		
		elementOne = english[randomOne];
		elementTwo = english[randomTwo];
	}

	int letterOneAt = 0;
	int letterTwoAt = 0;

	//swap elements one and two
	for (int i = 0; i < 26; i++)
	{
		if (cipherKey.at(i) == elementOne)
		{
			letterOneAt = i;
		}

		if (cipherKey.at(i) == elementTwo)
		{
			letterTwoAt = i;
		}
	}
	
	cipherKey.at(letterOneAt) = elementTwo;
	cipherKey.at(letterTwoAt) = elementOne;
}





void Member::crossover(Member t1, Member t2)
{
	//take elements from t1 and elements from t2 and cross them over


	//crossover test
	//randomly select 4 letters from both t1 and t2 and then cross them over
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(0, 25);
	int randomLetterOne = distribution(generator);
	int randomLetterTwo = distribution(generator);
	int randomLetterThree = distribution(generator);
	int randomLetterFour = distribution(generator);

	//assign random numbers to letters

	char letterOne = english[randomLetterOne];
	char letterTwo = english[randomLetterTwo];
	char letterThree = english[randomLetterThree];
	char letterFour = english[randomLetterFour];

	//check to make sure all the letters are unique
	while ((letterOne == letterTwo) || (letterOne == letterThree) || (letterOne == letterFour)
		|| (letterTwo == letterThree) || (letterTwo == letterFour) || (letterThree == letterFour))
	{
		//if they are the same rerandomize and reassign values
		randomLetterOne = distribution(generator);
		randomLetterTwo = distribution(generator);
		randomLetterThree = distribution(generator);
		randomLetterFour = distribution(generator);

		letterOne = english[randomLetterOne];
		letterTwo = english[randomLetterTwo];
		letterThree = english[randomLetterThree];
		letterFour = english[randomLetterFour];
	}


	//maintains the locations of the letters being crossed over in both members
	std::vector<int> t1location;
	std::vector<int> t2location;

	for (int i = 0; i < 26; i++)
	{
		char currentT1 = t1.cipherKey.at(i);
		if (currentT1 == letterOne || currentT1 == letterTwo || currentT1 == letterThree || currentT1 == letterFour)
		{
			t1location.push_back(i);
		}

		char currentT2 = t2.cipherKey.at(i);
		if (currentT2 == letterOne || currentT2 == letterTwo || currentT2 == letterThree || currentT2 == letterFour)
		{
			t2location.push_back(i);
		}
	}


	//once the locations of the letters have been found, they are then swapped
	for (int v = 0; v < 4; v++)
	{
		char temp = t1.cipherKey.at(t1location.at(v));
		t1.cipherKey.at(t1location.at(v)) = t2.cipherKey.at(t1location.at(v));
		t2.cipherKey.at(t1location.at(v)) = temp;
	}

}


void Member::checkDuplicates()
{
	//initialize empty vector that indicates whethere the string has every letter
	std::vector<int> lettersFound;
	for (int i = 0; i < english.size(); i++)
		lettersFound.push_back(0);

	for (int p = 0; p < cipherKey.size(); p++)
	{
		for (int letter = 0; letter < english.size(); letter++)
		{
			if (english.at(letter) == cipherKey.at(p))
				lettersFound.at(letter)++;
		}
	}

	for (int out = 0; out < lettersFound.size(); out++)
	{
		if (lettersFound.at(out) == 2)
		{
			for (int replace = 0; replace < lettersFound.size(); replace++)
			{
				if (lettersFound.at(replace) == 0)
				{
					char temp = cipherKey.at(out);
					cipherKey.at(out) = cipherKey.at(replace);
					cipherKey.at(replace) = temp;
				}
			}
		}
	}
}
