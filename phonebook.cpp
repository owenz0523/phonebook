#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// split method
vector<string> split(const string &s, char delim) {
  vector<string> result;
  stringstream ss(s);
  string item;

  while (getline(ss, item, delim)) {
    result.push_back(item);
  }

  return result;
}

// add contact function
vector<vector<string>> addContact(vector<vector<string>> contactList) {
  string firstName, lastName, homeNum, mobileNum;
  vector<string> contact;
  cout << "First name: ";
  cin >> firstName;
  cout << "Last name: ";
  cin >> lastName;
  cout << "Home Number: ";
  cin >> homeNum;
  cout << "Mobile Number: ";
  cin >> mobileNum;
  homeNum = "Home:" + homeNum;
  mobileNum = "Mobile:" + mobileNum;
  if (firstName == lastName) {
    cout << "Contact not allowed!" << endl;
  } else {
    contact = {firstName, lastName, homeNum, mobileNum};
    contactList.push_back(contact);
  } 
  return contactList;
}

// remove contact function
vector<vector<string>> removeContact(vector<vector<string>> contactList) {
  string firstName, lastName;
  cout << "First name: ";
  cin >> firstName;
  cout << "Last name: ";
  cin >> lastName;
  for (int i=0; i < contactList.size(); i++) {
    if (firstName == contactList[i][0] && lastName == contactList[i][1]) {
      contactList.erase(contactList.begin() + i);
      break;
    }
  }
  return contactList;
}

// view contact function
void viewContact(vector<vector<string>> contactList) {
  for (int i=0; i < contactList.size(); i++) {
    cout << "Contact #" << i + 1 << endl;
    cout << contactList[i][0] << " " << contactList[i][1] << endl;
    cout << contactList[i][2] << endl;
    cout << contactList[i][3] << endl;
    cout << "----------------------------" << endl;
  }
}

// edit contact function
vector<vector<string>>editContact(vector<vector<string>> contactList) {
  string firstName, lastName;
  cout << "First name: ";
  cin >> firstName;
  cout << "Last name: ";
  cin >> lastName;
  for (int i=0; i < contactList.size(); i++) {
    if (firstName == contactList[i][0] && lastName == contactList[i][1]) {
      cout << "1. First Name" << endl;
      cout << "2. Last Name" << endl;
      cout << "3. Home Number" << endl;
      cout << "4. Mobile Number" << endl;
      int choice;
      cout << "Choice: ";
      cin >> choice;
      string change;
      cout << "Change: ";
      cin >> change;
      if (choice == 1) {
        contactList[i][0] = change;
      } else if (choice == 2) {
        contactList[i][1] = change;
      } else if (choice == 3) {
        contactList[i][2] = "Home:" + change;
      } else if (choice == 4) {
        contactList[i][3] = "Mobile:" + change;
      }
      break;
    }
  }
  return contactList;
}

// find contact function
void findContact(vector<vector<string>> contactList) {
  string firstName, lastName;
  cout << "First name: ";
  cin >> firstName;
  cout << "Last name: ";
  cin >> lastName;
  bool found = false;
  for (int i=0; i < contactList.size(); i++) {
      if (firstName == contactList[i][0] && lastName == contactList[i][1]) {
        found = true;
        cout << contactList[i][2] << endl;
        cout << contactList[i][3] << endl;
        break;
      }
    } 
  if (!found) {
    cout << "Contact not found." << endl;
  }
}


int main() {
  // set contact list
  vector<vector<string>> contactList = {};

  // parse text file to add to initial list
  string filename = "phonebook.txt";
  ifstream input;
  input.open(filename);
  string line;
  while (getline(input, line)) {
    line.erase(0, 1);
    contactList.push_back(split(line, ','));
  }

  // close file
  input.close();  
  
  // phone book runs until user exits
  while (true) {
    // output menu
    cout << "----------------------------" << endl;
    cout << "1. Add contact" << endl;
    cout << "2. Remove contact" << endl;
    cout << "3. View Contacts" << endl;
    cout << "4. Edit Contact" << endl;
    cout << "5. Find Contact" << endl;
    cout << "6. Exit" << endl;
  
    // choose option
    int choice;
    cout << "Choice: ";
    cin >> choice;
    cout << "----------------------------" << endl;
    
    // phone book functions
    if (choice == 1) {
      // add contact
      contactList = addContact(contactList); 
    } else if (choice == 2) {
      // remove contact
      contactList = removeContact(contactList);
    } else if (choice == 3) {
      // output information
      viewContact(contactList);
    } else if (choice == 4) {
      // edit contact
      contactList = editContact(contactList);    
    } else if (choice == 5) {
      // find contact
      findContact(contactList);
    } else if (choice == 6) {
      // exit program
      cout << "You have exited the phone book!" << endl;
      break;
    }

    // open, rewrite, and close text file
    ofstream ofs;
    ofs.open("phonebook.txt", ofstream::out | ofstream::trunc);
    for (int i=0; i < contactList.size(); i++) {
      string first, last, home, mobile, input;
      first = contactList[i][0];
      last = contactList[i][1];
      home = contactList[i][2];
      mobile = contactList[i][3];
      input = "{" + first + "," + last + "," + home + "," + mobile + ",},\n";
      ofs << input;
    }
    ofs.close();
  }
}