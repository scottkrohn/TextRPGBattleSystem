#ifndef ENEMYCLASSES_H_
#define ENEMYCLASSES_H_
#include <string>
#include <iostream>
class EnemyBase
{
	static const std::size_t BASE_MAX_HIT_POINTS = 100;
	static const std::size_t BASE_EXP_VALUE = 75;
	static const std::size_t BASE_ATTACK_POWER = 10;
	static const std::size_t MAX_ENEMY_LEVEL = 10;
	static const std::size_t BASE_ENEMY_LEVEL = 1;
	static const std::size_t DAMAGE_VARIANCE_PERCENT = 30;
	static const std::size_t BASE_GOLD_VALUE = 25;
public:
	EnemyBase(const std::string name);
	EnemyBase(const std::size_t lvl,const std::string name);
	virtual ~EnemyBase() {}
	bool EnemyIsDead() const;
	std::size_t EnemyExpValue() const;
	std::size_t EnemyLevel() const;
	std::string ReturnName() const;
	std::size_t EnemyGoldValue() const;
	void GainHitPoints(const std::size_t hitPointsGained);
	std::size_t UseAbility();
	virtual void TakeDamage(const std::size_t damageTaken);
	// BasicAttack is based on attack power and the same for each enemy type
	std::size_t BasicAttack();
	virtual std::size_t AbilityOne() {return 0;}
	virtual std::size_t AbilityTwo() {return 0;}
	virtual std::size_t AbilityThree() {return 0;}
	virtual void DisplayHitPoints() const;
	virtual void Debug() const;
protected:
	std::size_t currentHitPoints;
	std::size_t maxHitPoints;
	std::size_t level;
	std::size_t attackPower;
	std::size_t expValue;
	std::size_t goldValue;
private:
	std::string enemyName;
	bool isDead;
};

// Normal Enemy Classes
// Wyvern will be the easiest enemy to defeat
class WyvernEnemy: public EnemyBase
{
public:
	WyvernEnemy(const std::string name = "Wyvern");
	WyvernEnemy(const std::size_t lvl, const std::string name);
	std::size_t AbilityOne();
	std::size_t AbilityTwo();
	std::size_t AbilityThree();
private:
};

// Goblin will be the median enemy
class GoblinEnemy: public EnemyBase
{
public:
	GoblinEnemy(const std::string name = "Goblin");
	GoblinEnemy(const std::size_t lvl, const std::string name);
	std::size_t AbilityOne();
	std::size_t AbilityTwo();
	std::size_t AbilityThree();
private:
};

// Wight will be the hardest enemy to defeat
class WightEnemy: public EnemyBase
{
public:
	WightEnemy(const std::string name = "Wight");
	WightEnemy(const std::size_t lvl, const std::string name);
	std::size_t AbilityOne();
	std::size_t AbilityTwo();
	std::size_t AbilityThree();
private:
};

// Boss Classes

class BossNergal: public EnemyBase
{
	static const std::size_t NERGAL_BASE_HIT_POINTS = 1000;
	static const std::size_t NERGAL_EXP_VALUE = 250;
	static const std::size_t NERGAL_GOLD_VALUE = 400;
public:
	BossNergal(const std::string name = "Nergal");
	BossNergal(const std::size_t lvl, const std::string name);
	std::size_t AbilityOne();
	std::size_t AbilityTwo();
	std::size_t AbilityThree();
};

class BossAegir: public EnemyBase
{
	static const std::size_t AEGIR_BASE_HIT_POINTS = 2000;
	static const std::size_t AEGIR_EXP_VALUE = 350;
	static const std::size_t AEGIR_GOLD_VALUE = 500;
public:
	BossAegir(const std::string name = "Aegir");
	BossAegir(const std::size_t lvl, const std::string name);
	std::size_t AbilityOne();
	std::size_t AbilityTwo();
	std::size_t AbilityThree();
};

class BossZoltan: public EnemyBase
{
	static const std::size_t ZOLTAN_BASE_HIT_POINTS = 3000;
	static const std::size_t ZOLTAN_EXP_VALUE = 450;
	static const std::size_t ZOLTAN_GOLD_VALUE = 600;
public:
	BossZoltan(const std::string name = "Zoltan");
	BossZoltan(const std::size_t lvl, const std::string name);
	std::size_t AbilityOne();
	std::size_t AbilityTwo();
	std::size_t AbilityThree();
};
#endif