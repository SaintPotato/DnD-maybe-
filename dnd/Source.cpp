#include "functions.h"

Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]
{
	{ "dragon", 'd', 15, 3, 50 },
	{ "orc", 'o', 7, 2, 25 },
	{ "slime", 's', 3, 1, 10 }
};

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем генерацию значения из диапазона
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

Monster Monster::getRandomMonster()
{
	int number = getRandomNumber(0, Monster::MAX_TYPES - 1);
	return Monster(static_cast<Type>(number));	
}

void Player::restoreHealth()
{
	(m_health + 2 > 12) ? m_health = 12 : m_health += 2;
}

void attackMonster(Player& player, Monster& monster)
{
	monster.reduceHealth(player.getDamage());
	std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage." << std::endl;
}

void attackPlayer(Player& player, Monster& monster)
{
	player.reduceHealth(monster.getDamage());
	std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage." << std::endl;
}

void fightMonster(Player& player, Monster& monster)
{
	std::cout << "\nYou have detected a " << monster.getName() << "(" << monster.getSymbol() << ")" 
		<< " with " << monster.getHealth() << " hp." <<std::endl;
	std::cout << "You have " << player.getGold() << " gold, " << player.getHealth() 
		<< " hp and " << player.getLevel() << " level." << std::endl;

	std::cout << "Press (R) for Run and (F) for Figth: ";
	char choice;
	std::cin >> choice;

	int randomNumber = getRandomNumber(0, 100);

	if (choice == 'F' || randomNumber < 50)
	{
		std::cout << "The monster has seen you! Prepare for a fight." << std::endl;
		while (player.isAlive() && monster.isAlive())
		{
			attackMonster(player, monster);

			if (!monster.isAlive()) 
			{
				std::cout << "What a fight! You killed the " << monster.getName() << ", gained "
					<< monster.getGold() << " gold, restored hp and leveled up! Congratulaitons!" << std::endl;
				player.levelUp();
				player.restoreHealth();
				continue;
			}
			
			attackPlayer(player, monster);

			if (!player.isAlive())
			{
				std::cout << "During the journey you've reached " << player.getLevel() << " and have earned "
					<< player.getGold() << " gold." << std::endl;
				std::cout << "The end was near, you only had to get " << 20 - player.getLevel()
					<< " levels, but the fortune was not on your side." << std::endl;
				std::cout << "Rest in peace, hero..." << std::endl;
			}

		}
	}
	else if (randomNumber > 50)
	{
		std::cout << "You fled successfully." << std::endl;
	}
}