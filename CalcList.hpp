// Making sure this header only gets included once.
#pragma once
// Inclusion of all the libraries needed for this project.
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "CalcListInterface.hpp"
// Declaration of the node class that contains all the information we need.
class CalcN {
private:
	int position;
	FUNCTIONS operation;
	double operand;
	double total;
	CalcN* next;
	friend class CalcList;
};
// Declaration of the list class that has the header pointer and all the functions needed for manipulations in this project.
class CalcList : public CalcListInterface {
private:
	CalcN* header_p;
public:
	//Constructor
	CalcList();
	//Destructor
	~CalcList();
	// Check if empty function.
	bool empty() const;
	// Check if list is one node long.
	bool single_node_check() const;
	// Return the total function.
    double total() const;
	// Function that adds a new operation to the linked list.
    void newOperation(const FUNCTIONS func, const double operand);
	// Function that removes the last node.
    void removeLastOperation();
	// Function that return a string with all the elements of nodes formatted to show what operations where done.
    std::string toString(unsigned short precision) const;
};