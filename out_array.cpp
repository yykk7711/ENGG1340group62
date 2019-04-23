/* This function is used to print out an array passed into it onto
the screen along with the related data of the commodity */

#include <iostream>
#include <string>
using namespace std;

// Struct used to hold details of all commodities. [FOR REFERENCE]
struct commodity {
  string name; // name of commodity
  string manuf; // name of manufacturer
  int qty; // quantity of commodity
  commodity* next // setting up linked list
} ;

void out_array(commodity a[]) {
  for (int i = 0; i < a.size(); i++) {
    cout << a[i].name << "\tManufacturer: " << a[i].manuf <<
    "\tQuantity: " << a[i].qty << endl;
  }
}
