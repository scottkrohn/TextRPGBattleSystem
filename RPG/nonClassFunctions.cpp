#include "jobClasses.h"
#include "weaponsClasses.h"
#include <ctime>
#include <cstdlib>

// function called to seed random numbers for the program
void SeedRandom()
{
	std::srand(std::time(0));
}

// function is used to return a random number within a specified range.
int DamageChangeAmount(std::size_t variancePercent)
{
	std::size_t randomRange = rand() % (variancePercent * 2 + 1);
	int damageChangeAmount = randomRange - variancePercent;
	return damageChangeAmount;
}

//jobType: 1 == Warrior, 2 == Mage
PlayerCharacterBase * CreatePlayerCharacter(const std::string name, const std::size_t jobType)
{
	enum jobTypes {jobTypeWarrior = 1,
				   jobTypeMage = 2,
				   jobTypeArcher = 3};
	if(jobType == jobTypeWarrior)
	{
		Weapon defaultWeapon("Rusted Sword", 1);
		return new Warrior(name, defaultWeapon);
	}
	else if(jobType == jobTypeMage)
	{
		Weapon defaultWeapon("Driftwood Staff", 2);
		return new Mage(name, defaultWeapon);
	}
	else if(jobType == jobTypeArcher)
	{
		Weapon defaultWeapon("Long Bow", 1);
		return new Archer(name, defaultWeapon);
	}
	else
	{
		std::cout << "ERROR: invalid jobType selection" << std::endl;
		return NULL;
	}
}

void HandleInvalidInput(std::istream &inputStream)
{
	inputStream.clear();
	std::cout << "Invalid option, please try again." << std::endl;
	while(inputStream.get() != '\n')
	{
		continue;
	}
}