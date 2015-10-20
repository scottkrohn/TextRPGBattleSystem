#include "jobClasses.h"
#include "enemyClasses.h"
#include "nonClassFunctionsHeader.h"
#include "handleClass.h"
#include "battleSystemClass.h"
#include "weaponsClasses.h"
#include "shopClasses.h"
#include <fstream>
#include <vector>
#include <algorithm>

//int main()
//{
//	SeedRandom();
//	Archer player;
//	//player.DisplayStats();
//	BossZoltan zoltan;//(8, "Zoltan");
//	zoltan.DisplayHitPoints();
//	BossNergal nergal(4, "Nergal");
//	nergal.DisplayHitPoints();
//	BossAegir aegir(6, "Aegir");
//	aegir.DisplayHitPoints();
//	std::vector<int> damages;
//	for(int i = 0; i != 1000000; ++i)
//	{
//		damages.push_back(zoltan.UseAbility());
//	}
//	sort(damages.begin(), damages.end());
//
//	for(int i = 0; i != 200; ++i)
//	{
//		std::size_t cnt = count(damages.begin(), damages.end(), i);
//		std::cout << i << ": " << cnt << std::endl;
//	}
//	return 0;
//}

int main()
{
	SeedRandom();	// Seeds random values for entire program.
	// Create weapon shops and load inventory.
	WeaponShop staveShop;
	std::ifstream staveInputFile("staves.txt");
	staveShop.InitializeShop(staveInputFile);
	WeaponShop swordShop;
	std::ifstream swordInputFile("swords.txt");
	swordShop.InitializeShop(swordInputFile);
	WeaponShop bowShop;
	std::ifstream bowInputFile("bows.txt");
	bowShop.InitializeShop(bowInputFile);


	// Get user input to create a player character.
	std::cout << "\n----------------------------------" << std::endl;
	std::cout << "Welcome to Scott's Text Adventure!" << std::endl;
	std::cout << "----------------------------------" << std::endl;
	std::cout << "Enter your character's name: ";
	std::string characterName;
	getline(std::cin, characterName);
	std::cout << "\nChoose your class:" << std::endl;
	std::cout << "[1] Warrior -- High HP & high defense, low damage output" << std::endl
			  << "[2] Mage    -- Low HP & low defense, high damage output. " << std::endl
			  << "[3] Archer  -- Medium HP & medium defense, medium damage output." << std::endl;
	std::size_t jobChoicesCount = 3;
	int jobChoice = 0;
	std::cout << ">>";
	// While input is valid and isn't out of range for the options.
	while(!(std::cin >> jobChoice) || 0 > jobChoice || jobChoice > jobChoicesCount)
	{
		HandleInvalidInput(std::cin);
	}

	// Use input to create the player character.
	Handle<PlayerCharacterBase> playerHandle(CreatePlayerCharacter(characterName, jobChoice));
	//playerHandle->GainExp(3000);
	std::cout << "\nCharacter Information:" << std::endl;
	playerHandle->DisplayStats();
	std::cout << "\nPress enter to begin the game!" << std::endl;
	std::cin.get();
	std::cin.get();

	// Create Battle object.
	Battle battleSystem;

	// Run main program loop while player isn't dead.
	while(!playerHandle->PlayerIsDead())
	{
		if(playerHandle->ReturnLevel() % 3 == 0)
		{
			battleSystem.BossBattle(playerHandle);
		}
		else
		{
			battleSystem.RandomBattle(playerHandle);
		}
		if(!playerHandle->PlayerIsDead())
		{
			enum MenuOptions {NextBattle = 1, 
							  WeaponShop = 2, 
							  DisplayStats = 3,
							  QuitGame = 4};
			int menuChoicesTotal = 4;
			int menuChoice = 0;
			while(menuChoice != NextBattle)
			{
				std::cout << "Menu: " << std::endl;
				std::cout << "[1] Next Battle" << std::endl;
				std::cout << "[2] Weapon Shop" << std::endl;
				std::cout << "[3] Display Stats" << std::endl;
				std::cout << "[4] Quit Game" << std::endl;
				std::cout << ">> ";
				// Take user input for menu choice, check for invalid input.
				while(!(std::cin >> menuChoice) || menuChoice < 0 || menuChoicesTotal < menuChoice)
				{
					// Clear std::cin and remove extra characters from istream.
					HandleInvalidInput(std::cin);
				}
				if(menuChoice == WeaponShop)
				{
					// Check the job type of the player. This is used to 
					// determine which store the player needs to visit. 
					std::string jobType = playerHandle->JobType();
					if(jobType == "warrior")
					{
						swordShop.DisplayInventory();
						swordShop.ProcessTransaction(playerHandle);

					}
					else if(jobType == "mage")
					{
						staveShop.DisplayInventory();
						staveShop.ProcessTransaction(playerHandle);
					}
					else if(jobType == "archer")
					{
						bowShop.DisplayInventory();
						bowShop.ProcessTransaction(playerHandle);
					}
				}
				else if(menuChoice == DisplayStats)
				{
					playerHandle->DisplayStats();
					std::cout << "Press enter to continue.";
					std::cin.get();
					std::cin.get();
				}
				else if(menuChoice == QuitGame)
				{
					std::cout << "This isn't programmed yet." << std::endl;
				}
			std::cout << std::endl;
			}
		}
	}
	return 0;
}