#include "NonPerishable.h"

using namespace sdds;
    namespace sdds{
    NonPerishable :: NonPerishable() {}

    char NonPerishable :: itemType() const {
        return 'N';
    }

    void NonPerishable :: write(ostream &os) const {
        Item::write(os); // call the base class write function

        if (!ErrorState) { // check if object is in a good state
            if (DisplayType == POS_LIST) {
                os << "     N / A   |";
            } else if (DisplayType == POS_FORM) {
                os << "=============^\n";
            }
        }
        cout << left;
    }

}