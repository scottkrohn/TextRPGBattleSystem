#include "weaponsClasses.h"
#include <iostream>
// Default constructor
Weapon::Weapon(const std::string name, const std::size_t dmg, const std::size_t weaponPrice): weaponName(name),
	damage(dmg), price(weaponPrice)
{
}

// Copy constructor
Weapon::Weapon(const Weapon &newWeapon)
{
	weaponName = newWeapon.weaponName;
	damage = newWeapon.damage;
	price = newWeapon.price;
}

// Assignment operator
Weapon & Weapon::operator=(const Weapon &rhs)
{
	weaponName = rhs.weaponName;
	damage = rhs.damage;
	price = rhs.price;
	return *this;
}

void Weapon::Debug() const
{
	std::cout << "Name:   " << weaponName << std::endl;
	std::cout << "Damage: " << damage << std::endl;
	std::cout << "Price:  " << price << std::endl;
}