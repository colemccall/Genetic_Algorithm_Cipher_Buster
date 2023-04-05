#ifndef GENETIC
#define GENETIC
#include <string>
#include <vector>
#include "Member.h"


class Genetic
{

private:
	


protected:
	int populationsize = 10;
	double populationFitness, populationFitnessThreshold;
	bool debug = false;
	bool debugPMX = false;
	bool debugFitness = false;



public:
	std::vector<Member> population;
	std::vector<std::string> cypheredMessage;
	//std::vector<bool> isMessageCyphered;
	std::string englishKey = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int contactTable[26][26];
	int contactTableElements, codedMessageElements;


	//constructors
	Genetic();


	//methods to find probability of crossing over and mutating
	bool crossoverProb();
	bool mutateProb();

	
	//quick check to make sure that popualtion has been initialized and genetic algorithm can start
	bool isPopulationSet();


	//methods to set up and run algorithm 
	std::string decipheredCode(Member);
	std::string returnMessage();
	double calculateMemberFitness(Member);
	double bestFitnessInPopulation();
	double calculatePopulationFitness();
	void insert(Member);


	void initializePopulation();
	void initializePopulationUnique(int);
	void initializeContactTable(std::string);
	void initializeCode(std::string);
	void normalizeContactTable();	//make sure that the english contact table has the same frequency as the message
	void displayContactTable();
	void displayPopulation();
	void displayCode();
	void displayPopulationFitness();
	void displayBest();

	
	//partially mapped crossover that will return two children
	std::vector<Member> pmx(Member, Member);
	std::vector<Member> selectBest();
	

	
};


class generational : public Genetic
{
private:

public:
	//constructors
	generational();
	generational(std::string, std::string);

	//population vector of next generation of members
	std::vector<Member> nextGenPopulation;

	//methods that starts the generational algorithm
	void runGenerationGeneticAlgorithm();

	//methods
	std::vector<Member> bestAndNext();

	//insert that replaces either keeps parent or replaces it with child instead of randomly inserting
	void generationalInsert(Member, int);

};






class steadystate : public Genetic
{
private:

public:
	//constructors
	steadystate();
	steadystate(std::string, std::string);


	//method that starts the steady state algorithm
	void runSteadyStateGeneticAlgorithm();
	
	
	Member select();
	std::vector<Member> selectMembers();

};


#endif


