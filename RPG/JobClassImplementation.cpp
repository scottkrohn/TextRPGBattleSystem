#include "jobClasses.h"
#include "nonClassFunctionsHeader.h"
#include <iostream>

/*********************************************************/
/********* PlayerCharacterBase CLASS FUNCTIONS ***********/
/*********************************************************/

// PlayerCharacterBase constructor
PlayerCharacterBase::PlayerCharacterBase(std::string name, Weapon weapon): 
	characterName(name), level(BASE_CHARACTER_LEVEL), expNeededToLevel(BASE_EXP_PER_LVL), 
	currentExp(BASE_EXP), defense(BASE_DEFENSE), maxHitPoints(BASE_MAX_HIT_POINTS), 
	currentHitPoints(BASE_MAX_HIT_POINTS), attackPower(BASE_ATTACK_POWER), 
	magicPower(BASE_MAGIC_POWER), damageModifier(0), abilityUseFailure(false),
	equippedWeapon(weapon), gold(BASE_GOLD_AMOUNT), isDead(false)
{
}

/************** PRIVATE PlayerCharacterBase FUNCTIONS ************/

bool PlayerCharacterBase::HasEnoughGold(const std::size_t goldAmount) const
{
	if(goldAmount <= gold)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// increase the amount of exp needed to level
void PlayerCharacterBase::IncreaseExpToLevel()
{
	expNeededToLevel += BASE_EXP_PER_LVL * level * .05;
}

// incease the players level and call supporting functions to increase other stats
void PlayerCharacterBase::IncreasePlayerLevel()
{
	// check if player is below the max character level
	if(level < MAX_CHARACTER_LVL)
	{
		++level;
		IncreaseExpToLevel();
		IncreaseMaxHitPoints();
		IncreaseDefense();
		IncreaseAttackPower();
		IncreaseMagicPower();
		std::cout << "You have reached level " << level << std::endl;
	}
}

/************** PUBLIC PlayerCharacterBase FUNCTIONS ************/
//	GainExp checks to make sure player isn't at max level. If they're below 
//	the max level, increase their currentExp amount by expGained. If the new 
//	expGained is greater than expNeededToLevel, calculate how much exp they've
//	exceeded the amount by and assign to expCarriedToNextLevel. Call 
//	IncreasePlayerLevel() to increment players level, then set current exp to 
//	expCarriedToNextLevel. If the new currentExp exceeds the new 
//	expNeededToLevel, loop and level the player again. 
void PlayerCharacterBase::GainExp(const std::size_t expGained)
{
	if(level < MAX_CHARACTER_LVL)
	{
		currentExp += expGained;
		while(currentExp >= expNeededToLevel)
		{
			std::size_t expCarriedToNextLevel = currentExp - expNeededToLevel;
			// increases players level and increases amount of exp needed for next level
			IncreasePlayerLevel();
			currentExp = expCarriedToNextLevel;
		}
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << characterName << " gained " << expGained 
				  << " Experience Points!  " << "(" << currentExp
				  << "/" << expNeededToLevel << ")" << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
	}
}

std::size_t PlayerCharacterBase::UseAbility(const std::size_t &abilityNumber)
{

	if(abilityNumber == 1)
	{
		GainPower();	// gain 1 stamina
		return AbilityOne();
	} 
	else if(abilityNumber == 2)
	{
		GainPower();	// gain 1 stamina
		return AbilityTwo();
	}
	else if(abilityNumber == 3)
	{
		return AbilityThree();
	}
	else if(abilityNumber == 4)
	{
		return AbilityFour();
	}
	else if(abilityNumber == 5)
	{
		return AbilityFive();
	}
	else if(abilityNumber == 6)
	{
		return AbilitySix();
	}
	else
	{
		std::cout << "ERROR: ability number out of range." << std::endl;
		return 0;
	}
}

std::string PlayerCharacterBase::ReturnName() const
{
	return characterName;
}

std::size_t PlayerCharacterBase::ReturnLevel() const
{
	return level;
}

std::size_t PlayerCharacterBase::AbilitiesKnownCount() const
{
	// abilityCount is the number of abilities to display
	std::size_t abilitiesKnown = 2;
	//	The loop below through each level. If the player is level 4, it
	//	loops 4 times. Each time it passed an even level it increments
	//	the abilityCount. 
	for(std::size_t i = 1; i != ReturnLevel()+1; ++i)
	{
		if(i % 2 == 0)
		{
			++abilitiesKnown;
		}
	}
	return abilitiesKnown;
}

std::size_t PlayerCharacterBase::TotalGold() const
{
	return gold;
}

// returns true if player is dead
bool PlayerCharacterBase::PlayerIsDead() const
{
	return isDead;
}

bool PlayerCharacterBase::AbilityFailed() const
{
	return abilityUseFailure;
}

//	ModifyDamage takes a size_t argument that is used to determine how much to return.
//	Another Ability function will set the damage modifier and ModifyDamage will convert
//	that damage modifier into a percentage value. It then determines the modified damage
//	amount to return by multiplying it's argument damageTotal by the percentage modifier.
//	The function also adds any weapon damage to the modified damage.
std::size_t PlayerCharacterBase::ModifyDamage(const std::size_t damageTotal)
{
	std::size_t modifiedDamage = 0;
	double percentOfChange = double(damageModifier) / 100;
	modifiedDamage += equippedWeapon.ReturnDamage();
	modifiedDamage += percentOfChange * (damageTotal + modifiedDamage);
	damageModifier = 0;
	return modifiedDamage;
}

void PlayerCharacterBase::EquipWeapon(const Weapon &weapon)
{
	equippedWeapon = weapon;
}

bool PlayerCharacterBase::SpendGold(const std::size_t goldAmount)
{
	if(HasEnoughGold(goldAmount))
	{
		gold -= goldAmount;
		return true;
	}
	else
	{
		return false;
	}
}

//	TakeDamage first checks the isDead status variable to make sure the player 
//	is alive. If they're alive, calculate the damage they take using 
//	damageTaken and adjusting for the players defense. Check if 
//	adjustedDamageTaken exceeds the player's current health. If it doesn't 
//	kill the player, subtract the amount from their hit points, otherwise 
//	inform the user the player has been killed, set hit points to zero and 
//	set isDead flag.
void PlayerCharacterBase::TakeDamage(const std::size_t damageTaken)
{
	if(!isDead)
	{
		// the amount of damage that defense negates is as a percent. 5 def negates 5% damage
		std::size_t adjustedDamageTaken = damageTaken - (damageTaken * (double(defense)/100));
		std::cout << "You take " << adjustedDamageTaken << " points of damage!" << std::endl;
		// check if this attack will kill the player, values converted to int to allow negative
		if((int(currentHitPoints) - int(adjustedDamageTaken)) > 0)
		{
			currentHitPoints -= adjustedDamageTaken;
		}
		else
		{
			currentHitPoints = 0;
			isDead = true;
			std::cout << "Player has been killed!" << std::endl;
		}
	}
	else
	{
		std::cout << "You cannot attack a dead character." << std::endl;
	}
}

// display users current and max hit points
void PlayerCharacterBase::DisplayHitPoints() const
{
	std::cout << characterName << "\tLVL " << level << " - " 
			  << (double(currentHitPoints) / double(maxHitPoints)) * 100 
			  << "% - HP: " << currentHitPoints
			  << "/" << maxHitPoints << std::endl;
}

void PlayerCharacterBase::GainGold(const std::size_t goldAmount)
{
	gold += goldAmount;
	std::cout << characterName << " earned " << goldAmount << " gold!" << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
}

// increase currentHealth
void PlayerCharacterBase::GainHitPoints(const std::size_t hitPointsGained)
{
	if(currentHitPoints + hitPointsGained >= maxHitPoints)
	{
		currentHitPoints = maxHitPoints;
	}
	else
	{
		currentHitPoints += hitPointsGained;
	}
}

// increase hit points using the formula below, increase player health to max
void PlayerCharacterBase::IncreaseMaxHitPoints()
{
	maxHitPoints += BASE_MAX_HIT_POINTS * (0.5 * level) * .10;
	currentHitPoints = maxHitPoints;
}

// increase defense by 2
void PlayerCharacterBase::IncreaseDefense()
{
	defense = defense + 2;
}

// increase attack power by 5 per level
void PlayerCharacterBase::IncreaseAttackPower()
{
	attackPower += 5;
}

// increase magic power by 5 per level
void PlayerCharacterBase::IncreaseMagicPower()
{
	magicPower += 3;
}

// display all player data
void PlayerCharacterBase::Debug() const
{
	std::cout << "characterName:    " << characterName << std::endl;
	std::cout << "level:            " << level << std::endl;
	std::cout << "expNeededToLevel: " << expNeededToLevel << std::endl;
	std::cout << "currentExp:       " << currentExp << std::endl;
	std::cout << "defense:          " << defense << std::endl;
	std::cout << "maxHitPoints:     " << maxHitPoints << std::endl;
	std::cout << "currentHitPoints: " << currentHitPoints << std::endl;
	std::cout << "attackPower       " << attackPower << std::endl;
	std::cout << "gold              " << gold << std::endl;
}

/*********************************************************/
/***************** Warrior CLASS FUNCTIONS ***************/
/*********************************************************/

// Warrior default constructor
Warrior::Warrior(std::string name, Weapon weapon): PlayerCharacterBase(name, weapon), 
	currentStamina(WARRIOR_BASE_STAMINA)
{
	defense = WARRIOR_BASE_DEFENSE;	// Warrior has higher base defense.
	abilityNames.push_back("Sword Slash (SC - 0)");
	abilityNames.push_back("Shield Bash (SC - 0) - Bash enemy, increase damage of next attack by 75%.");
	abilityNames.push_back("Life Blade  (SC - 1) - Heal yourself by amount equal to damage done.");
	abilityNames.push_back("Power Slash (SC - 2) - Deals 50% more damage than Sword Slash.");
	abilityNames.push_back("Tri-Slash   (SC - 3) - Attack 3 times.");
	abilityNames.push_back("Oathkeeper  (SC - 4) - Deal 3x attack power in damage, heals player.");
	abilityNames.push_back("UNNAMED ABILITY");
}

/**************** PUBLIC Warrior FUNCTIONS ***************/

void Warrior::DisplayAbilities() const
{
	//// abilitiesKnown is the number of abilities to display
	std::size_t abilitiesKnown = AbilitiesKnownCount();
	std::cout << "Current Stamina: " << currentStamina << std::endl;
	// display the correct number of abilites for the player's level
	for(std::size_t abilityCount = 0; abilityCount != abilitiesKnown; ++abilityCount)
	{
		std::cout << "[" << abilityCount+1 << "] " 
				  << abilityNames[abilityCount] << std::endl;
	}
}

void Warrior::DisplayStats() const
{
	std::cout << "Name: " << characterName << " -- Level " << level 
			  << " Warrior" << std::endl;
	std::cout << "Current Weapon: " << equippedWeapon.ReturnWeaponName() 
			  << " DMG: " << equippedWeapon.ReturnDamage() << std::endl;
	std::cout << "Exp Points:   " << currentExp << "/" << expNeededToLevel 
			  << std::endl;
	std::cout << "Hit Points:   " << currentHitPoints << "/" << maxHitPoints << std::endl;
	std::cout << "Stamina:      " << currentStamina << "/" << WARRIOR_MAX_STAMINA << std::endl;
	std::cout << "Defense:      " << defense << std::endl;
	std::cout << "Attack Power: " << attackPower << std::endl;
	std::cout << "Gold:         " << gold << std::endl;
	
}

// Sword Slash: normal attack, doesn't use any stamina, earns 1 stamina 
std::size_t Warrior::AbilityOne()
{
	std::size_t staminaCost = 0;
	std::size_t damageTotal = 0;
	if(UsePower(staminaCost))
	{
		damageTotal += BasicAttackDamage();
		damageTotal += ModifyDamage(damageTotal);
		std::cout << "You use Sword Slash!" << std::endl;
	}
	return damageTotal;
}

// Shield Bash: does 50% of Sword Slash damage, makes next attack to damage + 75%, earns 1 stamina
std::size_t Warrior::AbilityTwo()
{
	std::size_t staminaCost = 0;
	std::size_t damageTotal = 0;
	if(UsePower(staminaCost))
	{
		std::size_t swordSlashDamage = BasicAttackDamage();
		damageTotal = swordSlashDamage * .50;
		damageModifier = 75;	// increase damage modifier for next attack
		std::cout << "You use Shield Bash!" << std::endl;
	}
	return damageTotal;
}

// Life Blade: does Sword Slash damage and gives the player hit points equal to damage done
std::size_t Warrior::AbilityThree()
{
	const std::size_t staminaCost = 1;
	std::size_t damageTotal = 0;
	if(UsePower(staminaCost))
	{
		damageTotal = BasicAttackDamage();
		damageTotal = damageTotal + ModifyDamage(damageTotal);
		GainHitPoints(damageTotal);		// heal player by same amount as damageTotal
		std::cout << "You use Life Blade!" << std::endl;
		std::cout << "You regain " << damageTotal << " hit points." << std::endl;
	}
	return damageTotal;
}

// Power Slash: does Sword Slash damage + 50%, costs 2 stamina
std::size_t Warrior::AbilityFour()
{
	const std::size_t staminaCost = 2;
	std::size_t damageTotal = 0;
	if(UsePower(staminaCost))
	{
		damageTotal = BasicAttackDamage();
		damageTotal += damageTotal * .50;
		damageTotal += ModifyDamage(damageTotal);	// add modded damage if there is any
		std::cout << "You use Power Slash!" << std::endl;
	}
	return damageTotal;
}

// Tri-Slash: attacks 3 times, doing Sword Slash damage on each attack
std::size_t Warrior::AbilityFive()
{
	const std::size_t staminaCost = 3;
	std::size_t damageTotal = 0;
	const std::size_t numberOfAttacks = 3;
	if(UsePower(staminaCost))
		{
		for(std::size_t attackCount = 0; attackCount != numberOfAttacks; ++attackCount)
		{
			damageTotal += BasicAttackDamage();
		}
		std::cout << "You use Tri-Slash!" << std::endl;
	}
	return damageTotal;
}

// Oathkeeper: deals 3x attack power and heals player for 25% of damage done.
std::size_t Warrior::AbilitySix()
{
	const std::size_t staminaCost = 4;
	std::size_t damageTotal = 0;
	std::size_t damageMultiplier = 3;
	std::size_t healingAmount = 0;
	if(UsePower(staminaCost))
	{
		damageTotal = attackPower * damageMultiplier;
		damageTotal += ModifyDamage(damageTotal);
		healingAmount += damageTotal * .25;
		GainHitPoints(healingAmount);
		std::cout << "You use Oathkeeper!" << std::endl;
		std::cout << "You regain " << healingAmount << " hit points." << std::endl;
	}
	return damageTotal;
}

std::string Warrior::JobType() const
{
	return "warrior";
}

// Display all player data.
void Warrior::Debug() const
{
	PlayerCharacterBase::Debug();
	std::cout << "stamina:          " << currentStamina << std::endl;
}

/**************** PRIVATE Warrior FUNCTIONS **************/
void Warrior::GainPower()
{
	if(currentStamina < WARRIOR_MAX_STAMINA)
		++currentStamina;
}

// increase hit points using the formula below, increase player health to max
void Warrior::IncreaseMaxHitPoints()
{
	maxHitPoints += BASE_MAX_HIT_POINTS * (0.5 * level) * .15;
	currentHitPoints = maxHitPoints;
}

// Increase defense by 2.
void Warrior::IncreaseDefense()
{
	defense += 4;
}

// Increase attack power by 2, warrior gains less attack power per lvl.
void Warrior::IncreaseAttackPower()
{
	attackPower += 2;
}

// check if staminaCost argument is more than players current stamina
// return false if cost is too great, else subtract staminaCost from currentStamina, return true
bool Warrior::UsePower(const std::size_t powerCost)
{
	if(powerCost > currentStamina)
	{
		std::cout << "You don't have enough stamina for that ability." << std::endl;
		abilityUseFailure = true;
		return false;
	}
	else
	{
		abilityUseFailure = false;
		currentStamina -= powerCost;
		return true;
	}
}

// The variance in an attack is determined by the variable DAMAGE_VARIANCE_PERCENT.
// If DAMAGE_VARIANCE_PERCENT is 30, then the damage done will be in the range
// of the attack power +/- up to 30%. Meaning if attackPower is 10, the range
// of possible damage will be [7, 13].
std::size_t Warrior::BasicAttackDamage()
{
	int damageChangeAmount = DamageChangeAmount(DAMAGE_VARIANCE_PERCENT);
	std::size_t damageTotal = 0;
	double percentOfChange = 0.0;
	if(damageChangeAmount >= 0)
	{
		percentOfChange = double(damageChangeAmount) / 100;
		damageTotal = attackPower + attackPower * percentOfChange;
	}
	// If the damage amount is to be decreased, set percentOfChange equal 
	// to positive damageChangeAmount / 10. This produces a positive percentage 
	// used to set the value of damageTotal.
	else
	{
		percentOfChange = -1 * double(damageChangeAmount) / 100;
		damageTotal = attackPower * (1 - percentOfChange);
	}
	return damageTotal;
}

/*********************************************************/
/******************* Mage CLASS FUNCTIONS ****************/
/*********************************************************/

Mage::Mage(const std::string name, Weapon weapon): PlayerCharacterBase(name, weapon),
	currentMana(MAGE_BASE_MANA)
{
	abilityNames.push_back("Fire        (MC - 0)");
	abilityNames.push_back("Refresh     (MC - 0) - Heal yourself and restore mana.");
	abilityNames.push_back("Fire Storm  (MC - 2) - Unleash a storm of fire, deals 1.5x Fire damage.");
	abilityNames.push_back("Inferno     (MC - 4) - Cast 2-3 fireballs.");
	abilityNames.push_back("Flame Bath  (MC - 5) - Deal damage, increase damage of next spell by 50%.");
	abilityNames.push_back("HellFire    (MC - 6) - Summon Lord Belial.");
	abilityNames.push_back("UNNAMED ABILITY");
}

/**************** PUBLIC Mage FUNCTIONS ***************/

void Mage::DisplayAbilities() const
{
	//// abilitiesKnown is the number of abilities to display
	std::size_t abilitiesKnown = AbilitiesKnownCount();
	std::cout << "Current Mana: " << currentMana << std::endl;
	// display the correct number of abilites for the player's level
	for(std::size_t abilityCount = 0; abilityCount != abilitiesKnown; ++abilityCount)
	{
		std::cout << "[" << abilityCount+1 << "] " 
				  << abilityNames[abilityCount] << std::endl;
	}
}

void Mage::DisplayStats() const
{
	std::cout << "Name: " << characterName << " -- Level " << level 
			  << " Mage" << std::endl;
	std::cout << "Current Weapon: " << equippedWeapon.ReturnWeaponName() 
			  << " DMG: " << equippedWeapon.ReturnDamage() << std::endl;
	std::cout << "Exp Points:   " << currentExp << "/" << expNeededToLevel 
			  << std::endl;
	std::cout << "Hit Points:   " << currentHitPoints << "/" << maxHitPoints << std::endl;
	std::cout << "Mana:         " << currentMana << "/" << MAGE_MAX_MANA << std::endl;
	std::cout << "Defense:      " << defense << std::endl;
	std::cout << "Magic Power:  " << magicPower << std::endl;
	std::cout << "Gold:         " << gold << std::endl;
}

// Fire: does damage based on magicPower of Mage
std::size_t Mage::AbilityOne()
{
	std::size_t powerCost = 0;
	std::size_t damageTotal = 0;
	if(UsePower(powerCost))
	{
		damageTotal += BasicMagicDamage();
		damageTotal += ModifyDamage(damageTotal);
		std::cout << "You cast Fire!" << std::endl;
	}
	return damageTotal;
}

// Refresh: heals the Mage for 1.5x magicPower and restores 4 mana points
std::size_t Mage::AbilityTwo()
{
	std::size_t powerCost = 0;
	std::size_t amountOfManaToGain = 4;
	std::size_t hitPointsGained = magicPower * 1.5;
	if(UsePower(powerCost))
	{
		GainHitPoints(hitPointsGained);
		for(std::size_t i = 0; i != amountOfManaToGain; ++i)
		{
			GainPower();
		}
		std::cout << "You cast Refresh!" << std::endl;
		std::cout << "You regained " << hitPointsGained << " hit points. " << std::endl;
		std::cout << "You regained " << amountOfManaToGain << " mana points." << std::endl;
	}
	return 0;	// this ability does zero damage
}

// Fire Storm: does 1.5x BasicMagicDamage, costs 2 mana points.
std::size_t Mage::AbilityThree()
{
	std::size_t powerCost = 2;
	std::size_t damageTotal = 0;
	std::size_t damageMultiplier = 1.5;
	if(UsePower(powerCost))
	{
		damageTotal += BasicMagicDamage() * 1.5;
		damageTotal += ModifyDamage(damageTotal);
		std::cout << "You cast Fire Storm!" << std::endl;
	}
	return damageTotal;
}

// Inferno: casts 2-3 fireballs, costs 4 mana
std::size_t Mage::AbilityFour()
{
	std::size_t powerCost = 4;
	std::size_t damageTotal = 0;
	std::size_t numberOfFireballs = rand() % 2 + 2;
	if(UsePower(powerCost))
	{
		for(std::size_t castCount = 0; castCount != numberOfFireballs; ++castCount)
		{
			damageTotal += BasicMagicDamage();
		}
		damageTotal += ModifyDamage(damageTotal);
		std::cout << "You cast Inferno!" << std::endl;
	}
	return damageTotal;
}

// Flame Bath: inflict 2x base magic damage and increases damage of next
// spell by 50%. Costs 5 mana.
std::size_t Mage::AbilityFive()
{
	std::size_t powerCost = 5;
	std::size_t damageTotal = 0;
	std::size_t damageMultiplier = 2;
	if(UsePower(powerCost))
	{
		for(std::size_t castCount = 0; castCount != damageMultiplier; ++castCount)
		{
			damageTotal += BasicMagicDamage();
		}
		damageTotal += ModifyDamage(damageTotal);
		damageModifier = 50;	// Increases damage of next spell
		std::cout << "You cast Flame Bath!" << std::endl;
		std::cout << "Damage of your next spell incresed by " << damageModifier
				  << "%." << std::endl;
	}
	return damageTotal;
}

// Hellfire: Summons Belial, does 4x magicPower damage, costs 6 mana
std::size_t Mage::AbilitySix()
{
	std::size_t powerCost = 6;
	std::size_t damageTotal = 0;
	std::size_t damageMultiplier = 4;
	if(UsePower(powerCost))
	{
		damageTotal += magicPower * damageMultiplier;
		damageTotal += ModifyDamage(damageTotal);
		std::cout << "Belial has been summoned!" << std::endl
				  << "Belial unlseashes Hellfire!" << std::endl;
	}
	return damageTotal;
}

std::string Mage::JobType() const
{
	return "mage";
}

void Mage::Debug() const
{
	PlayerCharacterBase::Debug();
	std::cout << "magicPower:       " << magicPower << std::endl;
	std::cout << "currentMana:      " << currentMana << std::endl;
}


/**************** PRIVATE Mage FUNCTIONS **************/
void Mage::GainPower()
{
	if(currentMana < MAGE_MAX_MANA)
	{
		++currentMana;
	}
}

// increase hit points using the formula below, increase player health to max
void Mage::IncreaseMaxHitPoints()
{
	maxHitPoints += BASE_MAX_HIT_POINTS * (0.5 * level) * .05;
	currentHitPoints = maxHitPoints;
}

// mage class gains 1 defense per level, the lowest amount of all the classes
void Mage::IncreaseDefense()
{
	++defense;
}

// UsePower returns true if powerCost is not more than the currentStamina.
// If the powerCost is greater than the 
bool Mage::UsePower(const std::size_t powerCost)
{
	if(powerCost > currentMana)
	{
		std::cout << "You do not have enough mana to cast that spell." << std::endl;
		abilityUseFailure = true;	// set failure status if not enough mana
		return false;
	}
	else
	{
		abilityUseFailure = false;
		currentMana -= powerCost;
		return true;
	}
}

// BasicMagicDamage is the base damage amount used for several of the Mage
// class abilities. It returns a value that is in the range of +/- 30% of the
// Mage's magicPower then mulitplies that by 1.5. 
std::size_t Mage::BasicMagicDamage()
{
	int damageChangeAmount = DamageChangeAmount(DAMAGE_VARIANCE_PERCENT);
	std::size_t damageTotal = 0;
	double percentOfChange = 0.0;
	if(damageChangeAmount >= 0)
	{
		percentOfChange = double(damageChangeAmount) / 100;
		damageTotal = (magicPower + magicPower * percentOfChange) * 1.5;
	}
	else
	{
		percentOfChange = -1 * double(damageChangeAmount) / 100;
		damageTotal = (magicPower * (1 - percentOfChange)) * 1.5;
	}
	return damageTotal;
}

/*********************************************************/
/****************** Archer CLASS FUNCTIONS ***************/
/*********************************************************/

Archer::Archer(std::string name, Weapon weapon): PlayerCharacterBase(name, weapon),
	currentStamina(ARCHER_BASE_STAMINA)
{
	attackPower = ARCHER_BASE_ATTACK_POWER;
	abilityNames.push_back("Quick Shot  (SC - 0)");
	abilityNames.push_back("Focus Shot  (SC - 0) - Deal 75% damage and increase next shot by 75%.");
	abilityNames.push_back("Siphon Shot (SC - 1) - Shoot and heal yourself for 75% of normal damage.");
	abilityNames.push_back("Barrage     (SC - 2) - Shoot 3 arrows at once.");
	abilityNames.push_back("Cannon Shot (SC - 3) - Deal 2x atk power in damage, 50% chance to do 3x.");
	abilityNames.push_back("Demon Arrow (SC - 4) - Deal 4x attack power in damage.");
	abilityNames.push_back("UNNAMED ABILITY");
}

/**************** PUBLIC Archer FUNCTIONS ***************/
void Archer::DisplayAbilities() const
{
	std::size_t abilitiesKnown = AbilitiesKnownCount();
	std::cout << "Current Stamina: " << currentStamina << std::endl;
	for(std::size_t abilityCount = 0; abilityCount != abilitiesKnown; ++abilityCount)
	{
		std::cout << "[" << abilityCount+1 << "] "
				  << abilityNames[abilityCount] << std::endl;
	}
}

void Archer::DisplayStats() const
{
	std::cout << "Name: " << characterName << " -- Level " << level
			  << " Archer" << std::endl;
	std::cout << "Current Weapon: " << equippedWeapon.ReturnWeaponName()
			  << " DMG: " << equippedWeapon.ReturnDamage() << std::endl;
	std::cout << "Exp Points:    " << currentExp << "/" << expNeededToLevel
			  << std::endl;
	std::cout << "Hit Points:    " << currentHitPoints << "/" << maxHitPoints << std::endl;
	std::cout << "Stamina:       " << currentStamina << "/" << ARCHER_MAX_STAMINA	 << std::endl;
	std::cout << "Defense:       " << defense << std::endl;
	std::cout << "Attack Power:  " << attackPower << std::endl;
	std::cout << "Gold:          " << gold << std::endl;
}

// Quick Shot: Does damage equal to attackPower +/- 30%
std::size_t Archer::AbilityOne()
{
	std::size_t staminaCost = 0;
	std::size_t damageTotal = 0;
	if(UsePower(staminaCost))
	{
		damageTotal += BasicRangedDamage();
		damageTotal += ModifyDamage(damageTotal);
		std::cout << "You use Quick Shot!" << std::endl;
	}
	return damageTotal;
}

// Focus Shot: Increases damage of next shot by 75% and deals 75% damage.
std::size_t Archer::AbilityTwo()
{
	std::size_t staminaCost = 0;
	std::size_t damageTotal = 0;
	double percentOfChange = .75;
	if(UsePower(staminaCost))
	{
		damageTotal += BasicRangedDamage() * percentOfChange;
		damageModifier = 75;
		std::cout << "You use Focus Shot!" << std::endl;
		std::cout << "Your next ability will do 75% bonus damage!" << std::endl;
	}
	return damageTotal;
}

// Siphon Shot: Deal 75% normal damage, heal player equal to damage sone
std::size_t Archer::AbilityThree()
{
	std::size_t staminaCost = 1;
	std::size_t damageTotal = 0;
	std::size_t healingDone = 0;
	double percentOfChange = .75;
	if(UsePower(staminaCost))
	{
		damageTotal += BasicRangedDamage() * percentOfChange;
		damageTotal += ModifyDamage(damageTotal);
		healingDone = damageTotal;
		GainHitPoints(healingDone);
		std::cout << "You use Siphon Shot!" << std::endl;
		std::cout << "You regain " << healingDone << " hit points" << std::endl;
	}
	return damageTotal;
}

// Barrage: Shoots 3 arrows at once
std::size_t Archer::AbilityFour()
{
	std::size_t staminaCost = 2;
	std::size_t damageTotal = 0;
	std::size_t shotTotal = 3;
	double percentOfChange = .75;
	if(UsePower(staminaCost))
	{
		for(std::size_t shotNumber = 0; shotNumber != shotTotal; ++shotNumber)
		{
			damageTotal += BasicRangedDamage() * percentOfChange;
		}
		damageTotal += ModifyDamage(damageTotal);
		std::cout << "You use Barrage!" << std::endl;
	}
	return damageTotal;
}

// Cannon Shot: Does damage equal to 2.5 times attack power, 50% to do 3.5x attack power
std::size_t Archer::AbilityFive()
{
	std::size_t staminaCost = 3;
	std::size_t damageTotal = 0;
	double damageMultiplier = 2.5;
	std::size_t randomNumber = rand() % 2;
	if(UsePower(staminaCost))
	{
		if(randomNumber == 1)
		{
			damageMultiplier = 3.5;
		}
		damageTotal += attackPower * damageMultiplier;
		damageTotal += ModifyDamage(damageTotal);
		std::cout << "You use Cannon Shot!" << std::endl;
	}
	return damageTotal;
}

// Demon Arrow: Does 4x attackPower as damage;
std::size_t Archer::AbilitySix()
{
	std::size_t staminaCost = 4;
	std::size_t damageTotal = 0;
	double damageMultiplier = 4;
	if(UsePower(staminaCost))
	{
		damageTotal += attackPower * damageMultiplier;
		damageTotal += ModifyDamage(damageTotal);
		std::cout << "You use Demon Arrow!" << std::endl;
	}
	return damageTotal;
}

std::string Archer::JobType() const
{
	return "archer";
}


/**************** PRIVATE Archer FUNCTIONS ***************/
void Archer::GainPower()
{
	if(currentStamina < ARCHER_MAX_STAMINA)
	{
		++currentStamina;
	}
}

void Archer::IncreaseDefense()
{
	defense += 2;
}

void Archer::IncreaseAttackPower()
{
	attackPower += 3;
}

bool Archer::UsePower(const std::size_t powerCost)
{
	if(powerCost > currentStamina)
	{
		std::cout << "You do not have enough stamina to use that ability." << std::endl;
		abilityUseFailure = true;
		return false;
	}
	else
	{
		abilityUseFailure = false;
		currentStamina -= powerCost;
		return true;
	}
}

std::size_t Archer::BasicRangedDamage()
{
	int damageChangeAmount = DamageChangeAmount(DAMAGE_VARIANCE_PERCENT);
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

