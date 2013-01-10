/*
* Laura Marshall
* Project Number: 3
* Due Date: 08/24/2010
* Compiler Used: Visual Studio 2008
* File Name: project3_marshall.cpp
*/

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include <sstream>

using namespace std;

/*
Class: CEmployee
Purpose: Tracks the functions of an Employee Record in a link list.
The head node is tracked by the EmployeeManager.

*/
class CEmployee {
public:

	CEmployee() : m_Name(""), m_Age(0), m_Salary(0), m_pLink(0) {};
	~CEmployee();

	CEmployee* AddEmp(CEmployee* pHeadNode, CEmployee* NewEmployee);
	CEmployee* CEmployee::CreateUserEmp();
	CEmployee * DeleteEmp(CEmployee *pHeadPtr, string name);
	void SearchEmp(CEmployee *pHeadPtr, string name);
	bool SaveToFile(CEmployee *&pHeadPtr, char* filename);
	void ExitProg(CEmployee *pHeadPtr);
	void ListEmployees(CEmployee* pHeadPtr);

	// Display a single employee at the pCurNode
	void CEmployee::Display(CEmployee* pCurNode, int i);

	// Setters for private member data
	void SetName(const string& name) { m_Name = name; };
	void SetAge(const int& age) { m_Age = age; };
	void SetSalary(const int& salary) { m_Salary = salary; };
	void SetNext(CEmployee* nextEmp) { m_pLink = nextEmp; };

	// Getters for private member data
	string GetName() { return m_Name; };
	int GetAge() { return m_Age; };
	int GetSalary() { return m_Salary; };
	CEmployee* GetNext() { return m_pLink; };
	bool bIsGreater(int result) { if (result >= 0) return true; return false; };

	// helper for ListEmployees
	string FormatThousands(int thousands);

private:
	string m_Name;
	int m_Age;
	int m_Salary;
	CEmployee *m_pLink;
};

/********************************************************************
* FUNCTION: SaveToFile *
* PURPOSE: Save the Employee Linked List to a file.
* PARAMETERS: pHeadNode, filename
***********************************************************************/
bool CEmployee::SaveToFile(CEmployee *&pHeadNode, char *filename){

	CEmployee* pCurNode = pHeadNode;

	ofstream OutFile(filename);

	if (!OutFile) {
		cout << "Cannot open file!" << endl;
		return 1;
	}

	int i = 0;

	while(pCurNode != 0){
		OutFile << pCurNode->GetName();
		OutFile << ";";
		OutFile << pCurNode->GetAge();
		OutFile << ";";
		OutFile << pCurNode->GetSalary();
		OutFile << "\n";

		pCurNode = pCurNode->GetNext();
		i++;
	}

	OutFile.close();

	return true;

}

/********************************************************************
* FUNCTION: ExitProg *
* PURPOSE: deletes memory spaces that were being *
* used. *
* PARAMETERS: pHeadNode *
* LOCAL VARIABLES: pCurr, pDeleteThisNode *
***********************************************************************/
void CEmployee::ExitProg (CEmployee *pHeadNode)
{
	CEmployee *pCurr, *pDeleteThisNode;
	pCurr = pHeadNode;
	while ( pCurr != 0)
	{
		pDeleteThisNode = pCurr;
		pCurr = pCurr->m_pLink;
		delete pDeleteThisNode;
	}
}


CEmployee::~CEmployee()
{
}


/********************************************************************
* FUNCTION: FormatThousands
* PURPOSE: Converts the number to a string. If number is in the
* thousands, insert ','.
* PARAMETERS: number
* RETURN: A string formatted for the display in thousands.
***********************************************************************/
string CEmployee::FormatThousands(int number) {

	/* the converted string */
	string number_to_string;

	/* Convert the number by reading it into a stream
	and sending it out as a string with str() */
	stringstream out;
	out << number;
	number_to_string = out.str();

	if (number > 999.99){
		/* the formatted string to return */
		string formatted = "";

		string::const_iterator it = number_to_string.begin();

		int string_len = number_to_string.length();
		int count = string_len;
		while ( it != number_to_string.end() )
		{
			if ( count < string_len && (count % 3  == 0 )) {
				formatted.push_back(',');
			}
			formatted.push_back(*it);

			count--;
			it++;
		}
		return formatted;
	}

	return number_to_string;

}

/********************************************************************
* FUNCTION: Display
* PURPOSE:  displays a single employee record to the screen.
* PARAMETERS: pHeadNode - the head node, int i - the number of this employee.
***********************************************************************/
void CEmployee::Display(CEmployee* pCurNode, int i) {

	if (pCurNode != 0) {
		cout << i << ". \t";
		cout << setw(20) << setfill(' ') << pCurNode->GetName();
		cout << "\t" << pCurNode->GetAge();
		cout << "\t" << FormatThousands(pCurNode->GetSalary()) << endl;
	}
}

/********************************************************************
* FUNCTION: ListEmployees
* PURPOSE:  displays the employee records to the screen.
* PARAMETERS: pHeadNode - the head node
***********************************************************************/
void CEmployee::ListEmployees(CEmployee* pHeadNode) {
	CEmployee* pCurNode = pHeadNode;


	cout << "# \t\tEmployee Name\tAge\tSalary" << endl;
	cout << "=============================================" << endl;

	int i = 0;

	while(pCurNode != 0){
		Display(pCurNode, i);
		pCurNode = pCurNode->GetNext();
		i++;
	}
}

/********************************************************************
* FUNCTION: SearchEmp
* PURPOSE: Does a linear search through the link list by employee name
* and displays the employee record to the screen.
* PARAMETERS: pHeadNode - the head node
*			  name - the Employee Name to search
***********************************************************************/
void CEmployee::SearchEmp(CEmployee* pHeadNode, string name) {

	CEmployee* pCurNode = pHeadNode;
	int i = 0;
	while(pCurNode != 0) {
		if (strcmp(name.c_str(), pCurNode->GetName().c_str()) == 0) {
			cout << "Found Employee:";
			pCurNode->Display(pCurNode, i);
			return;
		}

		pCurNode = pCurNode->GetNext();
		i++;
	}
	cout << "Employee Not found: " << name << endl;
}

/********************************************************************
* FUNCTION: DeleteEmp
* PURPOSE: Delete an Employee by name from the link list.
* PARAMETERS: pHeadPtr - the head node
*			  name - the Employee Name to delete
* RETURN: CEmployee* - the head node.
***********************************************************************/
CEmployee* CEmployee::DeleteEmp(CEmployee* pHeadPtr, string name){

	CEmployee* pCurNode = pHeadPtr;

	// Temporary node holds the current node to delete it
	CEmployee* pDeleteThisNode = 0;

	CEmployee* pPrevNode = 0;

	while(pCurNode != 0) {

		if (strcmp(name.c_str(), pCurNode->GetName().c_str()) == 0) {

			pDeleteThisNode = pCurNode;
			pCurNode = pCurNode->GetNext();

			if (!pPrevNode) {
				// No previous node so pCurNode is the new head
				pHeadPtr = pCurNode;
			} else {
				pPrevNode->SetNext(pCurNode);
			}

			delete pDeleteThisNode;
			return pHeadPtr;
		}
		pPrevNode = pCurNode;
		pCurNode = pCurNode->GetNext();
	}
	cout << "Employee Not found to delete: " << name << endl;
	return pHeadPtr;
}

/***********************************************************************
* FUNCTION: AddEmp
* PURPOSE: Adds a new employee in the linked list alphabetically by name.
* PARAMETERS: pHeadNode - head node of the linked list.
			  pNewNode - new node to add to the linked list.
* PRECONDITION: pNewNode's next is initialized to null and is a valid CEmployee.
***********************************************************************/
CEmployee* CEmployee::AddEmp (CEmployee* pHeadNode, CEmployee* pNewNode) {
	CEmployee* pCurNode = pHeadNode;
	CEmployee* pPreviousNode = 0;
	int compare_current = 0;

	// The linked list is empty so add the NewNode to the head
	if (!pCurNode) {
		pHeadNode = pNewNode;
		pCurNode = pNewNode;
	} else {

		/* while the new node is less that the current node */
		while ( pCurNode != 0 ) {

			/* Do a comparison between string 1 = pNewNode & string 2 = pCurNode
			returns > 0 if new node is greater than current node, bIsGreater is true*/
			compare_current = strcmp( pNewNode->GetName().c_str(), pCurNode->GetName().c_str() );

			if ( bIsGreater(compare_current) ) {

				/* At the end of the linked list so add new node */
				if (!pCurNode->GetNext()) {
					pCurNode->SetNext(pNewNode);
					/* pNewNode next is initialized to null*/
					pCurNode = pNewNode;
				}

			} else {

				if (pPreviousNode) {
					pPreviousNode->SetNext(pNewNode);
					pNewNode->SetNext(pCurNode);
				} else {
					/* At the head of the linked list so add new node before HeadNode */
					pNewNode->SetNext(pHeadNode);
					pHeadNode = pNewNode;
					return pHeadNode;
				}
			}
			pPreviousNode = pCurNode;
			pCurNode = pCurNode->GetNext();
		}

	}

	return pHeadNode;
}



/***********************************************************************
* FUNCTION: CreateUserEmp
* PURPOSE: Creates a new employee from user input.
* PARAMETERS: None
* RETURN: A new Employee with the next node initialized to null.
***********************************************************************/
CEmployee* CEmployee::CreateUserEmp()
{
	string name_str;
	string first;
	string last;
	int age;
	int salary;

	CEmployee* new_employee = new CEmployee();
	cout << "\nEnter Employee First Name: ";
	cin >> first;
	cout << "\nEnter Employee Last Name: ";
	cin >> last;
	cout << "\nEnter Employee's Age: ";
	cin >> age;
	cout << "\nEnter Employee's Salary: ";
	cin >> salary;
	name_str.append(first);
	name_str.push_back(' ');
	name_str.append(last);
	new_employee->SetName(name_str);
	new_employee->SetAge( age );
	new_employee->SetSalary( salary );
	new_employee->SetNext(0);

	return new_employee;
}

/***********************************************************************
* CLASS: EmployeeFileManager
* PURPOSE: Manages the EmployeeFile and linked list of employees.
* Tracks the head node of the CEmployee linked list with pHeadNode
***********************************************************************/
class EmployeeFileManager{

public:

	/* Used for parsing a line in the EmployeeFile */
	enum EParseState { NAME, AGE, SALARY };

	enum EUserCommand{ ADD, DELETE, SEARCH, SAVE, LIST, QUIT, INVALID};
	EmployeeFileManager();
	~EmployeeFileManager();

	/* Read the m_EmployeeFile file and calls GetNextEmployeeFromFile */
	bool ReadFile(char* filename);
	void SetEmployeeFile(char* filename) { m_EmployeeFile = filename; };
	char* GetEmployeeFile() { return m_EmployeeFile; };

	void ProcessUserInput();

	/*Get the Employee from a line in the m_EmployeeFile*/
	CEmployee* GetNextEmployeeFromFile(const string& line);


	EUserCommand GetUserCommand(int& user_input);
private:
	CEmployee* m_pHeadNode;
	char* m_EmployeeFile;
};

EmployeeFileManager::EmployeeFileManager(): m_pHeadNode(0), m_EmployeeFile(0)
{
}

EmployeeFileManager::~EmployeeFileManager()
{
}



/***********************************************************************
* FUNCTION: EmployeeFileManager::ReadFile
* PURPOSE: Reads the file and calls CEmployee::AddEmp to add a new Employee
* to the linked list.
* PARAMETERS: filename - the name of the employee file
* RETURN: bEmployeeIsAdded - true if new employees are added,
*                            false if there are any errors
***********************************************************************/
bool EmployeeFileManager::ReadFile(char* filename) {

	ifstream infile(filename);
	SetEmployeeFile(filename);

	if (!infile){
		return false;
	}

	string line; // string to be read from the file

	// Replaces strtok, not recommended by Visual Studio 2008

	CEmployee* EmployeeWorker = new CEmployee;

	bool bEmployeeIsAdded = false;

	while ( std::getline(infile, line) ) {

		if (!infile.good()){
			return false;
		}
		m_pHeadNode = EmployeeWorker->AddEmp(m_pHeadNode, GetNextEmployeeFromFile(line));

		if (!m_pHeadNode) {
			cout << "Error Adding Employee." << endl;
			return false;
		}
	}	 //while

	return true;
}

/***********************************************************************
* FUNCTION: EmployeeFileManager::GetNextEmployeeFromFile
* PURPOSE: Parse a line containing employee information and create a new Employee.
* PARAMETERS: line - a single line from the employee file
* RETURN: CEmployee - A new employee.
***********************************************************************/
CEmployee* EmployeeFileManager::GetNextEmployeeFromFile(const string& line){

	CEmployee* next_employee = new CEmployee;

	/* Create a string iterator to tokenize line into characters */
	string::const_iterator it = line.begin();

	EParseState state = NAME;

	string name_str;
	string age_str;
	string salary_str;

	/* Iterate through line per character */
	while (it != line.end()){

		if (state==NAME) {
			if (*it == ';') {
				state=AGE;
				it++;
				continue;
			} else {

				if (isalpha(*it) || isspace(*it)) {
					name_str.push_back(*it);
				} else {
					cout << "Error parsing input line, expected a character or ;, found " << *it << endl;
					return 0;
				}
			}
		}

		if (state == AGE) {
			if (*it == ';') {
				state=SALARY;
				it++;
				continue;
			}

			if (isdigit(*it)) {
				age_str.push_back(*it);
			} else {
				cout << "Error parsing input line, expected a digit or ; but found " << *it <<  endl;
				return 0;
			}
		}

		if (state == SALARY) {
			if (isdigit(*it)) {
				salary_str.push_back(*it);
			}
		}

		/* consume the current character by incrementing the iterator */
		it++;
	}

	next_employee->SetName(name_str);
	next_employee->SetAge( atoi( age_str.c_str() ) );
	next_employee->SetSalary( atoi( salary_str.c_str() ) );
	next_employee->SetNext(0);

	return next_employee;
}


/*
Function: EmployeeFileManager::GetUserCommand
Purpose: Converts user input into a command Enum EUserCommand
Returns: EUserCommand: ADD, DELETE, SEARCH, SAVE, LIST, pr QUIT
*/
EmployeeFileManager::EUserCommand EmployeeFileManager::GetUserCommand(int& user_input) {

	if (user_input == 1) {
		return ADD;
	}

	if (user_input == 2) {
		return DELETE;
	}

	if (user_input == 3) {
		return SEARCH;
	}

	if (user_input == 4) {
		return LIST;
	}

	if (user_input == 5) {
		return SAVE;
	}

	if (user_input == 6) {
		return QUIT;
	}

	return INVALID;
}
/*
Function: EmployeeFileManager::ProcessUserInput
Purpose: Process the next command from the user.
*/
void EmployeeFileManager::ProcessUserInput() {

cout << "Menu Options:" << endl;
cout << "1. Add Employee" << endl;
cout << "2. Delete Employee" << endl;
cout << "3. Search Employee" << endl;
cout << "4. List All Employees" << endl;
cout << "5. Save Employee Database" << endl;
cout << "6. Exit Employee Database" << endl;
cout << "Enter Your Choice:" << endl;

	bool done = false;
	int input = 0;
	CEmployee* worker = new CEmployee();

	while (!done) {
			cin >> input;

			if (!cin.good()){
				cout << "You entered an invalid choice";
				break;
			}

			EUserCommand command = GetUserCommand(input);

			if (command == ADD) {
				// add a new node then update the headnode
				m_pHeadNode = worker->AddEmp(m_pHeadNode, worker->CreateUserEmp());
			}

			if (command == SAVE) {
				worker->SaveToFile(m_pHeadNode, GetEmployeeFile());
			}

			if (command == SEARCH) {
				string first;
				string last;
				cout << "Enter Employee First name to search:" << endl;
				cin >> first;
				cout << "Enter Employee First name to search:" << endl;
				cin >> last;
				string name;
				name.append(first);
				name.push_back(' ');
				name.append(last);
				worker->SearchEmp(m_pHeadNode, name);
			}

			if (command == DELETE) {
				string first;
				string last;
				cout << "Enter Employee First name to delete:" << endl;
				cin >> first;
				cout << "Enter Employee First name to delete:" << endl;
				cin >> last;
				string name;
				name.append(first);
				name.push_back(' ');
				name.append(last);
				// delete then update the m_pHeadNode
				m_pHeadNode = worker->DeleteEmp(m_pHeadNode, name);
			}

			if (command == LIST) {
				worker->ListEmployees(m_pHeadNode);
			}

			if (command == QUIT) {
				done = true;
				worker->SaveToFile(m_pHeadNode, GetEmployeeFile());
				worker->ExitProg(m_pHeadNode);
				cout << "You entered 6 to exit.  Exiting now." << endl;
			}

			if (command == INVALID) {
				cout << "You entered an invalid choice." << endl;
			}

			if (!done)
			{
				cout << "\nMenu Options:" << endl;
				cout << "1. Add Employee" << endl;
				cout << "2. Delete Employee" << endl;
				cout << "3. Search Employee" << endl;
				cout << "4. List All Employees" << endl;
				cout << "5. Save Employee Database" << endl;
				cout << "6. Exit Employee Database" << endl;
				cout << "Enter Your Choice:" << endl;
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

int main(int argc, char *argv[]){

	EmployeeFileManager* employee_reader = new EmployeeFileManager();

	if (argc == 2){
		bool bFileReadSuccess = false;
		bFileReadSuccess = employee_reader->ReadFile(argv[1]);

		if (!bFileReadSuccess){
			cout << "Error reading file." << endl;
			delete employee_reader;
			return 1;
		} else {
			cout << "Done reading Employee file." << endl;
		}
	} else {
		cout << "Error: Invalid argument." << endl;
		cout << "Usage: " << argv[0] << " <filename>" << endl;
		delete employee_reader;
		return 1;
	}

	employee_reader->ProcessUserInput();
	delete employee_reader;

	return 0;
}
