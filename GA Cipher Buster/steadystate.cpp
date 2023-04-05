#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Member.h"
#include "Genetic.h"

steadystate::steadystate()
{

}

steadystate::steadystate(std::string codefile, std::string tablefile)
{
	initializeContactTable(tablefile);
	initializeCode(codefile);
	initializePopulationUnique(100);
	normalizeContactTable();
}


std::vector<Member> steadystate::selectMembers()
{
	//select two random numbers between 0 and 9 using a mersenne twister
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(0, population.size() - 1);
	int randomOne = distribution(generator);
	int randomTwo = distribution(generator);


	//if the two random numbers are same, get new numbers
	while (randomOne == randomTwo)
	{
		randomTwo = distribution(generator);
	}


	Member t1 = population.at(randomOne);
	Member t2 = population.at(randomTwo);
	std::vector<Member> selectedMembers;
	selectedMembers.push_back(t1);
	selectedMembers.push_back(t2);

	return selectedMembers;
}



void steadystate::runSteadyStateGeneticAlgorithm()
{
	//while population is not good enough
	//have a method that evaluates the population and returns a bool if good enough or not
	int counter = 0;
	int crossoverCount = 0;
	int mutateCount = 0;


	populationFitnessThreshold = 2850;
	while (bestFitnessInPopulation() > populationFitnessThreshold)
	{
		//select 2 members from the population
		//(t1, t2) = select(P)
	
		//random select
		std::vector<Member> members = selectMembers();
		
		//best selection
		//std::vector<Member> members = selectBest();
		
		if (debug) { std::cout << "Members selected" << std::endl; }
		Member t1 = members.at(0);
		Member t2 = members.at(1);
		Member xPrime;
		
		
		if (crossoverProb())
		{
			xPrime = pmx(t1, t2).at(0);
			crossoverCount++;
		}
		else
		{
			if (counter % 2 == 0)
				xPrime = t2;
			else
				xPrime = t1;
		}

		if (mutateProb())
		{
			xPrime.mutate(); 
			mutateCount++;
		}
		

		xPrime.fitness = calculateMemberFitness(xPrime);

		//insert xPrime into Population by replacing worst in Population
		insert(xPrime);

		counter++;
		

		std::cout << "Generation " << counter << ": best fitness is " << bestFitnessInPopulation() << std::endl;
	}


	std::cout << "Mutations: " << mutateCount << " , Crossovers: " << crossoverCount << " , Generations: " << counter << std::endl;
	displayPopulationFitness();
}