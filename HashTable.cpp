/*
  Choy, Oscar
  CS A200
  February 11, 2016

  This is an implementation of a hash table, built on an array.
  
 */

#include "HashTable.h"

/*
	Overloaded instream operator
	This is a friend function that prints out the table in the following format:

		Index 0: (value is displayed, or "E" to indicate is empty)
		Index 1: (value is displayed, or "E" to indicate is empty)
		...		 (other indices are displayed)
		Index 9: (value is displayed, or "E" to indicate is empty)
		Index 10: (value is displayed, or "E" to indicate is empty)
*/
ostream& operator<<(ostream& out, const HashTable& hTable) {
	
	for (int i = 0; i < hTable.capacity; i++) {
		out << "Index " << i << ": ";

		if (hTable.table[i] == -1) {
			out << "E" << endl;
		} else {
			out << hTable.table[i] << endl;
		}
	}

	return out;

}

/*
	Default constructor
	The function initializes the hash table to capacity 11 (which is already set as a constant), 
	the number of elements to 0, and creates a dynamic array of integers. In addition, the constructor 
	will populate each index of the array with - 1, to indicate that slots are available.
*/
HashTable::HashTable() {

	numOfElements = 0;
	capacity = CAPACITY;

	table = new int[capacity];

	for (int i = 0; i < capacity; i++) {
		table[i] = -1;
	}
}

/*
	Overloaded constructor
	The function initializes the hash table to a given capacity, the number of elements to 0, and 
	creates a dynamic array of integers. In addition, the constructor will populate each index of
	the array with -1, to indicate that slots are available.
*/
HashTable::HashTable(int givenCap) {
	numOfElements = 0;
	capacity = givenCap;

	table = new int[capacity];

	for (int i = 0; i < capacity; i++) {
		table[i] = -1;
	}
}
/*
	Copy constructor
	The function creates a new hash table and copies all the elements from the hash 
	table passed as a parameter into the newly created hash table.
*/
HashTable::HashTable(const HashTable& otherTable) {
	numOfElements = otherTable.numOfElements;
	capacity = otherTable.capacity;

	table = new int[capacity];

	for (int i = 0; i < capacity; i++) {
		table[i] = otherTable.table[i];
	}

}

/*
	Function insert
	The function will call the function hashValue to find the index where the key 
	should be inserted and insert the key. The function uses linear probing to handle 
	collisions. If the table is full, the function outputs the error message,
	"Table is full. Cannot insert."
*/
void HashTable::insert(int hashKey) {

	int index = hashValue(hashKey, 0);
	int start = index;
	bool inserted = false;

	do {
		if (table[index] == -1) {
			table[index] = hashKey;
			inserted = true;
		} else {
			index++;
			if (index == capacity) {
				index = 0;
			}
		}
	} while ((index != start) && (!inserted));
	
	if (!inserted) {
		cerr << "Table is full. Cannot insert." << endl;
	}
}

/*
	Function search
	The function returns true if the item is found, and false otherwise. 
	The function will stop if either of these things happens:
			- it has gone once around the whole array
			- if finds an empty slot
			- it finds the key
*/
bool HashTable::search(int hashKey) const { 
	bool found = false;
	bool endSearch = false;
	int index = hashValue(hashKey, 0);
	int startInd = index;

	do {
		if (table[index] == hashKey) {
			endSearch = true;
			found = true;
		} else if (table[index] == -1) {
			endSearch = true;
		} else {
			index++;
			if (index == capacity) {
				index = 0;
			}
		}
	} while ((!endSearch) && (index != startInd));

	return found;
}

/*
	Function getCapacity 
	The function returns the capacity of the table.
*/
int HashTable::getCapacity() const {
	return capacity;
}

/*
	Overloaded assignment operator
*/
HashTable& HashTable::operator=(const HashTable& otherTable) {
	if (this != &otherTable) {
		if (capacity != otherTable.capacity) {
			delete[] table;
			table = new int[otherTable.capacity];

			capacity = otherTable.capacity;
		}

		numOfElements = otherTable.numOfElements;

		for (int i = 0; i < capacity; i++) {
			table[i] = otherTable.table[i];
		}

	} else {
		cerr << "Attempted assignment to itself." << endl;
	}

	return *this;
}

/*
	Overloaded subscript operator
	The function returns the value at a specific index in the hash table.

*/
int HashTable::operator[](int index) const {
	return table[index];
}

/*
	Destructor
	The function deletes the dynamic table from memory and resets 
	the pointer to NULL.
*/
HashTable::~HashTable() {
	delete[] table;
	table = NULL;
}

/*
	Function hashValue
	The function is a private function that returns the hash value given by the formula

	h(key) = key % n
*/
int HashTable::hashValue(int key, int j) const {

	return ((key + (j * STEPSIZE)) % capacity);
}