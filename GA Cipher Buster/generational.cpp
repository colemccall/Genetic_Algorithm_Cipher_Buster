#include <iostream>
#include <string>
#include <vector>
#include "Member.h"
#include "Genetic.h"



generational::generational()
{

}



generational::generational(std::string codefile, std::string tablefile)
{
	initializeContactTable(tablefile);
	initializeCode(codefile);
	initializePopulationUnique(1000);
	normalizeContactTable();
}



void generational::runGenerationGeneticAlgorithm()
{
	//while population not good enough
	int counter = 0, crossoverCount = 0, mutateCount = 0, totalCount = 0;

	while (bestFitnessInPopulation() > populationFitnessThreshold)
	{
		Member xPrimeOne = bestAndNext().at(0);
		Member xPrimeTwo = bestAndNext().at(1);

		for (int i = 2; i < population.size(); i += 2)
		{
			//select 2 members from the population
			Member xPrimeI = population.at(i);
			Member xPrimeI1 = population.at(i + 1);


			if (crossoverProb())
			{
				std::vector<Member> children = pmx(xPrimeI, xPrimeI1);
				xPrimeI = children.at(0);
				xPrimeI1 = children.at(1);
				crossoverCount++;
			}


			if (mutateProb())
			{
				xPrimeI.mutate();
				xPrimeI1.mutate();
				mutateCount++;
			}

			
			//the child may be the same as parent, or it may have mutated or crossed over, either way its added back into the population
			xPrimeI.fitness = calculateMemberFitness(xPrimeI);
			xPrimeI1.fitness = calculateMemberFitness(xPrimeI1);
			insert(xPrimeI);
			insert(xPrimeI1);

		}

		//the top two are left the same and kept untouched
		xPrimeOne.fitness = calculateMemberFitness(xPrimeOne);
		xPrimeTwo.fitness = calculateMemberFitness(xPrimeTwo);
		insert(xPrimeOne);
		insert(xPrimeTwo);
		

		counter++;
		totalCount++;

		std::cout << "Generation: " << counter << " best fitness is " << bestFitnessInPopulation() << std::endl;


		//this feature allows the population to reset if no keys actaully find a solution
		//this is done by seeing if the best key meets the standard after 100 generations
		if (counter == 100)
		{
			counter = 0;
			mutateCount = 0;
			crossoverCount = 0;
			population.clear();
			initializePopulationUnique(1000);

			std::cout << std::endl << "Population is not good enough... restarting with new population" << std::endl;
		}
	}

	std::cout << "Mutations: " << mutateCount << " , Crossovers: " << crossoverCount << " , Generations: " << totalCount << std::endl;
}

//replaces the worst value
void generational::generationalInsert(Member current, int location)
{
	population.at(location) = current;
}


std::vector<Member> generational::bestAndNext()
{	
	std::vector<Member> topTwo;

	double bestFitness = population.at(0).fitness;
	double nextBestFitness = population.at(1).fitness;
	int bestLocation = 0;
	int nextBestLocation = 1;
	
	for (int i = 0; i < population.size(); i++)
	{
		double currentFitness = population.at(i).fitness;


		//best member
		if (currentFitness < bestFitness)
		{
			//move the current best to second best 
			nextBestFitness = bestFitness;
			nextBestLocation = bestLocation;

			//then update and set best member
			bestFitness = currentFitness;
			bestLocation = i;
		}


		//second best member
		if (currentFitness < nextBestFitness && currentFitness > bestFitness)
		{
			nextBestFitness = currentFitness;
			nextBestLocation = i;
		}
	}


	//once the best members have been found, add them and return them
	topTwo.push_back(population.at(bestLocation));
	topTwo.push_back(population.at(nextBestLocation));
	return topTwo;
}

