#include <iostream>
#include <string>
using namespace std;

const string filename = "inventory.txt";

/*
Program Features:
- search commodities
- insert new commodity
- delete obsolete commodities
- update commodity information (allow multipele)
- automatic change of inventory status
- deliver alerts when commodity is out of stock (error handling for too much minus)
- overflow alerts?
- stats on rate of consumption?
*/

// Struct used to hold details of all commodities.
struct commodity {
  string name; // name of commodity
  string manuf; // name of manufacturer
  int qty; // quantity of commodity
  commodity* next; // setting up linked list
} ;

// INTRODUCTORY MESSAGE & MESSAGES INDICATING USER CAN PROCEED
void intro(int x) {
  if (x == 0) { // first intro message
    cout << "// Welcome to the commodity manager! //" << endl << "\nType \"options\" to view available "
    "actions and \"help\" for further details regarding available options. Type \"exit\" "
    "to shut down the program." << endl;
  }
  cout << endl << "PLEASE INPUT YOUR SELECTED OPTION TO PROCEED: " << endl;
}

// INPUT : A command the user wishes to inquire further about
// OUTPUT : Gives further detail on the function and input style of the command.
void help(string str);

// Displays all available commands to the user.
void options() {
  cout << "Available commands are:\nsearch, insert, delete, "
  "edit, display, options, help, exit." << endl << endl;
}

// INPUT: String of any length
// RETURN: String with all alphabetical characters converted into lowercase
// Error handling in case of variance in user input
string lowercase(string str);

// INPUT : array of commodity structs, number of elements in the array
// OUTPUT : Prints out the commodities in order with accompanying details
// Purpose : used to output arrays of items to the screen for the user to see
void out_array(commodity a[], int n);

// clears any dynamically allocated memory before ending the program to prevent memory leak
void end_program(commodity* &head);

// INPUT: head of the linked list to be able to check if item already exists
// RETURN: A commodity struct with name, manufacturer, and quantity.
commodity* insert(commodity* &head);

/* Using file I/O and a reference to a 'inventory.txt' to keep track of all items even when program has been terminated
This program opens the file (or creates a new one if it doesnt exist) and creates a linked list which will be used whilst
the program runs.*/
void initialize_list(commodity* &head,string filename);

// adds item to the end of linked list
void append_item(commodity* &head, string name, string manuf, int qty);

// INPUT: pointer to the head
// RETURN: A pointer to a specified commodity, namely, with the specified name
commodity* find_by_name(commodity* &head);

void edit_item(commodity* target);

void delete_item(commodity* head, commodity* target);

int main() {
  commodity* head = NULL;
  initialize_list(head,filename);

  string option, userin;
  intro(0);

// While loop to take in user input until program end
  while (getline(cin,userin)) {
    option = lowercase(userin);
    // separate userin and option so that error messages match case with input
    if (option == "options") {
      cout << endl;
      options();
    }
    else if (option == "help") {
      cout << "Which option would you like further details on?" << endl;
      cin >> userin;
      help(userin);
      continue;
    }
    else if (option == "search") {
      // give parameters for what can be searched for - name/manuf/qty
      // error handling for user input on search (for strings only)
      // qty search is in-stock/out of stock (remember to do lowercase)
      // pass dynamically allocated array to out_array
    }
    else if (option == "display") {
      // prompt user to ask what they want to sort by - last updated (? might be difficult),
      // quantity, alphabetical name, alphabetical manufacturer
      // pass a dynamically allocated array to out_array
    }
    else if (option == "edit") {
      cout << "Please enter the name of the item you wish to edit.\n";
      commodity* target = find_by_name(head);
      edit_item(target);
    }
    else if (option == "insert") {
      commodity* new_item = insert(head); // INSERT TO BE IMPLEMENTED, ERROR HANDLING IF ITEM ALREADY EXISTS
      if (new_item -> name != "") { // EMPTY STRING RETURNED IF THE PROCESS IS CANCELLED
        append_item(head, new_item -> name, new_item -> manuf, new_item -> qty);
      }
      continue;
    }
    else if (option == "delete") {
      cout << "Please enter the name of the item you wish to delete.\n";
      commodity* target = find_by_name(head);
      cout << "Are you sure you wish to delete the item: " << target->name << "? (Y/N)\n";
      char confirm;
      cin >> confirm;
      if (confirm=='Y') {
        remove(head, target); 
      }
      else {
        cout << "Action not executed.\n";
      }
      // final promt (Y/N) - then "this item has been deleted".
    }
    else if (option == "exit") {
      cout << endl << "// Thank you for using the program, this program has now ended. //" << endl;
      end_program(head); // TO BE IMPLEMENTED
      break;
    }
    else {
      cout << userin << " is not an available command. Type 'options' to view the available commands.\n";
    }
    intro(1);
  }

  return 0;
}
