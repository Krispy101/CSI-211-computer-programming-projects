#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <fstream>
using namespace std;

struct gameObject {
	string name;
	int level;
	int defence;
	int attack;
	int life;
};

void startGame(gameObject& hero, gameObject* monsters, int size);
bool fight(gameObject& hero, gameObject& monster);
void currentmonster(int m, int d);
void HeroIcon(int d);
void StinkyratIcon(int d);
void CyclopIcon(int d);
void BOSSPICKACHUIcon(int d);
void DeathIcon();

int main() {
	srand(time(0));

	//this opens the input file
	ifstream infile;
	infile.open("Character Stats.txt");

	//this detects if the file has failed to load
	if (infile.fail())
	{
		cerr << "\nError Opening File" << endl;
		exit(1);
	}
	string nameofstat;
	int statnum=0;
	string statname;
	gameObject hero;
	hero.name;
	hero.level;
	hero.defence;
	hero.attack;
	hero.life;

	infile >> nameofstat >> statname;
	hero.name = statname;

	/*
	
	Make sure to add a text file named Character Stats.txt or change the loction path in the code.

	In the file make sure to add the name first after title of stat, example file is as follows
	    Name:
		Kratos
		Level:
		20
		Defence:
		20
		Attack:
		20
		Life:
		50

       you are free to manipulate the name or stat values.

	*/
	
		while (infile)
		{
			
				infile >> nameofstat >> statnum;

				if (nameofstat == "Level:")
				{
					hero.level = statnum;

				}
				else if (nameofstat == "Defence:")
				{
					hero.defence = statnum;

				}
				else if (nameofstat == "Attack:")
				{

					hero.attack = statnum;
				}
				else if (nameofstat == "Life:")
				{

					hero.life = statnum;
				}

				
			
			
			
			
			
		}
	
	

	infile.close();

	
	

	gameObject monsters[3];

	monsters[0].name = "Stinky rat";
	monsters[0].level = 1;
	monsters[0].defence = 2;
	monsters[0].attack = 3;
	monsters[0].life = 15;

	monsters[1].name = "Cyclop";
	monsters[1].level = 3;
	monsters[1].defence = 12;
	monsters[1].attack = 21;
	monsters[1].life = 25;

	monsters[2].name = "BOSS PICKACHU";
	monsters[2].level = 5;
	monsters[2].defence = 20;
	monsters[2].attack = 35;
	monsters[2].life = 50;

		startGame(hero, monsters, 3);
		return 0;
}
int m = 0;
void startGame(gameObject& hero, gameObject* monsters, int size)
{
	bool result = false;
	int i;
	for (i = 0; i < size; i++)
	{
		m = i; 
		result = fight(hero, monsters[i]);
		if (result == true) {
			cout << "You lost fighting " << monsters[i].name << endl;
			break;
		}
	}
	if (result == false)
		cout << "You won!" << endl;

}

bool fight(gameObject& hero, gameObject& monster)
{
	int heroAttack = rand() % hero.attack + 1; // 1---15
	int monsterAttack = rand() % monster.attack + 1; // 1--3
	int l = hero.life;

	cout << endl << "Begining New Adventure..." << endl << endl;
	Sleep(5000);
	while (hero.life > 0 && monster.life > 0) {
	    if (hero.life < (l * .5))//hero is enraged
		{
			heroAttack = heroAttack * 2;
			if (heroAttack % 4 == 0)//hero lands a crit while enraged
			{
				heroAttack = heroAttack * 1.5;
				monster.life = monster.life - (heroAttack - heroAttack / 100.0 * monster.defence);
				if (monster.life < 0) monster.life = 0;
				cout << hero.name << " lands a critical attack on " << monster.name << " while enraged for " << heroAttack << " damage, " << " " << monster.name << " is stunned and has " << monster.life << " life left!" << endl << endl;
				if (monster.life <= 0) {
					DeathIcon();
				}
				else {
					currentmonster(m, heroAttack);
				}
				
				Sleep(5000);

				
			}
			else {
				monster.life = monster.life - (heroAttack - heroAttack / 100.0 * monster.defence);
				if (monster.life < 0) monster.life = 0;
				cout << hero.name << " attacks " << monster.name << " for " << heroAttack << " damage, " << " " << monster.name << " has " << monster.life << " life left!" << endl << endl;
				if (monster.life <= 0) {
					DeathIcon();
				}
				else {
					currentmonster(m, heroAttack);
				}
				Sleep(5000);
				if (monster.life > 0) 
				{
					hero.life = hero.life - (monsterAttack - monsterAttack / 100.0 * hero.defence);
					if (hero.life < 0) hero.life = 0;
					cout << monster.name << " attacks " << hero.name << " for " << monsterAttack << " damage, " << hero.name << " has " << hero.life << " life left!" << endl << endl;
					if (hero.life <= 0) {
						DeathIcon();
					}
					else {
						HeroIcon(monsterAttack);
					}
					Sleep(5000);
					if (monsterAttack % 5 == 0)
					{
						monster.life += ceil(hero.life * .15);
						hero.life -= ceil(hero.life * .15) ;
						cout << monster.name << " used life drain on " << hero.name << ", " << monster.name << " gained " << ceil(hero.life * .15) << " life!" << endl << hero.name << " lost " << ceil(hero.life * .15) << " life!" << endl << endl;
						Sleep(5000);
					}
				}
				
			}
		
		}
		else if (heroAttack % 5 == 0)//hero lands a crit
		{
			heroAttack = heroAttack * 1.5;
			monster.life = monster.life - (heroAttack - heroAttack / 100.0 * monster.defence);
			if (monster.life < 0) monster.life = 0;
			cout << hero.name << " lands a critical attack on " << monster.name << " for " << heroAttack << " damage, " << " " << monster.name << " has " << monster.life << " life left!" << endl << endl;
			if (monster.life <= 0) {
				DeathIcon();
			}
			else {
				currentmonster(m, heroAttack);
			}
			Sleep(5000);
			if (monster.life > 0) {
				hero.life = hero.life - (monsterAttack - monsterAttack / 100.0 * hero.defence);
				if (hero.life < 0) hero.life = 0;
				cout << monster.name << " attacks " << hero.name << " for " << monsterAttack << " damage, " << hero.name << " has " << hero.life << " life left!" << endl << endl;
				if (hero.life <= 0) {
					DeathIcon();
				}
				else {
					HeroIcon(monsterAttack);
				}
				Sleep(5000);
				if (monsterAttack % 5 == 0)
				{
					monster.life += ceil(hero.life * .15);
					hero.life -= ceil(hero.life * .15);
					cout << monster.name << " used life drain on " << hero.name << ", " << monster.name << " gained " << ceil(hero.life * .15) << " life!" << endl << hero.name << " lost " << ceil(hero.life * .15) << " life!" << endl << endl;
					Sleep(5000);
				}
			}
		}
		
		else {
			monster.life = monster.life - (heroAttack - heroAttack / 100.0 * monster.defence);
			if (monster.life < 0) monster.life = 0;
			cout << hero.name << " attacks " << monster.name << " for " << heroAttack << " damage, " << " " << monster.name << " has " << monster.life << " life left!" << endl << endl;
			if (monster.life <= 0) {
				DeathIcon();
			}
			else {
				currentmonster(m, heroAttack);
			}
			Sleep(5000);
			if (monster.life > 0) {
				hero.life = hero.life - (monsterAttack - monsterAttack / 100.0 * hero.defence);
				if (hero.life < 0) hero.life = 0;
				cout << monster.name << " attacks " << hero.name << " for " << monsterAttack << " damage, " << hero.name << " has " << hero.life << " life left!" << endl << endl;
				if (hero.life <= 0) {
					DeathIcon();
				}
				else {
					HeroIcon(monsterAttack);
				}
				Sleep(5000);
				if (monsterAttack % 5 == 0)
				{
					monster.life += ceil(hero.life * .15);
					hero.life -= ceil(hero.life * .15);
					cout << monster.name << " used life drain on " << hero.name << ", " << monster.name << " gained " << ceil(hero.life * .15) << " life!" << endl << hero.name << " lost " << ceil(hero.life * .15) << " life!" << endl << endl;
					Sleep(5000);
				}
			}
		}
		

		heroAttack = rand() % hero.attack + 1; // 1---15
		monsterAttack = rand() % monster.attack + 1; // 1--3
	}
	if (hero.life <= 0)
		return true;
	else
		return false;
}
void currentmonster(int m, int d)
{
	if (m==0)
	{
		StinkyratIcon(d);
	}
	else if (m == 1)
	{
		CyclopIcon(d);
	}
	else if (m == 2)
	{
		BOSSPICKACHUIcon(d);
	}
}
void HeroIcon(int d)
{

	cout << "('')/" << endl << "/|\\/" << "   -" << d << " life" << endl << "/ \\" << endl;


}
void StinkyratIcon(int d)
{
	cout << "   ? oo?___ ?  " << endl << " ? C(\")(   )S ? " << "   -" << d << " life" << endl << "    ^ ^ ^  ^  " << endl;

}
void CyclopIcon(int d)
{
	cout << " ___" << endl << "(_0_)" << endl << "//||\\\\" << endl << "  ||" << "   -" << d << " life" << endl << "//  \\\\" << endl;

}
void BOSSPICKACHUIcon(int d)
{
	cout << "         \\:.             .:/" << endl << "          \\``._________.''/" << endl << "           \\             /" <<
		endl << "   .--.--, / .':.   .':. \\" << endl << "  /__:  /  | '::' . '::' |" << endl << "     / /   |`.   ._.   .'|" << endl << "    / /    |.'         '.|" << "   -" << d << " life" <<
		endl << "   /___-_-,|.\\  \\   /  /.|" << endl << "        // |''\\.;   ;,/ '|" << endl << "        `==|:=         =:|" << endl << "           `.          .'" <<
		endl << "             :-._____.-:" << endl << "            `\'\'       `\'\'" << endl;
}

void DeathIcon()
{
	cout << "   _____" << endl << " _|     |_" << endl << "|         |" << endl << "|  R.I.P  |" << endl << "|         |" << endl << "|_________|" << endl << "XXXXXXXXXXX" << endl;

}