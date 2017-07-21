#pragma once
/*
Author: Peter O'Donohue
Creatoin Date: 07/11/17
Modification Date: 07/20/17
Description: Together, these four classes make up the different types of ships within the board game 
'battleship'. The derived classes titled 'Destroyer', 'Carrier', and 'Sub', inherit 'Ship's' function 
and data members. To create a ship, create an object of desired ship type, initializing it with an
orientation and starting row and column, i.e. Destroyer(north, 3, 3). The game board itslef is 10x10, and the 
constructors will auto correct any illegal starting square to the closest legal position. Once your ship's
have been created, you can retrive any data member value by calling the base class's 'get' functions.
You can also move a ship with the move function, as well as inflict damage to other ships and change a 
ship's submerged status. To move a ship, call the move function on that object, passing the desired 
movement speed through that function. You can determine a ship's maximum speed by getting 
that ship's maximum speed. If you exceed the maximum speed, the function will automatically set the current
move speed to the ship's maximum value. To inflict damage on a ship, call the getHit function by passing 
through another ship object that will serve as the attacker. Keep in mind that a submarine has the
abilitiy to submerge itself, and that only a destroyer can inflict damage on a submerged sub. To change a
sub's submerged status, call the flipState function on such an object. Important points to consider are
a ship will reverse its orientation if it moves off the board, all ship damage can't fall below zero,
and destroyers and carriers can't submerge themselves. 
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum OrientType { north, south, east, west };

// Ship class declaration
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
	/*
	PRE: object of type Ship, Destroyer, Carrier, or Sub has been declared.
	POST: object's first initialization values for orient, startRow, and startCol 
	have been set.
	*/
	orient = east;
	startRow = 1;
	startCol = 1;
}

int Ship::getSpeed()
{
	/*
	PRE: object of type Ship, Destroyer, Carrier, or sub has been initialized
	POST: object's maximum speed data member has been returned to the main function
	*/
	return speed;
}

int Ship::getDamage()
{
	/*
	PRE: object of type Ship, Destroyer, Carrier, or sub has been initialized
	POST: object's current damage data member has been returned to the main function
	*/
	return damage;
}

int Ship::getStartRow()
{
	/*
	PRE: object of type Ship, Destroyer, Carrier, or sub has been initialized
	POST: object's startRow data member has been returned to the main function
	*/
	return startRow;
}

int Ship::getStartCol()
{
	/*
	PRE: object of type Ship, Destroyer, Carrier, or sub has been initialized
	POST: object's startCol data member has been returned to the main function
	*/
	return startCol;
}

string Ship::getType()
{
	/*
	PRE: object of type Ship, Destroyer, Carrier, or sub has been initialized
	POST: object's type data member has been returned to the main function
	*/
	return type;
}
bool Ship::getUWater()
{
	/*
	PRE: object of type Ship, Destroyer, Carrier, or sub has been initialized
	POST: object's uWater data member has been returned to the main function
	*/
	return uWater;
}
bool Ship::flipState()
{
	/*
	PRE: object of type Ship, Destroyer, Carrier, or sub has been initialized
	POST: object's uWater data member has been returned to the main function
	*/
	return uWater;
}

OrientType Ship::getOrient()
{
	/*
	PRE: object of type Ship, Destroyer, Carrier, or sub has been initialized
	POST: object's orient data member has been returned to the main function
	*/
	return orient;
}

void Ship::move(int vel)
{
	/*
	PRE: object of type Ship, Destroyer, Carrier, or Sub has been initialized
	POST: object's starting square has changed and control passes back to the main funciton
	*/
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
	/*
	PRE: object of type Ship, Destroyer, Carrier, or Sub has been initialized, getHit function
	has been called on that object, getHit passes through an object of type Ship, Destroyer,
	Carrier, or Sub.
	POST: object's damage has been computed and control is passed back to the main function.
	*/
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

// Destroyer class definition
class Destroyer : public Ship
{
public:
	Destroyer(OrientType, int, int);
};

// Destroyer function definitions
Destroyer::Destroyer(OrientType orientation, int begRow, int begCol)
{
	/*
	PRE: object of type Destroyer has been declared, passing through an orientation, beginning row,
	and beginning column value.
	POST: Object's data members have been initialized, checked and or corrected to legal data values,
	and control passes back to the main function.
	*/
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

// Carrier class declaration
class Carrier : public Ship
{
public:
	Carrier(OrientType, int, int);
};

// Carrier function definitions
Carrier::Carrier(OrientType orientation, int begRow, int begCol)
{
	/*
	PRE: object of type Carrier has been declared, passing through an orientation, beginning row,
	and beginning column value.
	POST: Object's data members have been initialized, checked and or corrected to legal data values,
	and control passes back to the main function.
	*/
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

// Sub class definition
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
	/*
	PRE: object of type Sub has been declared, passing through an orientation, beginning row,
	and beginning column value.
	POST: Object's data members have been initialized, checked and or corrected to legal data values,
	and control passes back to the main function.
	*/
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

void Sub::getHit(Ship shipType)
{
	/*
	PRE: an object of type Sub has been created, getHit function called on that object,
	getHit passing through an object of any ship type
	POST: damage has been calculated and assigned to object's damage member, control
	passes back to the main function
	*/
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
	/*
	PRE: object of type Sub has been initialized, flipState function called on object
	POST: object's uWater data member has been changed, control passes back to main function
	*/
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

// unit test function declarations
bool testInitialization();
bool testMove();
bool testGetHit();
bool testFlipState();
int main()
{
	if (testInitialization())
		cout << "initialization function passed unit tests." << endl;
	if (testMove())
		cout << "move function passed unit tests." << endl;
	if (testGetHit())
		cout << "getHit function passed unit tests." << endl;
	if (testFlipState())
		cout << "flipState function passed unit tests." << endl;
	return 0;
}

// unit test function definitions

bool testInitialization()
{

	// test ship initializations when placement is within board boundaries
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
	// test ship initializations when placement exceeds board bounds
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

	// test ship initializations when starting square contains a negative value
	Destroyer aa(north, -5, 5), ab(north, 5, -5), ac(north, -5, -5);
	Carrier ad(north, -7, 7), ae(north, 7, -7), af(north, -7, -7);
	Sub ag(north, -8, 8), ah(south, 8, -8), ai(south, -8, -8);
	if (aa.getStartRow() != 3 || ab.getStartCol() != 1 || ac.getStartRow() != 3 || ac.getStartCol() != 1)
	{
		cout << "Destroyer initialization function is incorrect." << endl;
		return false;
	}
	if (ad.getStartRow() != 4 || ae.getStartCol() != 1 || af.getStartRow() != 4 || af.getStartCol() != 1)
	{
		cout << "Carrier initialization function is incorrect." << endl;
		return false;
	}
	if (ag.getStartRow() != 2 || ah.getStartCol() != 1 || ai.getStartRow() != 1 || ai.getStartCol() != 1)
	{
		cout << "sub initialization function is incorrect." << endl;
		return false;
	}
	return true;
}

bool testMove()
{
	// test move when ships remains inbounds
	Destroyer a(north, 5, 5);
	Carrier b(south, 3, 3);
	Sub c(east, 4, 5);
	a.move(2);
	b.move(1);
	c.move(2);
	if (a.getStartRow() != 3 || b.getStartRow() != 4 || c.getStartCol() != 7)
	{
		cout << "in bound movement failed." << endl;
		return false;
	}

	// test move function when speed exceeds either minimum or maximum value
	Destroyer d(north, 5, 5), e(north, 7, 4);
	Carrier f(south, 3, 3), g(south, 6, 6);
	Sub h(east, 4, 5), i(west, 3, 4);
	d.move(-1545);
	e.move(5454);
	f.move(-8543);
	g.move(15345);
	h.move(-1337);
	i.move(2434);
	if (d.getStartRow() != 5 || e.getStartRow() != 4 || f.getStartRow() != 3 || g.getStartRow() != 7
		|| h.getStartCol() != 5 || i.getStartCol() != 2)
	{
		cout << "movement function allows illegal values." << endl;
		return false;
	}

	// test move function if ship would move off board boundaries
	Destroyer j(north, 3, 4);
	Carrier k(south, 7, 5);
	Sub l(east, 9, 10);
	j.move(2);
	k.move(17);
	l.move(55);

	if ((j.getOrient() != south && j.getStartRow() != 1) || (k.getOrient() != north && k.getStartRow() != 10)
		|| (l.getOrient() != west && l.getStartCol() != 10) )
	{
		cout << "movement function fails when ship moves off board boundaries." << endl;
		return false;
	}

	return true;
}

bool testGetHit()
{
	Destroyer a(south, 5, 5);
	Carrier b(north, 6, 6);
	Sub c(east, 4, 4);
	
	// each ship is attacked by each other ship
	a.getHit(b);
	a.getHit(c);
	b.getHit(a);
	b.getHit(c);
	c.getHit(a);
	c.getHit(b);
	if (a.getDamage() != 2 || b.getDamage() != 1 || c.getDamage() != 0)
	{
		cout << "normal attack failed." << endl;
		return false;
	}

	// each ship damage taken exceeds maximum damage
	for (int i = 0; i < 5; ++i)
	{
		a.getHit(b);
		b.getHit(c);
		c.getHit(a);
	}
	if (a.getDamage() != 0 || b.getDamage() != 0 || c.getDamage() != 0)
	{
		cout << "ship(s) damage is a negative value." << endl;
		return false;
	}

	// test getHit when sub is underwater
	Destroyer d(north, 4, 4);
	Carrier e(south, 5, 5);
	Sub f(north, 7, 7);
	f.flipState();  // sets sub's uWater = true

	f.getHit(e);
	if (f.getDamage() != 2)
	{
		cout << "sub can be attacked by carrier when sub is submerged." << endl;
		return false;
	}
	f.getHit(d);
	if (f.getDamage() != 1)
	{
		cout << "sub can't be attacked by destroyer when sub is submerged." << endl;
		return false;
	}
	
}

bool testFlipState()
{
	Destroyer a(north, 4, 4);
	Carrier b(north, 5, 5);
	Sub c(east, 3, 3);

	a.flipState();
	b.flipState();
	c.flipState();

	if (a.getUWater() != false || b.getUWater() != false || c.getUWater() != true)
	{
		cout << "ship(s) uWater member is incorrect." << endl;
		return false;
	}
}
