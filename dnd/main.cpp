#include "functions.h"

int main()
{	
	srand(static_cast<unsigned int>(time(0))); // устанавливает значение системных часов в качестве стартового числа
	rand(); // сбрасывает первый результат

	std::cout << "Welcome! Enter your name: ";
	std::string playerName;
	std::getline(std::cin, playerName);

	Player player(playerName);

	while (player.isAlive() && !player.hasWon())
	{
		Monster monster = Monster::getRandomMonster();

		fightMonster(player, monster);

		if (player.hasWon())
			std::cout << "It's been a long way, but You did it. Congratulations ( ^_^)";
	}

	return 0;
}