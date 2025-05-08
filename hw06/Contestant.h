#ifndef CONTESTANT_H
#define CONTESTANT_H
#include <string>
#include "Codemon.h"
#include "Item.h"
class Map;

class Contestant
{
private:
	std::string name;
	bool isPlayer;
	int numCodemons;
	int numItems;
	Item items[20];
public:
	Codemon codemons[10];
	//default constructor that automatically prompts for the name and sets
	// numCodemons and items owned to 0
	Contestant();

	//Parameterized constructor that accepts a name as an argument and 
	// initializes numCodemons and items owned to 0
	Contestant(std::string name, bool isPlayer);

	////Copy constructor
	//Contestant(const Contestant& other);

	//Methods

	//DESC: Updates the contestant's pocket with the given codemon, checking if a 
	// codemon with the same name is already in their pocket, rejecting if so
	//PRE: The contestant and codemon should be properly initialized
	//POST: The codemon is added to the contestant's pocket if it is not already present
	void updatePocket(Codemon codemon);

	//DESC: Updates the contestant's backpack with the given item
	//PRE: The contestant and item should be properly initialized4
	//POST: The item is added to the contestant's backpack
	void updateBackpack(Item item);

	//DESC: Updates pocket and backpack contents 
	//PRE: The contestant should be properly initialized
	//POST: The contestant's pocket and backpack are updated
	void prepare();

	//DESC: Prints relevant contestant info in a formatted manner
	//PRE: The contestant should be properly initialized
	//POST: The contestant's name, number of codemons, codemons, and items are printed
	void print();

	//DESC: Prints the parts of the map visible to the contestant 
	//PRE: Contestant and map should be properly initialized
	//POST: Visible map will be printed 
	void printVisibleMap(Contestant other, Map map, Codemon activeCodemon, Codemon otherActiveCodemon) const;

	//Getter
	std::string getName() const;
	int getNumCodemons() const;
	bool getIsPlayer() const;
	//Codemon* getCodemons() const;

	friend void skillLookup(Contestant contestants[], int numContestants);
};
#endif // !CONTESTANT_H



