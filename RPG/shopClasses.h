#ifndef WEAPONSHOPCLASS_H_
#define WEAPONSHOPCLASS_H_
#include "weaponsClasses.h"
#include "handleClass.h"
#include "jobClasses.h"
#include <vector>

class WeaponShop
{
public:
	WeaponShop() {};
	void InitializeShop(std::ifstream &inputFile);
	void DisplayInventory() const;
	std::size_t WeaponCost(const std::size_t weaponNumber);
	Weapon ReturnSoldWeapon(const std::size_t weaponNumber);
	bool ProcessTransaction(Handle<PlayerCharacterBase> &player);
	void Debug() const;
private:
	std::vector<Weapon> weaponsForSale;
};
#endif