#pragma once
/*
Author: Peter O'Donohue
Creatoin Date: 07/11/17
Modification Date: 07/20/17
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
	Ship();
	int getSpeed();
	int getDamage();
	int getStartRow();
	int getStartCol();
	bool getUWater();
	string getType();
	OrientType getOrient();
	void move(int vel);
	virtual bool flipState();
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
Ship::Ship()
{
	orient = east;
	startRow = 1;
	startCol = 1;
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
bool Ship::getUWater()
{
	return uWater;
}
bool Ship::flipState()
{
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

	if (type == "Destroyer")
	{
		if (tempType == "Carrier" || tempType == "Sub")
			if (damage == 0)
				damage = 0;
			else
				--damage;
	}

	if (type == "Carrier")
	{
		if (tempType == "Destroyer" || tempType == "Sub")
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
{
	type = "Destroyer";
	speed = 3;
	length = 3;
	damage = 4;
	uWater = false;
	startRow = begRow;
	startCol = begCol;
	orient = orientation;
	// verify ship doesn't exceed the board's boundaries when placed at starting square
	if (orientation == south && ((begRow + (length - 1)) > 10))
		startRow = 8;
	if (orientation == south && begRow < 1)
		startRow = 1;
	if (orientation == south && begCol > 10)
		startCol = 10;
	if (orientation == south && begCol < 1)
		startCol = 1;
	if (orientation == north && ((begRow - (length - 1)) < 1))
		startRow = 3;
	if (orientation == north && begRow > 10)
		startRow = 10;
	if (orientation == north && begCol > 10)
		startCol = 10;
	if (orientation == north && begCol < 1)
		startCol = 1;
	if (orientation == east && ((begCol + (length - 1)) > 10))
		startCol = 8;
	if (orientation == east && begCol < 1)
		startCol = 1;
	if (orientation == east && begRow > 10)
		startRow = 10;
	if (orientation == east && begRow < 1)
		startRow = 1;
	if (orientation == west && ((begCol - (length - 1)) < 1))
		startCol = 3;
	if (orientation == west && begCol > 10)
		startCol = 10;
	if (orientation == west && begRow > 10)
		startRow = 10;
	if (orientation == west && begRow < 1)
		startRow = 1;
}

class Carrier : public Ship
{
public:
	Carrier(OrientType, int, int);
};

// Carrier function definitions
Carrier::Carrier(OrientType orientation, int begRow, int begCol)
{
	type = "Carrier";
	speed = 1;
	length = 4;
	damage = 3;
	uWater = false;
	startRow = begRow;
	startCol = begCol;
	orient = orientation;
	// verify ship doesn't exceed the board's boundaries when placed at starting square
	if (orientation == south && ((begRow + (length - 1)) > 10))
		startRow = 7;
	if (orientation == south && begRow < 1)
		startRow = 1;
	if (orientation == south && begCol > 10)
		startCol = 10;
	if (orientation == south && begCol < 1)
		startCol = 1;
	if (orientation == north && ((begRow - (length - 1)) < 1))
		startRow = 4;
	if (orientation == north && begRow > 10)
		startRow = 10;
	if (orientation == north && begCol > 10)
		startCol = 10;
	if (orientation == north && begCol < 1)
		startCol = 1;
	if (orientation == east && ((begCol + (length - 1)) > 10))
		startCol = 7;
	if (orientation == east && begCol < 1)
		startCol = 1;
	if (orientation == east && begRow > 10)
		startRow = 10;
	if (orientation == east && begRow < 1)
		startRow = 1;
	if (orientation == west && ((begCol - (length - 1)) < 1))
		startCol = 4;
	if (orientation == west && begCol > 10)
		startCol = 10;
	if (orientation == west && begRow > 10)
		startRow = 10;
	if (orientation == west && begRow < 1)
		startRow = 1;
}

class Sub : public Ship
{
public:
	Sub(OrientType, int, int);
	void getHit(Ship);
	bool flipState();
};

// sub function definitions
Sub::Sub(OrientType orientation, int begRow, int begCol)
{
	type = "Sub";
	length = 2;
	speed = 2;
	damage = 2;
	uWater = false;
	startRow = begRow;
	startCol = begCol;
	orient = orientation;
	if (orientation == south && ((begRow + (length - 1)) > 10))
		startRow = 9;
	if (orientation == south && begRow < 1)
		startRow = 1;
	if (orientation == south && begCol > 10)
		startCol = 10;
	if (orientation == south && begCol < 1)
		startCol = 1;
	if (orientation == north && ((begRow - (length - 1)) < 1))
		startRow = 2;
	if (orientation == north && begRow > 10)
		startRow = 10;
	if (orientation == north && begCol > 10)
		startCol = 10;
	if (orientation == north && begCol < 1)
		startCol = 1;
	if (orientation == east && ((begCol + (length - 1)) > 10))
		startCol = 9;
	if (orientation == east && begCol < 1)
		startCol = 1;
	if (orientation == east && begRow > 10)
		startRow = 10;
	if (orientation == east && begRow < 1)
		startRow = 1;
	if (orientation == west && ((begCol - (length - 1)) < 1))
		startCol = 2;
	if (orientation == west && begCol > 10)
		startCol = 10;
	if (orientation == west && begRow > 10)
		startRow = 10;
	if (orientation == west && begRow < 1)
		startRow = 1;
}

// sub function definitions
void Sub::getHit(Ship shipType)
{
	string tempType = shipType.getType();
	if (getUWater() == true && tempType == "Carrier")
		damage = damage;
	else
	{
		if (damage == 0)
			damage = damage;
		else --damage;
	}
}
bool Sub::flipState()
{
	if (uWater == false)
		uWater = true;
	else
		uWater = false;
	return uWater;
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
	if (ship->getUWater())
		out << " underwater";
	else
		out << " not underwater";

	return out;
}

/*
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

	return 0;
}
/*


bool testInitialization();
bool testMove();
bool testGetHit();
bool testFlipState();
int main()
{

	testInitialization();
	system("pause");
	return 0;
}

bool testInitialization()
{

	// test ship initializations
	Destroyer a(north, 3, 10), b(south, 8, 5), c(east, 7, 8), d(west, 7, 3);
	Carrier e(north, 4, 10), f(south, 7, 5), g(east, 9, 7), h(west, 3, 4);
	Sub i(north, 2, 10), j(south, 9, 5), k(east, 9, 9), l(west, 3, 2);
	if (a.getStartRow() != 3 || b.getStartRow() != 8|| c.getStartCol() != 8 || d.getStartCol() != 3)
	{
		cout << "Destroyer initialization function is incorrect." << endl;
		return false;
	}
	if (e.getStartRow() != 4 || f.getStartRow() != 7 || g.getStartCol() != 7 || h.getStartCol() != 4)
	{
		cout << "Carrier initialization function is incorrect." << endl;
		return false;
	}
	if (i.getStartRow() != 2 || j.getStartRow() != 9 || k.getStartCol() != 9 || l.getStartCol() != 2)
	{
		cout << "sub initialization function is incorrect." << endl;
		return false;
	}
	// test initializations that exceed board bounds
	Destroyer m(north, 2, 10), n(south, 9, 5), o(east, 7, 9), p(west, 7, 2);
	Carrier q(north, 3, 10), r(south, 8, 5), s(east, 9, 8), t(west, 3, 3);
	Sub u(north, 1, 10), v(south, 9, 5), w(east, 9, 9), x(west, 3, 1);
	if (m.getStartRow() != 3 || n.getStartRow() != 8 || o.getStartCol() != 8 || p.getStartCol() != 3)
	{
		cout << "Destroyer initialization function is incorrect." << endl;
		return false;
	}
	if (q.getStartRow() != 4 || r.getStartRow() != 7 || s.getStartCol() != 7 || t.getStartCol() != 4)
	{
		cout << "Carrier initialization function is incorrect." << endl;
		return false;
	}
	if (u.getStartRow() != 2 || v.getStartRow() != 9 || w.getStartCol() != 9 || x.getStartCol() != 2)
	{
		cout << "sub initialization function is incorrect." << endl;
		return false;
	}
}
