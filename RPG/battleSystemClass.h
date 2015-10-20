// The Battle class represents a battle system. It takes a Handle<PlayerCharacterBase>
// and the creates a battle between the player and a randomly created
// enemy class object.

#ifndef BATTLESYSTEMCLASS_H_
#define BATTLESYSTEMCLASS_H_
#include "jobClasses.h"
#include "enemyClasses.h"
#include "handleClass.h"

class Battle
{
public:
	Battle();
	void RandomBattle(Handle<PlayerCharacterBase> &player);
	void BossBattle(Handle<PlayerCharacterBase> &player);
	void StartBattle(Handle<PlayerCharacterBase> &player);
private:
	void DisplayHitPoints(const Handle<PlayerCharacterBase> &player) const;
	void DisplayCombatants(const Handle<PlayerCharacterBase> &player) const;
	void CreateEnemy(const std::size_t playerLevel);
	bool PlayerAttacksFirst() const;
	bool EnemyIsDead () const;
	bool CheckAbilityEligibility(const Handle<PlayerCharacterBase> &player, 
		const std::size_t abilityChoice) const;
	void AwardExp(Handle<PlayerCharacterBase> &player);
	void AwardGold(Handle<PlayerCharacterBase> &player);
	void PlayerTurn(Handle<PlayerCharacterBase> &player);
	void EnemyTurn(Handle<PlayerCharacterBase> &player);
	void EndBattle(Handle<PlayerCharacterBase> &player);
	Handle<EnemyBase> enemy;

};
#endif