#include "Perishable.h"

using namespace sdds;
using namespace std;

namespace sdds {
    char Perishable:: itemType() const {
        return 'P';
    }

    istream& Perishable::read(istream &is) {
        string d;
        Item::read(is); // invoke the read of the base class
        if (!ErrorState) {
            cout << "Expiry date (YYYY/MM/DD)\n> ";
            getline(cin, d, '\n');
            stringstream ss(d);
            string part;
            int year, month, day;
            getline(ss, part, '/');
            year = stoi(part);
            getline(ss, part, '/');
            month = stoi(part);
            getline(ss, part, '/');
            day = stoi(part);
            Date temp(year, month, day, 0, 0);
            temp.dateOnly(1);
            if (temp.error()) //temp.error is returning object
                ErrorState = new Error(temp.error().GetError()); //copy objects data to item's error state
            else
                m_expiryDate = temp;
        }
        return is;
    }


    void Perishable::write(ostream &os) const {
        Item::write(os); // invoke the base class's write() function
        if (!ErrorState) {
            if (DisplayType == POS_LIST) {
                os << "  ";
                os << m_expiryDate;
                os << " |";
            } else if (DisplayType == POS_FORM) {
                os << "Expiry date: " << m_expiryDate << endl;
                os << "=============^" << endl;
            }
        }
        cout << left;
    }

    void Perishable::load(ifstream &ifs) {
        string s;
        Item::load(ifs); // Call the base class load function first
        if (!ErrorState && !ifs.eof()) { // Check if the ifstream and the object are in a good state
            ifs.ignore(); // Ignore the comma separator
            ifs >> s; // Extract the date from the ifstream
            stringstream ss(s);
            string part;
            int year, month, day;
            getline(ss, part, '/');
            year = stoi(part);
            getline(ss, part, '/');
            month = stoi(part);
            getline(ss, part, '/');
            day = stoi(part);
            Date temp(year, month, day, 0, 0);
            temp.dateOnly(1);
            if (temp.error()) //temp.error is returning object
                ErrorState = new Error(temp.error().GetError()); //copy objects data to item's error state
            else
                m_expiryDate = temp;
        }
    }

    void Perishable::save(ofstream &ofs) const {
        Item::save(ofs);
        if (!ErrorState) {
            ofs << "," << m_expiryDate;
        }
    }
}