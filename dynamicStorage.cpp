/** 
 * Name: Dallon Jarman
 * Student ID: dmj296
 * Class: CYB136
 * Assignment #: 2
 * Project Name: Dynamic Name Storage
 * Purpose: The purpose of this program is to dynamically allocate memory for a user specified number of names.
*/

/**
 * RECOMMEND WAY TO COMPILE
 * g++ -std=c++11 dynamicStorage.cpp -o dynamicStorage
 * ./dynamicStorage
*/

#include <iostream>
#include <string>
#include <algorithm> // Required for the sort function
#include <map> // Required for the map data structure
#include <vector> // Required for the vector data structure
#include <iomanip> // Required for the setw function


using namespace std;


// A struct to store each person's name
struct Name {
    string name;

    // Constructor
    Name(string name = "") {
        this->name = name;
        
    }
    
    // Destructor
    ~Name() {
        // Nothing to do here, but included for completeness
    }
};

// Function prototypes
bool compareNames(Name* a, Name* b);
int findNameIndex(Name** names, int numNames, string searchName);
void addName(Name**& names, int& numNames, string name);
void deleteName(Name**& names, int& numNames, string name);
bool nameExists(Name** names, int numNames, string name);
void title();

int main() 
{
    // Initialize variables
    int numNames = 0;

    // print title
    title();

    // Prompt the user to enter the number of names to store
    cout << "How many names do you want to enter? ";
    cin >> numNames;

    // Check if the user entered a number
    while (cin.fail()) 
    {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> numNames;
    }

    // Check if the user entered a positive number
    while (numNames < 0) 
    {
        cout << "Invalid input. Please enter a positive number: ";
        cin >> numNames;
    }

    // Ignore the newline character left by cin
    cin.ignore(); 
    
    // Declare a pointer to an array of pointers to Name objects
    Name **names = nullptr; 
    
    // Try to allocate memory for the array of pointers to Name objects
    try 
    {

        // Allocate memory for the array of pointers to Name objects
        names = new Name*[numNames];
        
        // Prompt the user to enter each person's name 
        for (int i = 0; i < numNames; i++) 
        {
            names[i] = new Name; // Allocate memory for a new Name object
            cout << "Enter name " << i+1 << ": ";
            getline(cin, names[i]->name);
            
        }

        // Declare a map to store the names by category
        map<string, vector<string>> categories;

         // Prompt the user to enter the number of names to store
        int numCategory = 0;
        cout << endl;
        cout << "How many categories do you want to enter? ";
        cin >> numCategory;

        // Check if the user entered a number
        while (cin.fail()) 
        {
            // Prompt the user to enter a number
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> numCategory;
        }

        // Check if the user entered a positive number
        while (numCategory < 0) 
        {
            // Prompt the user to enter a positive number
            cout << "Invalid input. Please enter a positive number: ";
            cin >> numCategory;
        }


        // Ignore the newline character left by cin
        cin.ignore(); 


        // Prompt the user to enter each category name and store it in the map
        for (int i = 0; i < numCategory; i++) 
        {
            // Prompt the user to enter the category name
            string categoryName;
            cout << "Enter category name " << i+1 << ": ";
            getline(cin, categoryName);

            // Add the category name to the map
            categories[categoryName] = vector<string>();
        }

        // Prompt the user to enter each person's category
        for (int i = 0; i < numNames; i++) 
        {
            // Loop through the map and prompt the user to enter the category value
            for (auto& category : categories) 
            {
                // Prompt the user to enter the category value
                cout << category.first << " for " << names[i]->name << ": ";
                string categoryValue;
                getline(cin, categoryValue);

                // Add the category value to the vector
                category.second.push_back(categoryValue);

            }
        }

        // print endline
        cout << endl;
        int choice = 0;
       

        while (choice != 7) 
        {
            cout << "Please enter a your next steps ( 1 - 7 )" << endl;
            cout << "1. Add a name " << endl;
            cout << "2. Delete a name " << endl;
            cout << "3. Add a category " << endl;
            cout << "4. Delete a category " << endl;
            cout << "5. Print the list " << endl;
            cout << "6. Search for a name" << endl;
            cout << "7. Exit" << endl;

            // Prompt the user to enter their choice
            cout << "Enter your choice: ";
            cin >> choice;
            cout << endl;

            // check if the user entered a number
            while (cin.fail()) 
            {
                // Prompt the user to enter a number
                cout << "Invalid input. Please enter a number: ";
                cin.clear();
                cin.ignore(256, '\n');
                cin >> choice;
            }

            // Check if the user entered a number within the range
            while (choice < 1 || choice > 7) 
            {
                // Prompt the user to enter a number within the range
                cout << "Invalid input. Please enter a number between 1 and 8: ";
                cin >> choice;
            }

                string searchName;
                int nameWidth = 20;
                int categoryWidth = 15;

            switch (choice) 
            {
                case 1:
                    // Add a name
                    // Prompt the user to enter the name
                    
                    cout << "Enter a name: ";
                    cin >> searchName;

                    // Add the name to the array of pointers to Name objects
                    addName(names, numNames, searchName);

                    // Prompt the user to enter the category values
                    for (auto& category : categories) 
                    {
                        // Prompt the user to enter the category value
                        cout << category.first << " for " << names[numNames - 1]->name << ": ";
                        string categoryValue;
                        //clear cin
                        cin.clear();
                        cin.ignore(256, '\n');

                        cin >> categoryValue;

                        // Add the category value to the vector
                        category.second.push_back(categoryValue);
                    }

                    // print endline
                    cout << endl;

                    break;
                
                case 2:
                    // Delete a name
                    // Prompt the user to enter the name
                    cout << "Enter a name: ";
                    cin >> searchName;

                    // Check to see if the name exists
                    if (!nameExists(names, numNames, searchName)) 
                    {
                        // Prompt the user to enter a different name
                        cout << "Name does not exist. Please enter a different name: ";
                        cin >> searchName;
                    }

                    // Delete the name from the array of pointers to Name objects
                    deleteName(names, numNames, searchName);

                    // Delete the category values from the map
                    for (auto& category : categories) 
                    {
                        // Delete the category value from the vector
                        category.second.pop_back();
                    }

                    // print endline
                    cout << endl;

                    break;

                case 3:
                    // Add a category
                    // Prompt the user to enter the category name
                    cout << "Enter category name: ";
                    cin >> searchName;

                    // Check to see if category already exists
                    if (categories.find(searchName) != categories.end()) 
                    {
                        // Prompt the user to enter a different category name
                        cout << "Category already exists. Please enter a different category name: ";
                        cin >> searchName;
                    }

                    // Add the category name to the map
                    categories[searchName] = vector<string>();

                    // Prompt the user to enter the category values
                    for (int i = 0; i < numNames; i++) 
                    {
                        // Prompt the user to enter the category value
                        cout << searchName << " for " << names[i]->name << ": ";
                        string categoryValue;
                        cin >> categoryValue;

                        // Add the category value to the vector
                        categories[searchName].push_back(categoryValue);
                    }

                    // print endline
                    cout << endl;

                    break;
                
                case 4:
                    // Delete category
                    // Prompt the user to enter the category name
                    cout << "Enter category name: ";
                    cin >> searchName;

                    // Check to see if category already exists
                    if (categories.find(searchName) != categories.end()) 
                    {
                        // Delete the category name from the map
                        categories.erase(searchName);

                        // print endline
                        cout << endl;
                    }

                    break;
                    
                case 5:
                    
                    // initalize variables
                     
                    // Print the header row
                    cout << setw(nameWidth) << left << "Name";
                    for (auto& category : categories) 
                    {
                        cout << setw(categoryWidth) << left << category.first;
                    }

                    // prints endline
                    cout << endl;

                    // Print a line of equals under the header row
                    for (int j = 0; j < nameWidth + categoryWidth * categories.size(); j++) 
                    {
                        cout << "=";
                    }

                    // prints endline
                    cout << endl;

                    // Print the data rows
                    for (int i = 0; i < numNames; i++) 
                    {
                        // Print the name
                        cout << setw(nameWidth) << left << names[i]->name;

                        // Print the category values
                        for (auto& category : categories) 
                        {
                            cout << setw(categoryWidth) << left << category.second[i];
                        }

                        // print endline
                        cout << endl;

                        // Print a line of dashes under the row
                        for (int j = 0; j < nameWidth + categoryWidth * categories.size(); j++) 
                        {
                            cout << "-";
                        }

                        // print endlineKe
                        cout << endl;
                    }
                    break;

                case 6:
                    // Allow the user to search for a specific name
                    cout << "Enter a name to search for: ";
                    cin >> searchName;

                    // Search for the name using the find_if function
                    Name* foundName = nullptr;

                    // Search for the name
                    for (int i = 0; i < numNames; i++) 
                    {
                        if (names[i]->name == searchName) 
                        {
                            foundName = names[i];
                            break;
                        }
                    }
                    // Display the name if it was found
                    if (foundName != nullptr) 
                    {
                        cout << "Found " << foundName->name << endl;
                        cout << endl;
                    }
                    else 
                    {
                        cout << "Name not found" << endl;
                        cout << endl;
                    }

                    // Allow the user to search for a specific name
                    int index = findNameIndex(names, numNames, searchName);

                    // Display the name if it was found
                    if (index != -1) 
                    {
                        // print the name
                        cout << "Name: " << names[index]->name << endl;

                        // print the category values
                        for (auto& category : categories) 
                        {
                            cout << category.first << ": " << category.second[index] << endl;
                        }
                    } 
                    else 
                    {
                        cout << "The name " << searchName << " was not found" << endl;
                    }

                    // print endline
                    cout << endl;

                    break;
            }
        }

        // Display a goodbye message
        cout << "Goodbye!" << endl;

        // Free the memory allocated for the Name objects
        for (int i = 0; i < numNames; i++) 
        {
            delete names[i];
        }
        delete[] names;
    }

    // Catch any exceptions thrown by the new operator
    catch (bad_alloc &ex) 
    { 
        // Display an error message and free any memory that was allocated
        cout << "Memory allocation failed: " << ex.what() << endl;

        // Free the memory allocated for the array of pointers to Name objects
        for (int i = 0; i < numNames; i++) 
        {
            delete names[i]; 
        }
        delete[] names; 
    }

    // End program
        // Return SUCCESS
    return 0;
}

/* Create functions: */

// A function to compare two Name objects by their names
bool compareNames(Name* a, Name* b) 
{
    return a->name < b->name;
}

int findNameIndex(Name** names, int numNames, string targetName) {
    for (int i = 0; i < numNames; i++) {
        if (names[i]->name == targetName) {
            return i;
        }
    }
    // Name not found
    return -1;
}

// addName function:
void addName(Name**& names, int& numNames, string name) 
{
    // Create a new Name object
    Name* newName = new Name;
    newName->name = name;

    // Create a new array of pointers to Name objects
    Name** newNames = new Name * [numNames + 1];

    // Copy the pointers from the old array to the new array
    for (int i = 0; i < numNames; i++) 
    {
        newNames[i] = names[i];
    }

    // Add the pointer to the new Name object to the new array
    newNames[numNames] = newName;

    // Delete the old array
    // What language feautre does this misuse
    // of the delete operator use?
    delete[] names;

    // Update the names array to point to the new array
    names = newNames;

    // Update the number of names
    numNames++;
}



// deleteName function:
void deleteName(Name**& names, int& numNames, string name) 
{
    // Find the index of the name
    int index = findNameIndex(names, numNames, name);

    // Check if the name was found
    if (index != -1) 
    {
        // Delete the Name object
        delete names[index];

        // Create a new array of pointers to Name objects
        Name** newNames = new Name * [numNames - 1];

        // Copy the pointers from the old array to the new array
        for (int i = 0; i < index; i++) 
        {
            newNames[i] = names[i];
        }
        for (int i = index + 1; i < numNames; i++) 
        {
            newNames[i - 1] = names[i];
        }

        // Delete the old array
        delete[] names;

        // Update the names array to point to the new array
        names = newNames;

        // Update the number of names
        numNames--;
    }
}

// nameExists function:
bool nameExists(Name** names, int numNames, string name) 
{
    // Find the index of the name
    int index = findNameIndex(names, numNames, name);

    // Check if the name was found
    if (index != -1) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void title()
{
    cout << endl;
    cout << "Name List" << endl;
    cout << "=========" << endl;
    cout << endl;
}