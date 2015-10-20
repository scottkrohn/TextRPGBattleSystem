#include "jobClasses.h"
#include <iostream>
#include <string>

/********* PlayerCharacterBase CLASS FUNCTIONS ***********/
// PlayerCharacterBase constructor
PlayerCharacterBase::PlayerCharacterBase(std::string name = "Unamed Character"): 
	level(1), expNeededToLevel(BaseExpNeededToLevel), currentExp(0), defense(BaseDefense),
	maxHitPoints(BaseMaxHp), currentHitPoints(BaseMaxHp), attackPower(baseAttackPower),
	isDead(false), characterName(name)
{
}

// PROTECTED PlayerCharacterBase MEMBER FUNCTIONS: used by public member functions
bool PlayerCharacterBase::checkIfDead(const std::size_t damageTaken)
{
	// check if player is alive and damageTaken isn't negative
	if(!isDead && damageTaken >=0)	
	{
		// check if the damage taken kills the player
		if(currentHitPoints - damageTaken <= 0)
		{
			// set player's HP to zero since HP can't be negative
			currentHitPoints = 0;
			isDead = true;
			return true;
		}
	}
	return false;	// return false if player is not dead
}

void PlayerCharacterBase::increaseExpToLevel()
{
	expNeededToLevel += BaseExpNeededToLevel * level * .05
}

void PlayerCharacterBase::increasePlayerLevel()
{
	// check if player is below the max character level
	if(level < MaxCharacterLevel)
	{
		++level;
		increaseExpToLevel
	}
}

void PlayerCharacterBase::increaseMaxHP()
{
	maxHitPoints += maxHitPoints * (0.5 * level) * .10;
}

// PUBLIC PlayerCharacterBase MEMBER FUNCTIONS
void PlayerCharacterBase::takeDamage(const std::size_t damageTaken)
{
	if(!isDead)
	{
		// the amount of damage that defense negates is as a percent. 5 def negates 5% damage
		std::size_t actualDamageTaken = damageTaken - damageTaken * (defense/100);
		// check if this attack will kill the player
		if(!checkIfDead(actualDamageTaken))
		{
			currentHitPoints -= actualDamageTaken;
		}
		else
		{
			std::cout << "Player has been killed!" << std::endl;
		}
	}
}

void PlayerCharacterBase::gainExp(const std::size_t expGained)
{
	if(level < MaxCharacterLevel)
	{
		currentExp += expGained;
		if(currentExp >= expNeededToLevel)
		{
			// increases players level and increases amount of exp needed for next level
			increasePlayerLevel();
		}
	}
}
