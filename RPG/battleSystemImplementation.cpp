#include "battleSystemClass.h"
#include "handleClass.h"
#include <Windows.h>

//	The Battle class represents a battle between a player character and a non
//  player character. 

// default constructor, creates a random enemy by calling CreateEnemy
Battle::Battle()
{
}

//	StartBattle is the main routine for the Battle class. When it is called,
//	it creates a random EnemyBase deived object for the player to fight.
//	The Sleep() command is used to insert short delays so the player can 
//	follow the actions taking place.
void Battle::RandomBattle(Handle<PlayerCharacterBase> &player)
{
	CreateEnemy(player->ReturnLevel());
	StartBattle(player);
}

void Battle::BossBattle(Handle<PlayerCharacterBase> &player)
{
	if(player->ReturnLevel() == 3)
	{
		BossNergal *nergalPtr = new BossNergal(3, "Nergal");
		enemy.AssignNewObject(nergalPtr);
	}
	else if(player->ReturnLevel() == 6)
	{
		BossAegir *aegirPtr = new BossAegir(6, "Aegir");
		enemy.AssignNewObject(aegirPtr);
	}
	else if(player->ReturnLevel() == 9)
	{
		BossZoltan *zoltanPtr = new BossZoltan(9, "Zoltan");
		enemy.AssignNewObject(zoltanPtr);
	}
	std::cout << "YOU ARE ABOUT TO FIGHT A BOSS, PRESS ENTER TO BEGIN" << std::endl;
	std::cin.get();
	std::cin.get();
	StartBattle(player);
}

void Battle::StartBattle(Handle<PlayerCharacterBase> &player)
{
	const std::size_t delayInMilliSec = 1100;
	//CreateEnemy(player->ReturnLevel());
	DisplayCombatants(player);
	Sleep(delayInMilliSec);
	// if the player is attacking first
	if(PlayerAttacksFirst())
	{
		// while both enemy and player are alive
		while(!enemy->EnemyIsDead() && !player->PlayerIsDead())
		{
			DisplayHitPoints(player);
			PlayerTurn(player);
			// check if the player's attack has killed the enemy
			if(!enemy->EnemyIsDead())
			{
				Sleep(delayInMilliSec);
				EnemyTurn(player);
				Sleep(delayInMilliSec);
				// check if the enemy's attack has killed the player
				if(player->PlayerIsDead())
				{
					EndBattle(player);
				}
			}
			else if(enemy->EnemyIsDead())
			{
				Sleep(delayInMilliSec);
				EndBattle(player);
			}
		}
	}
	// if the enemy is attacking first
	else
	{
		while(!enemy->EnemyIsDead() && !player->PlayerIsDead())
		{
			EnemyTurn(player);
			// check if enemy's attack has killed the player
			if(!player->PlayerIsDead())
			{
				Sleep(delayInMilliSec);
				DisplayHitPoints(player);
				Sleep(delayInMilliSec);
				PlayerTurn(player);
				Sleep(delayInMilliSec);
				// check if the player's attack has killed the enemy
				if(enemy->EnemyIsDead())
				{
					EndBattle(player);
				}
			}
			else if(player->PlayerIsDead())
			{
				EndBattle(player);
			}
		}
	}
}

// Display the player and enemy hit points
void Battle::DisplayHitPoints(const Handle<PlayerCharacterBase> &player) const
{
	enemy->DisplayHitPoints();
	player->DisplayHitPoints();
}

// Display player and enemy names
void Battle::DisplayCombatants(const Handle<PlayerCharacterBase> &player) const
{
	std::cout << "*************************************" << std::endl;
	std::cout << "\tENEMY ENCOUNTERD!" << std::endl;
	std::cout << player->ReturnName() << "    -- VS --    " << enemy->ReturnName() << std::endl;
	std::cout << "*************************************\n" << std::endl;
}


//	CreateEnemy generates a random number in the range 1-3 inclusive. It then 
//	uses that number to create 1 out of the three different enemy types.
//	The AssignNewObject function from the Handle data member is called to load 
//	the newly created enemy object into the EnemyHandle member.

void Battle::CreateEnemy(const std::size_t playerLevel) 
{
	std::size_t randomEnemyChoice = rand() % 3 + 1;
	if(randomEnemyChoice == 1)
	{
		WyvernEnemy *wyvernEnemyPtr = new WyvernEnemy(playerLevel, "Wyvern");
		enemy.AssignNewObject(wyvernEnemyPtr);
	}
	else if(randomEnemyChoice == 2)
	{
		GoblinEnemy *goblinEnemyPtr = new GoblinEnemy(playerLevel, "Goblin");
		enemy.AssignNewObject(goblinEnemyPtr);
	}
	else if(randomEnemyChoice == 3)
	{
		WightEnemy *wightEnemyPtr = new WightEnemy(playerLevel, "Wight");
		enemy.AssignNewObject(wightEnemyPtr);
	}
	else
	{
		std::cout << "ERROR: UNABLE TO CREATE ENEMY." << std::endl;
	}
}

// Return random value in range 0-1 inclusive, if 1 player attacks first.
bool Battle::PlayerAttacksFirst() const
{
	std::size_t randomNumber = rand() % 2;
	if(randomNumber == 1)
	{
		return true;
	}
	return false;
}

// Returns true if enemy is dead.
bool Battle::EnemyIsDead() const
{
	return enemy->EnemyIsDead();
}

// Awards the player the enemy's exp value.
void Battle::AwardExp(Handle<PlayerCharacterBase> &player)
{
	player->GainExp(enemy->EnemyExpValue());
}

// Awards the player the enemy's gold value.
void Battle::AwardGold(Handle<PlayerCharacterBase> &player)
{
	player->GainGold(enemy->EnemyGoldValue());
}

bool Battle::CheckAbilityEligibility(const Handle<PlayerCharacterBase> &player,
	const std::size_t abilityChoice) const
{
	// If the player knows the ability.
	if(abilityChoice <= player->AbilitiesKnownCount() && abilityChoice > 0)
	{
		return true;
	}
	return false;
}

void Battle::PlayerTurn(Handle<PlayerCharacterBase> &player) 
{
	std::cout << std::endl << "Choose an ability to use:" << std::endl;
	std::size_t abilityChoice = 0;
	std::size_t damageDone = 0;
	player->DisplayAbilities();
	do
	{
		std::cout << ">>>";
		// check for valid input and if ability can be used by the player
		while(!(std::cin >> abilityChoice) || !CheckAbilityEligibility(player, abilityChoice))
		{
			std::cout << "\nInvalid option, please choose again."
					  << std::endl << ">>>";
			std::cin.clear();
			while(std::cin.get() != '\n')
			{
				continue;
			}
		}
		// clear input if user enters an eligible abilityChoice followed by extra chars
		while(std::cin.get() != '\n')
		{
			continue;
		}
		std::cout << "-----------------------------------------------" << std::endl;
		damageDone += player->UseAbility(abilityChoice);
		std::cout << "-----------------------------------------------" << std::endl;
	} while (player->AbilityFailed());
	enemy->TakeDamage(damageDone);
	std::cout << "-----------------------------------------------" << std::endl;
}

void Battle::EnemyTurn(Handle<PlayerCharacterBase> &player)
{
	std::cout << "-----------------------------------------------" << std::endl;
	std::size_t damageDone = enemy->UseAbility();
	std::cout << "-----------------------------------------------" << std::endl;
	player->TakeDamage(damageDone);
	std::cout << "-----------------------------------------------" << std::endl;
}

void Battle::EndBattle(Handle<PlayerCharacterBase> &player)
{
	if(enemy->EnemyIsDead())
	{
		AwardExp(player);
		AwardGold(player);
	}
	else
	{
		std::cout << "You have been defeated!" << std::endl;
		std::cout << "GAME OVER" << std::endl;
	}
}