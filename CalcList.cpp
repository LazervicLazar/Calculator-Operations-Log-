// Including the header file with classes that inherited from the abstract class.
#include "CalcList.hpp"
using namespace std;
double global_total = 0;
int position = 1;
// Calc List constructor.
CalcList::CalcList() : header_p(NULL) {}
// Calc List destructor
CalcList::~CalcList() {
	while (!empty())
		removeLastOperation();
}
// Function that checks if the list is empty.
bool CalcList::empty() const {
	return header_p == NULL;
}
// Function that checks if the list has one element.
bool CalcList::single_node_check() const {
	return header_p != NULL && header_p->next == NULL;
}
// Function that returns the running total.
double CalcList::total() const {
	return global_total;
}
// Function that adds a new operation to the linked list.
void CalcList::newOperation(const FUNCTIONS func, const double operand) {
// Check if the divison by 0 has occured.
    if (func == DIVISION && operand == 0) {
        throw ("Division by zero is not allowed.\n");
    }
    // Declaring a new total that will be saved into the new node.
	double newnode_total=0;
// Switch statement that uses the operation to calculate the new local and global total.
	switch (func){
		// Case if addition is the operation.
	case ADDITION:
		newnode_total = global_total + operand;
		global_total = newnode_total;
		break;
		// Case if subtraction is the operation.
	case SUBTRACTION:
		newnode_total = global_total - operand;
		global_total = newnode_total;
		break;
		// Case if multiplication is the operation.
	case MULTIPLICATION:
		newnode_total = global_total * operand;
		global_total = newnode_total;
		break;
		// Case if division is the operation.
	case DIVISION:
		newnode_total = global_total / operand;
		global_total = newnode_total;
		break;
	default:
		cout << "Invalid operation selected";
		return;
	}
	// Checking if the list is empty. Therefore, the new operation is the first node.
	if (empty()) {
		CalcN* newnode = new CalcN;
		newnode->next = NULL;
		newnode->operand = operand;
		newnode->operation = func;
		header_p = newnode;
		newnode->position = 1;
        position++;
		newnode->total = newnode_total;
	}
	// Else the node is added normally to the begining of the list and all the elements are assigned accordingly.
	else {
		CalcN* newnode = new CalcN;
		newnode->next = header_p;
		newnode->operand = operand;
		newnode->operation = func;
		header_p = newnode;
		position++;
		newnode->position = position;
		newnode->total = newnode_total;
	}
}
// Function that removes the last node.
void CalcList::removeLastOperation() {
	// Checking if the list is empty and throwing if it is.
	if (empty())
		throw("The list is empty. Operation impossible.");
	// Checking if the list has 1 element and if it does the header points to NULL.
	if (single_node_check()) {
		CalcN* last_node = header_p;
		header_p = NULL;
		delete last_node;
		position = 0;
		global_total = 0;
	}
	// Else the first node of the list is removed.
	else {
		CalcN* removed = header_p;
		header_p = removed->next;
		global_total = header_p->total;
		position--;
		delete removed;
	}
}
// Function that return a string with all the elements of nodes formatted to show what operations where done.
string CalcList::toString(unsigned short precision) const{
    
	int pos = position;
	// Declaring the string stream and string that will return.
	stringstream stream;
	string printout;
	// Setting the precision of the stream.
	stream.precision(precision);
	CalcN* cur;
    double zero = 0;
	// For loop that prints everything into the stream.
	for (cur = header_p; cur != NULL; cur = cur->next, pos--) {
		// Statement that takes care of the first node added.
		if (cur->next == NULL) {
			stream << pos << ": ";
			stream << fixed << zero;
		}
		// Statement that takes care of all the other node.
		else {
			stream << pos << ": ";
			stream << fixed << cur->next->total;
		}
		// If-else-if's that decide to print what operation.
		if (cur->operation == ADDITION) {
			stream << "+";
		}
		else if (cur->operation == SUBTRACTION) {
			stream << "-";
		}
		else if (cur->operation == MULTIPLICATION) {
			stream << "*";
		}
		else if (cur->operation == DIVISION) {
			stream << "/";
		}
		stream << cur->operand << "=" << cur->total << endl;
	}
	// Saving the stream into a string after we converted the streams content to string.
	printout = stream.str();
	// Returning the string containing all the nodes elements.
	return printout;
}

int main() {
    CalcList calcList;
    int choice;

    while (true) {
        cout << "Calculator Menu:" << endl;
        cout << "1. Add Operation" << endl;
        cout << "2. Remove Last Operation" << endl;
        cout << "3. Show Operations" << endl;
        cout << "4. Show Running Total" << endl;
        cout << "5. Quit" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1: // Add Operation
                {
                    int operation;
                    double operand;

                    cout << "Select operation:" << endl;
                    cout << "1. Addition" << endl;
                    cout << "2. Subtraction" << endl;
                    cout << "3. Multiplication" << endl;
                    cout << "4. Division" << endl;
                    cout << "Enter operation (1-4): ";
                    cin >> operation;

                    cout << "Enter operand: ";
                    cin >> operand;

                    try {
                        calcList.newOperation(static_cast<FUNCTIONS>(operation - 1), operand);
                    } catch (const char* message) {
                        cerr << message << endl;
                    }
                }
                break;

            case 2: // Remove Last Operation
                try {
                    calcList.removeLastOperation();
                    cout << "Last operation removed." << endl;
                } catch (const char* message) {
                    cerr << message << endl;
                }
                break;

            case 3: // Show Operations
                {
                    int precision;
                    cout << "Enter precision for displaying results: ";
                    cin >> precision;
                    cout << "Operations:" << endl;
                    cout << calcList.toString(precision) << endl;
                }
                break;

            case 4: // Show Running Total
                cout << "Running Total: " << fixed << setprecision(2) << calcList.total() << endl;
                break;

            case 5: // Quit
                return 0;

            default:
                cout << "Invalid choice. Please enter a valid option (1-5)." << endl;
                break;
        }
    }

    return 0;
}