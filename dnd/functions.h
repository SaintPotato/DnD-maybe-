#pragma once

#include <iostream>
#include <string>
#include <cstdlib> // для rand() и srand()
#include <ctime> // для time()

class Creature
{
protected:
	std::string m_name;
	char m_symbol;
	int m_health;
	int m_damage;
	int m_gold;

public:
	Creature(std::string name, char ch, int health, int damage, int gold)
		: m_name(name), m_symbol(ch), m_health(health), m_damage(damage), m_gold(gold)
	{
	}

	std::string getName() const { return m_name; };
	char getSymbol() const { return m_symbol; };
	int getHealth() const { return m_health; };
	int getDamage() const { return m_damage; };
	int getGold() const { return m_gold; };

	void reduceHealth(int dmg) { m_health -= dmg; };
	bool isAlive() { return m_health > 0; };
	void addGold(int gold) { m_gold += gold; };
};

class Player : public Creature
{
private:
	int m_level = 1;

public:
	Player(std::string name)
		: Creature(name, '@', 10, 1, 0)
	{
	}

	void levelUp() { m_level++, m_damage++; };
	void restoreHealth();
	int getLevel() const { return m_level; }
	bool hasWon()  { return m_level >= 10; }
};

class Monster : public Creature
{
public:	
	enum Type
	{
		DRAGON,
		ORC,
		SLIME,
		MAX_TYPES,
	};

	struct MonsterData
	{
		std::string name;
		char symbol;
		int health;
		int damage;
		int gold;
	};

	static MonsterData monsterData[MAX_TYPES];

	Monster(Type type) : Creature(monsterData[type].name, monsterData[type].symbol, 
		monsterData[type].health, monsterData[type].damage, monsterData[type].gold)
	{
	}

	static Monster getRandomMonster();
};

void fightMonster(Player& player, Monster& monster);