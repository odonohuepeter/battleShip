#pragma once
/*
Author: Peter O'Donohue
Creatoin Date: 07/11/17
Modification Date: 07/18/17
Description: FILL IN LATER
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum OrientType { north, south, east, west };

class Ship
{
public:
	Ship(OrientType, int, int);
	int getSpeed();
	int getDamage();
	int getStartRow();
	int getStartCol();
	bool flipState();
	string getType();
	OrientType getOrient();
	void move(int vel);
	virtual void getHit(Ship shipType);

protected:
	int speed;
	int length;
	int damage;
	int startRow;
	int startCol;
	bool uWater;
	string type;
	OrientType orient;
};

// Ship function definitions
Ship::Ship(OrientType orientation, int begRow, int begCol)
{
	// verify legal orientation 
	if (orientation == north || orientation == south || orientation == east || orientation == west)
	{
		orient = orientation;
		startRow = begRow;
		startCol = begCol;
	}
}

int Ship::getSpeed()
{
	return speed;
}

int Ship::getDamage()
{
	return damage;
}

int Ship::getStartRow()
{
	return startRow;
}

int Ship::getStartCol()
{
	return startCol;
}

string Ship::getType()
{
	return type;
}

bool Ship::flipState()
{
	if (type == "destroyer" || type == "carrier")
		return uWater;
	else if (uWater == false)
		uWater = true;
	else
		uWater = false;
	return uWater;
}

OrientType Ship::getOrient()
{
	return orient;
}

void Ship::move(int vel)
{
	if (vel < 0)  // if speed is set below min
		vel = 0;
	if (vel > speed)  // if speed is set above max
		vel = speed;
	// compute new start square if movement is within board bounds
	if (orient == north && (((startRow - vel) - (length - 1)) >= 1))
		startRow -= vel;
	else if (orient == south && (((startRow + vel) + (length - 1)) <= 10))
		startRow += vel;
	else if (orient == east && (((startCol + vel) + (length - 1)) <= 10))
		startCol += vel;
	else if (orient == west && (((startCol - vel) - (length - 1)) >= 1))
		startCol -= vel;
	// compute new start square if movement exceeds board bounds
	else if (orient == north && (((startRow - vel) - (length - 1)) < 1))
	{
		startRow = 1;
		orient = south;
	}
	else if (orient == south && (((startRow + vel) + (length - 1)) > 10))
	{
		startRow = 10;
		orient = north;
	}
	else if (orient == east && (((startCol + vel) + (length - 1)) > 10))
	{
		startCol = 10;
		orient = west;
	}
	else if (orient == west && (((startCol - vel) - (length - 1)) < 1))
	{
		startCol = 1;
		orient = east;
	}
}

void Ship::getHit(Ship shipType)
{
	string tempType = shipType.getType();

	if (type == "destroyer")
	{
		if (tempType == "carrier" || tempType == "sub")
			if (damage == 0)
				damage = 0;
			else
				--damage;
	}

	if (type == "carrier")
	{
		if (tempType == "destroyer" || tempType == "sub")
			if (damage == 0)
				damage = 0;
			else
				--damage;
	}
	return;
}
class Destroyer : public Ship
{
public:
	Destroyer(OrientType, int, int);
};

// Destroyer function definitions
Destroyer::Destroyer(OrientType orientation, int begRow, int begCol)
	: Ship(orientation, begRow, begCol)
{
	type = "destroyer";
	speed = 3;
	length = 3;
	damage = 4;
	uWater = false;

	// verify ship doesn't exceed the board's boundaries when placed at starting square
	if (orientation == south && (begRow + (length - 1) > 10))
		startRow = 8;
	if (orientation == north && (begRow - (length - 1)) < 1)
		startRow = 3;
	if (orientation == east && (begCol + (length - 1) > 10))
		startCol = 8;
	if (orientation == west && (begCol - (length - 1)) < 1)
		startCol = 3;
}

class Carrier : public Ship
{
public:
	Carrier(OrientType, int, int);
};

// Carrier function definitions
Carrier::Carrier(OrientType orientation, int begRow, int begCol)
	: Ship(orientation, begRow, begCol)
{
	type = "carrier";
	speed = 1;
	length = 4;
	damage = 3;
	uWater = false;

	// verify ship doesn't exceed the board's boundaries when placed at starting square
	if (orientation == south && (begRow + (length - 1) > 10))
		startRow = 7;
	if (orientation == north && (begRow - (length - 1)) < 1)
		startRow = 4;
	if (orientation == east && (begCol + (length - 1) > 10))
		startCol = 7;
	if (orientation == west && (begCol - (length - 1)) < 1)
		startCol = 4;
}

class Sub : public Ship
{
public:
	Sub(OrientType, int, int);
	bool getUwater();
	void getHit(Ship);
};

// sub function definitions
Sub::Sub(OrientType orientation, int begRow, int begCol)
	: Ship(orientation, begRow, begCol)
{
	type = "sub";
	length = 2;
	speed = 2;
	damage = 2;
	uWater = false;

	// verify ship doesn't exceed the board's boundaries when placed at starting square
	if (orientation == south && (begRow + (length - 1) > 10))
		startRow = 9;
	if (orientation == north && (begRow - (length - 1)) < 1)
		startRow = 2;
	if (orientation == east && (begCol + (length - 1) > 10))
		startCol = 9;
	if (orientation == west && (begCol - (length - 1)) < 1)
		startCol = 2;
}

// sub function definitions
bool Sub::getUwater()
{
	return uWater;
}

void Sub::getHit(Ship shipType)
{
	string tempType = shipType.getType();
	if (getUwater() == true && tempType == "carrier")
		damage = damage;
	else
	{
		if (damage == 0)
			damage = damage;
		else --damage;
	}
}

OrientType str2Orient(string dir) {
	if (dir == "north") return north;
	else if (dir == "south") return south;
	else if (dir == "east") return east;
	else return west;
}

string orient2Str(OrientType orient)
{
	if (orient == north)
		return "north";
	else if (orient == south)
		return "south";
	else if (orient == east)
		return "east";
	else
		return "west";
}

ostream & operator<<(ostream &out, Ship * ship)
{
	out << ship->getType() << " "
		<< ship->getStartRow() << " "
		<< ship->getStartCol() << " "
		<< ship->getDamage() << " "
		<< ship->getSpeed() << " "
		<< orient2Str(ship->getOrient());

	return out;
}

int main() {
	char choice;
	int numShips, shipId, vel, attackedId;
	string direction, shipType;
	int startRow, startCol;
	vector<Ship *> fleet;

	cin >> choice;
	while (choice != 'q') {
		if (choice == 'i') {// initialize
			cin >> numShips;
			fleet.resize(numShips);
			for (int i = 0; i < numShips; i++) {
				cin >> shipType >> direction >> startRow >> startCol;
				if (shipType == "destroy")
					fleet[i] = new Destroyer(str2Orient(direction), startRow, startCol);
				else if (shipType == "carry") {
					fleet[i] = new Carrier(str2Orient(direction), startRow, startCol);
				}
				else if (shipType == "sub") {
					fleet[i] = new Sub(str2Orient(direction), startRow, startCol);
				}
			}
		}
		else if (choice == 's') {// status of fleet
			for (int i = 0; i < fleet.size(); i++)
				cout << (fleet[i]) << endl;
		}
		else if (choice == 'm') { // move
			cin >> shipId >> vel;
			fleet[shipId]->move(vel);
		}
		else if (choice == 'a') { //attack
			cin >> shipId >> attackedId;
			fleet[shipId]->getHit(*fleet[attackedId]);
		}
		else if (choice == 'f') {//flip
			cin >> shipId;
			fleet[shipId]->flipState();
		}
		cin >> choice;
	}
	cout << "Hello"
	return 0;
}