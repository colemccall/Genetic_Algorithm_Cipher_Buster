#ifndef MEMBER
#define MEMBER
#include <vector>
#include <string>


class Member
{
private:




public:
	//constructors
	Member();
	Member(std::string);


	//array of values that can be mutated or crossed over
	std::string cipherKey;
	std::string english = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	double fitness;
	


	//methods used to mutate and crossover
	//only implemented sometimes, based on probability methods above
	void mutate();
	void crossover(Member, Member);
	
	
	void checkDuplicates();


	


};

#endif
