#include "enemyClasses.h"

/*********************************************************/
/************** EnemyBase CLASS FUNCTIONS ****************/
/*********************************************************/

// Default constructor
EnemyBase::EnemyBase(const std::string name = "Unknown Enemy"):
	enemyName(name), currentHitPoints(BASE_MAX_HIT_POINTS), maxHitPoints(BASE_MAX_HIT_POINTS),
	level(BASE_ENEMY_LEVEL), attackPower(BASE_ATTACK_POWER), expValue(BASE_EXP_VALUE),
	goldValue(BASE_GOLD_VALUE), isDead(false)
{
}

//	This is the constructor that will be used when an enemy is randomy created 
//	based on the level of the player. Created values for maxHitPoints, 
//	currentHitPoints, attackPower and expValue based off the enemy level 
//	supplied as an argument.

EnemyBase::EnemyBase(const std::size_t lvl, const std::string name = "Unknown Name"): 
	enemyName(name), level(lvl), isDead(false)
{
	if(level > 10)	// Check to make sure level input was valid, if not correct it.
	{
		std::cout << "I WAS PASSED A BAD VALUE" << std::endl;
		level = 10;
	}
	maxHitPoints = BASE_MAX_HIT_POINTS * level * .5;
	currentHitPoints = maxHitPoints;
	attackPower = BASE_ATTACK_POWER + (2 * level);
	expValue = BASE_EXP_VALUE + (5 * level);
	goldValue = BASE_GOLD_VALUE + (5 * level);
}


// Check if enemy is dead, return true if enemy is dead.                        
bool EnemyBase::EnemyIsDead() const
{
	return isDead;
}

// Return exp value of the enemy.
std::size_t EnemyBase::EnemyExpValue() const
{
	return expValue;
}

// Return the level of the enemy.
std::size_t EnemyBase::EnemyLevel() const
{
	return level;
}

// Returns the name of the enemy.
std::string EnemyBase::ReturnName() const
{
	return enemyName;
}

// Returns the gold value of the enemy.
std::size_t EnemyBase::EnemyGoldValue() const
{
	return goldValue;
}

// Increases the enemy's current hit points.
void EnemyBase::GainHitPoints(const std::size_t hitPointsGained)
{
	if((currentHitPoints + hitPointsGained) > maxHitPoints)
	{
		currentHitPoints = maxHitPoints;
	}
	else
	{
		currentHitPoints += hitPointsGained;
	}
}

// Randomly chooses an ability for the enemy to use. There is a 50% change it
// the enemy will use AbilityOne, 33.3% chance it will use AbilityTwo, and
// 16.6% change it will use AbilityThree.
std::size_t EnemyBase::UseAbility()
{
	std::size_t randomNum = rand() % 6 + 1;
	if(randomNum >= 1 && randomNum <= 3)
		return AbilityOne();
	else if(randomNum >=4 && randomNum <= 5)
		return AbilityTwo(); 
	else if(randomNum = 6)
		return AbilityThree();
}


// Takes damage and subtracts from enemy hit points.
// Sets isDead bool if damage kills enemy.
void EnemyBase::TakeDamage(const std::size_t damageTaken)
{
	std::cout << "The " << enemyName << " takes " << damageTaken
			  << " points of damage!" << std::endl;
	if(int(currentHitPoints) - int(damageTaken) > 0)
	{
		currentHitPoints -= damageTaken;
	}
	else
	{
		currentHitPoints = 0;
		isDead = true;
		std::cout << enemyName << " has been defeated!" << std::endl;
	}
}

//	BasicAttack is the same for all derived classes. The amount of damage done
//	is equal to the enemy's attackPower with a variance range of 30% plus or minus.
std::size_t EnemyBase::BasicAttack()
{
	std::size_t randomRange = rand() % (DAMAGE_VARIANCE_PERCENT * 2 + 1);
	int damageChangeAmount = randomRange - DAMAGE_VARIANCE_PERCENT;
	std::size_t damageTotal = 0;
	double percentOfChange = 0.0;
	if(damageChangeAmount >= 0)
	{
		percentOfChange = double(damageChangeAmount) / 100;
		damageTotal = attackPower + attackPower * percentOfChange;
	}
	else
	{
		percentOfChange = -1 * double(damageChangeAmount) / 100;
		damageTotal = attackPower * (1 - percentOfChange);
	}
	return damageTotal;
}

// Displays the enemy's hit points as a value and a percentage.
void EnemyBase::DisplayHitPoints() const
{
	std::cout << enemyName << "\tLVL " << level << " - "
			  << (double(currentHitPoints) / double(maxHitPoints)) * 100 
			  << "% - HP: " << currentHitPoints
			  << "/" << maxHitPoints << std::endl;
}

void EnemyBase::Debug() const
{
	std::cout << "enemyName:         " << enemyName << std::endl;
	std::cout << "currentHitPoints:  " << currentHitPoints << std::endl;
	std::cout << "maxHitPoints:      " << maxHitPoints << std::endl;
	std::cout << "level:             " << level << std::endl;
	std::cout << "attackPower:       " << attackPower << std::endl;
	std::cout << "expValue:          " << expValue << std::endl;
	std::cout << "goldValue:         " << goldValue << std::endl;
}

/*********************************************************/
/************** WyvernEnemy CLASS FUNCTIONS **************/
/*********************************************************/

// Default constructor
WyvernEnemy::WyvernEnemy(const std::string name): EnemyBase(name)
{
}

WyvernEnemy::WyvernEnemy(const std::size_t lvl, const std::string name):
	EnemyBase(lvl, name)
{
}

// Attack: damage based on BasicAttack().
std::size_t WyvernEnemy::AbilityOne()
{
	std::size_t damageTotal = 0;
	damageTotal = BasicAttack();
	std::cout << "The " << ReturnName() << " attacks!" << std::endl;
	return damageTotal;
}

// Hell Dive: The wyvern does 1.5 times attackPower as damage.
std::size_t WyvernEnemy::AbilityTwo()
{
	double damageMultiplier = 1.5;
	std::size_t damageTotal = 0;
	damageTotal += attackPower * damageMultiplier;
	std::cout << "The " << ReturnName() << " uses Hell Dive!" << std::endl;
	return damageTotal;
}

// Fire Breath: The wyvern does 2.5 times attackPower as damage.
std::size_t WyvernEnemy::AbilityThree()
{
	double damageMultiplier = 2.5;
	std::size_t damageTotal = attackPower * damageMultiplier;
	std::cout << "The " << ReturnName() << " uses Fire Breath!" << std::endl;
	return damageTotal;
}

/*********************************************************/
/************** GoblinEnemy CLASS FUNCTIONS **************/
/*********************************************************/

// Default constructor
GoblinEnemy::GoblinEnemy(const std::string name): EnemyBase(name)
{
}

GoblinEnemy::GoblinEnemy(const std::size_t lvl, const std::string name):
	EnemyBase(lvl, name)
{
}

// Attack: damage based on BasicAttack().
std::size_t GoblinEnemy::AbilityOne()
{
	std::size_t damageTotal = 0;
	damageTotal += BasicAttack();
	std::cout << "The " << ReturnName() << " attacks!" << std::endl;
	return damageTotal;
}

// Shank: The goblin attacks 2 times in one turn.
std::size_t GoblinEnemy::AbilityTwo()
{
	std::size_t damageTotal = 0;
	const std::size_t numberOfAttacks = 2;
	for(std::size_t attackCount = 0; attackCount != numberOfAttacks; ++attackCount)
	{
		damageTotal += BasicAttack();
	}
	std::cout << "The " << ReturnName() << " uses Shank!" << std::endl;
	return damageTotal;
}

// Goblin Rush: The golbin attacks 3 times in one turn.
std::size_t GoblinEnemy::AbilityThree()
{
	std::size_t damageTotal = 0;
	const std::size_t numberOfAttacks = 3;
	for(std::size_t attackCount = 0; attackCount != numberOfAttacks; ++attackCount)
	{
		damageTotal += BasicAttack();
	}
	std::cout << "The " << ReturnName() << " uses Goblin Rush!" << std::endl;
	return damageTotal;
}

/*********************************************************/
/************** WightEnemy CLASS FUNCTIONS ***************/
/*********************************************************/

// Default Constructor
WightEnemy::WightEnemy(const std::string name): EnemyBase(name)
{
}

WightEnemy::WightEnemy(const std::size_t lvl, const std::string name):
	EnemyBase(lvl, name)
{
}

// Attack: damage based on BasicAttack()
std::size_t WightEnemy::AbilityOne()
{
	std::size_t damageTotal = 0;
	damageTotal += BasicAttack();
	std::cout << "The " << ReturnName() << " attacks!" << std::endl;
	return damageTotal;
}

// Blood Scythe: Does Normal Attack damage x2, heals the Wight for 50% of damage done.
std::size_t WightEnemy::AbilityTwo()
{
	std::size_t damageTotal = 0;
	std::size_t healingAmount = 0;
	const double percentOfChange = .50;
	const std::size_t numberOfAttacks = 2;
	for(std::size_t attackCount = 0; attackCount != numberOfAttacks; ++attackCount)
	{
		damageTotal += BasicAttack();
	}
	healingAmount = damageTotal * percentOfChange;
	GainHitPoints(healingAmount);
	std::cout << "The " << ReturnName() << " uses Blood Scythe!" << std::endl;
	std::cout << "The " << ReturnName() << " regains " << healingAmount 
			  << " hit points." << std::endl;
	return damageTotal;
}

// Hell's Fury: Does damage equal to 25% of the wight's max HP. 
std::size_t WightEnemy::AbilityThree()
{
	const double percentOfChange = .25;
	std::size_t damageTotal = 0;
	damageTotal += maxHitPoints * percentOfChange;
	std::cout << "The " << ReturnName() << " uses Hell's Fury!" << std::endl;
	return damageTotal;
}

/*********************************************************/
/************** BossNergal CLASS FUNCTIONS ***************/
/*********************************************************/

BossNergal::BossNergal(const std::string name): EnemyBase(name)
{
	maxHitPoints = NERGAL_BASE_HIT_POINTS;
	currentHitPoints = maxHitPoints;
	expValue = NERGAL_EXP_VALUE;
	goldValue = NERGAL_GOLD_VALUE;
}

BossNergal::BossNergal(const std::size_t lvl, const std::string name):
	EnemyBase(lvl, name)
{
	maxHitPoints = NERGAL_BASE_HIT_POINTS;
	currentHitPoints = maxHitPoints;
	expValue = NERGAL_EXP_VALUE;
	goldValue = NERGAL_GOLD_VALUE;
}

// Tongue Lash: attack based on BasicAttack()
std::size_t BossNergal::AbilityOne()
{
	std::size_t damageTotal = 0;
	damageTotal += BasicAttack();
	std::cout << "Nergal uses Tongue Lash!" << std::endl;
	return damageTotal;
}

// Demon's Blood: Does BasicAttack() damage x 1.5, heals Nergel for 30% of dmg
std::size_t BossNergal::AbilityTwo()
{
	std::size_t damageTotal = 0;
	std::size_t healingDone = 0;
	const double healingMultiplier = .3;
	const double damageMultiplier = 1.5;
	damageTotal += BasicAttack() * damageMultiplier;
	healingDone += damageTotal * healingMultiplier;
	std::cout << "Nergal uses Demon's Blood!" << std::endl;
	std::cout << "Nergal regains " << healingDone << " hit points!" << std::endl;
	return damageTotal;
}

// Soul Reaper: Does 2.5 BasicAttackDamage()
std::size_t BossNergal::AbilityThree()
{
	std::size_t damageTotal = 0;
	const double damageMultiplier = 2.5;
	damageTotal += BasicAttack() * damageMultiplier;
	std::cout << "Nergal uses Soul Reaper!" << std::endl;
	return damageTotal;
}

/*********************************************************/
/*************** BossAegir CLASS FUNCTIONS ***************/
/*********************************************************/

BossAegir::BossAegir(const std::string name): EnemyBase(name)
{
	maxHitPoints = AEGIR_BASE_HIT_POINTS;
	currentHitPoints = maxHitPoints;
	expValue = AEGIR_EXP_VALUE;
	goldValue = AEGIR_GOLD_VALUE;
}

BossAegir::BossAegir(const std::size_t lvl, const std::string name): 
	EnemyBase(lvl, name)
{
	maxHitPoints = AEGIR_BASE_HIT_POINTS;
	currentHitPoints = maxHitPoints;
	expValue = AEGIR_EXP_VALUE;
	goldValue = AEGIR_GOLD_VALUE;
}

// Crush: attack based on BasicAttack()
std::size_t BossAegir::AbilityOne()
{
	std::size_t damageTotal = 0;
	damageTotal += BasicAttack();
	std::cout << "Aegir uses Crush!" << std::endl;
	return damageTotal;
}

// Typhoon: Does BasicAttack() dmg x1.5, 50% of the time it does 2.5x dmg
std::size_t BossAegir::AbilityTwo()
{
	std::size_t damageTotal = 0;
	double damageMultiplier = 1.5;
	const std::size_t randomNumber = rand() % 2; // number between 0-1
	if(randomNumber == 1)
	{
		damageMultiplier = 2.5;
	}
	damageTotal += BasicAttack() * damageMultiplier;
	std::cout << "Aegir casts Typhoon!" << std::endl;
	return damageTotal;
}

// The Drowning: attack for BaseDamage() x2, heals Aegir for 30% of damage done
std::size_t BossAegir::AbilityThree()
{
	std::size_t damageTotal = 0;
	std::size_t healingDone = 0;
	const double healingMultiplier = .3;
	const double damageMultiplier = 2;
	damageTotal += BasicAttack() * damageMultiplier;
	healingDone += damageTotal * healingMultiplier;
	std::cout << "Aegir performs The Drowning!" << std::endl;
	std::cout << "Aegir regains " << healingDone << " hit points." << std::endl;
	return damageTotal;
}

/*********************************************************/
/*************** BossZoltan CLASS FUNCTIONS ***************/
/*********************************************************/
BossZoltan::BossZoltan(const std::string name): EnemyBase(name)
{
	maxHitPoints = ZOLTAN_BASE_HIT_POINTS;
	currentHitPoints = maxHitPoints;
	expValue = ZOLTAN_EXP_VALUE;
	goldValue = ZOLTAN_GOLD_VALUE;
}

BossZoltan::BossZoltan(const std::size_t lvl, const std::string name):
	EnemyBase(lvl, name)
{
	maxHitPoints = ZOLTAN_BASE_HIT_POINTS;
	currentHitPoints = maxHitPoints;
}

// Eye Gouge: does damage based on BasicAttack()
std::size_t BossZoltan::AbilityOne()
{
	std::size_t damageTotal = 0;
	damageTotal += BasicAttack();
	std::cout << "Zoltan uses Eye Gouge!" << std::endl;
	return damageTotal;
}

// Razor Wing: does BasicAttack() damage x2
std::size_t BossZoltan::AbilityTwo()
{
	std::size_t damageTotal = 0;
	double damageMultiplier = 2;
	damageTotal += BasicAttack() * damageMultiplier;
	std::cout << "Zoltan uses Razor Wing!" << std::endl;
	return damageTotal;
}

// Summon the Man in Black: summon man in black does damage equal to 1-5% of 
// the remaining HP of Zoltan
std::size_t BossZoltan::AbilityThree()
{
	std::size_t damageTotal = 0;
	std::size_t randomNumber = rand() % 5 + 1;		// number between 1-5
	double percentOfChange = double(randomNumber) / 100;	// 1%-5%
	damageTotal += currentHitPoints * percentOfChange;
	std::cout << "Zoltan summons the Man in Black!" << std::endl;
	std::cout << "The Man in Black's casts Deathcrush!" << std::endl;
	return damageTotal;
}