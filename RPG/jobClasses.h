#ifndef JOBCLASSES_H
#define JOBCLASSES_H
#include "weaponsClasses.h"
#include <string>
#include <iostream>
#include <vector>

// The PlayerCharacterBase class is an abstract base class tha is used as the 
// base class for all the derived job classes. There are three derived job 
// classes: Warrior, Mage & Archer. 

class PlayerCharacterBase
{
public:
	// Static const values used by class
	static const std::size_t BASE_EXP = 0;
	static const std::size_t BASE_EXP_PER_LVL = 200;
	static const std::size_t BASE_MAX_HIT_POINTS = 100;
	static const std::size_t BASE_DEFENSE = 10;
	static const std::size_t BASE_ATTACK_POWER = 20;
	static const std::size_t BASE_MAGIC_POWER = 30;
	static const std::size_t MAX_CHARACTER_LVL = 10;
	static const std::size_t BASE_CHARACTER_LEVEL = 1;
	static const std::size_t DAMAGE_VARIANCE_PERCENT = 30;	// 30/100 = .30
	static const std::size_t BASE_GOLD_AMOUNT = 0;
	// Public functions
	PlayerCharacterBase(std::string name = "Default Player", 
		Weapon weapon = Weapon("Default Weapon", 0, 0));
	virtual ~PlayerCharacterBase() {}
	void GainExp(const std::size_t expGained);
	std::size_t UseAbility(const std::size_t &abilityNumber);
	std::string ReturnName() const;
	std::size_t ReturnLevel() const;
	std::size_t AbilitiesKnownCount() const;
	std::size_t TotalGold() const;
	bool PlayerIsDead() const;
	bool AbilityFailed() const;
	std::size_t ModifyDamage(const std::size_t damageTotal);
	void EquipWeapon(const Weapon &weapon);
	bool SpendGold(const std::size_t goldAmount);
	// All public functions below may or may not be redefined by derived classes
	virtual std::size_t AbilityOne() {return 0;}
	virtual std::size_t AbilityTwo() {return 0;}
	virtual std::size_t AbilityThree() {return 0;}
	virtual std::size_t AbilityFour() {return 0;}
	virtual std::size_t AbilityFive() {return 0;}
	virtual std::size_t AbilitySix() {return 0;}
	virtual void DisplayAbilities() const {};
	bool UsePower(const std::size_t powerCost) {}
	virtual void TakeDamage(const std::size_t damageTaken);
	virtual void DisplayHitPoints() const;
	virtual void DisplayStats() const {}
	virtual void GainGold(const std::size_t goldAmount);
	virtual void GainHitPoints(const std::size_t hitPointsGained);
	virtual void GainPower() {};
	virtual void IncreaseMaxHitPoints();
	virtual void IncreaseDefense();
	virtual void IncreaseAttackPower() = 0;
	virtual void IncreaseMagicPower();
	virtual std::string JobType() const {return "none";}
	virtual void Debug() const;
protected:
	std::string characterName;
	std::size_t level;
	std::size_t expNeededToLevel;
	std::size_t currentExp;
	std::size_t defense;
	std::size_t maxHitPoints;
	std::size_t currentHitPoints;
	std::size_t attackPower;
	std::size_t magicPower;
	std::vector<std::string> abilityNames;
	std::size_t damageModifier;
	bool abilityUseFailure;
	Weapon equippedWeapon;
	std::size_t gold;
private:
	bool isDead;
	bool HasEnoughGold(const std::size_t goldAmount) const;
	void IncreaseExpToLevel();		// will not be redefined in derived classes
	void IncreasePlayerLevel();		// will not be redefined in derived classes
};


class Warrior: public PlayerCharacterBase
{
	static const std::size_t WARRIOR_BASE_STAMINA = 0;
	static const std::size_t WARRIOR_MAX_STAMINA = 10;
	static const std::size_t WARRIOR_BASE_DEFENSE = 25;
public:
	Warrior(std::string name = "Default Warror", 
		Weapon weapon = Weapon("Default Weapon", 0, 0));
	~Warrior() {}
	void DisplayAbilities() const;
	void DisplayStats() const;
	std::size_t AbilityOne();		// Sword Slash
	std::size_t AbilityTwo();		// Shield Bash
	std::size_t AbilityThree();		// Life Blade
	std::size_t AbilityFour();		// Power SLash
	std::size_t AbilityFive();		// Tri-Slash
	std::size_t AbilitySix();		// Oathkeeper
	std::string JobType() const;
	void Debug() const;
private:
	void GainPower();				// Warrior class gains 1 stamina per call
	void IncreaseMaxHitPoints();	// Warrior class gains slightly more hp per level than other classes
	void IncreaseDefense();			// Warrior class gains 4 defense per level
	void IncreaseAttackPower();		// Warrior class gains 1 attack power per level
	bool UsePower(const std::size_t powerCost);	 // subtracts argument amt from stamina
	std::size_t BasicAttackDamage();// Basic attack that is +/- 30% of attackPower
	std::size_t currentStamina;		// the warrior class defines one additional data member
};

class Mage: public PlayerCharacterBase
{
	static const std::size_t MAGE_BASE_MANA = 1;
	static const std::size_t MAGE_MAX_MANA = 10;
public:
	Mage(std::string name = "Default Mage", 
		Weapon weapon = Weapon("Default Weapon", 0, 0));
	~Mage() {}
	void DisplayAbilities() const;
	void DisplayStats() const;
	std::size_t AbilityOne();			// Fire
	std::size_t AbilityTwo();			// Refresh 
	std::size_t AbilityThree();			// Fire Storm
	std::size_t AbilityFour();			// Inferno
	std::size_t AbilityFive();			// Flame Bath
	std::size_t AbilitySix();			// Hellfire
	std::string JobType() const;
	void Debug() const;
private:
	void GainPower();				// Mage class gains 1 mana per cll
	void IncreaseMaxHitPoints();	// Mage gains the last amt of HP per lvl
	void IncreaseDefense();			// Mage gains 1 defense per level
	void IncreaseAttackPower() {};	// Not used in Mage class
	bool UsePower(const std::size_t powerCost);	// subtracts arg amt from mana
	std::size_t BasicMagicDamage();	// Basic magic attack that is +/- 30% of magicPower
	std::size_t currentMana;		// Additonal data member used by Mage class
};

class Archer: public PlayerCharacterBase
{
	static const std::size_t ARCHER_BASE_STAMINA = 0;
	static const std::size_t ARCHER_MAX_STAMINA = 10;
	static const std::size_t ARCHER_BASE_ATTACK_POWER = 25;
public:
	Archer(std::string name = "Default Archer", 
		Weapon weapon = Weapon("Default Weapon", 0, 0));
	~Archer () {}
	void DisplayAbilities() const;
	void DisplayStats() const;
	std::size_t AbilityOne();		// Quick Shot
	std::size_t AbilityTwo();		// Concentrate
	std::size_t AbilityThree();		// Siphon Shot
	std::size_t AbilityFour();		// Barrage
	std::size_t AbilityFive();		// Cannon Shot
	std::size_t AbilitySix();		// Demon Arrow
	std::string JobType() const;
private:
	void GainPower();				// Archer gains 2 stamina per call
	void IncreaseDefense();			// Archer gains 2 defense per level
	void IncreaseAttackPower();		// Archer gains 3 attack power per level
	bool UsePower(const std::size_t powerCost);	// Subtracts art amt from stamina
	std::size_t BasicRangedDamage();// Basic ranged attack that is +/- 30% of attackPower
	std::size_t currentStamina;		// Additional data member used by Archer class
};
#endif