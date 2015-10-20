#ifndef WEAPONSCLASSES_H_
#define WEAPONSCLASSES_H_
#include <string>

// The WeaponBase class is used as a member of the player character classes.
// Each player character has a weapon, and the damage member of the weapon
// increases the damage output of the player by that amount. For example,
// if the player attacks for 15 and the Weapon's damage is 4, the total
// damage inflicted by the player would be 19.

class Weapon
{
public:
	Weapon(const std::string name = "Unknown Weapon", const std::size_t dmg = 0, const std::size_t weaponPrice = 0);
	Weapon(const Weapon &newWeapon);
	Weapon & operator=(const Weapon &rhs);
	std::string ReturnWeaponName() const {return weaponName;}
	std::size_t ReturnDamage() const {return damage;}
	std::size_t ReturnPrice() const {return price;}
	void Debug() const;
private:
	std::string weaponName;
	std::size_t damage;
	std::size_t price;
};
#endif