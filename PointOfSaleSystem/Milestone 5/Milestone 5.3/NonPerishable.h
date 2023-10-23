#ifndef NONPERISHABLE
#define NONPERISHABLE

#include "Item.h"

using namespace sdds;
namespace sdds{
    class NonPerishable : public Item {
    public:
        NonPerishable();
        char itemType() const override;
        void write(ostream &os) const;
    };

}
#endif