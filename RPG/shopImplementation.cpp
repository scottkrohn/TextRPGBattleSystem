#include "shopClasses.h"
#include "nonClassFunctionsHeader.h"
#include <fstream>
#include <iostream>
#include <iomanip>

// InitializeShop takes an ifstream object as an argument and then uses that
// ifstream object to load the class member weaponsForSale with Weapon objects. 
void WeaponShop::InitializeShop(std::ifstream &inputFile)
{
	while(!inputFile.eof())
	{
		std::string weaponName;
		std::size_t weaponDamage;
		std::size_t weaponPrice;
		std::getline(inputFile, weaponName);
		(inputFile >> weaponDamage).get();
		(inputFile >> weaponPrice).get();
		Weapon *weapon = new Weapon(weaponName, weaponDamage, weaponPrice);
		weaponsForSale.push_back(*weapon);
		delete weapon;
	}
}

// Displays the entire inventory of the weapon shop.
void WeaponShop::DisplayInventory() const
{
	std::size_t weaponNumber = 1;
	for(std::vector<Weapon>::const_iterator i = weaponsForSale.begin(); i != weaponsForSale.end(); ++i)
	{
		std::cout << weaponNumber << ": " << std::left << std::setw(17) << i->ReturnWeaponName() << "--"
				  << "DMG: " << i->ReturnDamage() << "\t--" << "Price: "
				  << i->ReturnPrice() << std::endl;
		++weaponNumber;
	}
}

std::size_t WeaponShop::WeaponCost(const std::size_t weaponNumber)
{
	std::size_t weaponIndex = weaponNumber - 1;
	if(0 <= weaponIndex && weaponIndex < weaponsForSale.size())
	{
		return weaponsForSale[weaponIndex].ReturnPrice();
	}
	else
	{
		std::cout << "ERROR: invalid vector index" << std::endl;
	}
}

// Returns a copy of a weapon from the shop when a purchase is made.
Weapon WeaponShop::ReturnSoldWeapon(const std::size_t weaponNumber)
{
	std::size_t weaponIndex = weaponNumber - 1;
	if(0 <= weaponIndex && weaponIndex < weaponsForSale.size())
	{
		return weaponsForSale[weaponIndex];
	}
	else
	{
		std::cout << "ERROR: invalid vector index" << std::endl;
	}
}

// Processes a transaction between a shop object and a player.
bool WeaponShop::ProcessTransaction(Handle<PlayerCharacterBase> &player)
{
	int itemNumber = 0;
	std::cout << "CURRENT GOLD: " << player->TotalGold() << std::endl;
	std::cout << "Which item would you like to buy(0 to cancel): " << std::endl;
	std::cout << ">> ";
	while(!(std::cin >> itemNumber) || itemNumber < 0 || itemNumber > weaponsForSale.size())
	{
		HandleInvalidInput(std::cin);
		std::cout << ">> ";
	}
	if(itemNumber == 0)
	{
		return false;
	}
	else if(player->SpendGold(WeaponCost(itemNumber)))
	{
		Weapon purchasedWeapon(ReturnSoldWeapon(itemNumber));
		player->EquipWeapon(purchasedWeapon);
		std::cout << "You purchased a " << purchasedWeapon.ReturnWeaponName() << std::endl;
		std::cout << purchasedWeapon.ReturnWeaponName() << " equipped." << std::endl;
		return true;
	}
	else
	{
		std::cout << "You don't have enough gold. Transaction aborted." << std::endl;
		return false;
	}
}

// Displays debug data.
void WeaponShop::Debug() const
{
	for(std::vector<Weapon>::const_iterator i = weaponsForSale.begin(); i != weaponsForSale.end(); ++i)
	{
		i->Debug();
	}
}