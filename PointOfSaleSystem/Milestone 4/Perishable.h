#include "Date.h"
#include "Item.h"
#ifndef PERISHABLE
#define PERISHABLE

using namespace sdds;
using namespace std;

namespace sdds {
    class Perishable : public Item {
        Date m_expiryDate;

    public:
        char itemType() const override;

        istream &read(istream &is);

        void write(ostream &os) const override;

        void load(ifstream &ifs);

        void save(ofstream &ofs) const override;
    };
}
#endif