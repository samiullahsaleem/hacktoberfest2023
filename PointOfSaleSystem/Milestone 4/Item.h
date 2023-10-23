#ifndef ITEM
#define ITEM

#include <cstring>
#include <iostream>
#include <iomanip>
#include <limits>
#include "POS.h"
#include "PosIO.cpp"
#include "Error.h"

using namespace std;
namespace sdds {
    class Item : public PosIO {
    private:
        char m_sku[MAX_SKU_LEN + 1];
        char *m_name;
        double m_price;
        bool m_taxed;
        int m_quantity;

    protected:
        int DisplayType;
        Error *ErrorState;

    public:
        Item(const char *sku = "\0", const char *name = "\0", double price = 0.0, bool taxed = false, int quantity = 0);

        void set(char *sku, char *name, double price, bool taxed, int quantity);

        // Copy constructor
        Item(const Item &other);

        // Copy assignment operator
        Item &operator=(const Item &other);

        bool operator>(const Item &other) const;
        //Adds from data member quantity from the object

        int operator+=(int value);

        //subtracts from data member quantity from the object
        int operator-=(int quantity);

        operator bool() const;

        friend double& operator+=(double& left, const Item& right) {
            return left += right.cost() * right.quantity();
        }

        virtual char itemType() const = 0; // type indicator

        Item &displayType(int type);

        double cost() const;

        int quantity() const;

        Item &clear();

        bool operator==(const char *sku) const;

        virtual void write(ostream &os) const;

        virtual void save(ofstream &ofs) const;

        virtual istream &read(istream &is);

        void load(ifstream &ifs);

        ostream &bprint(std::ostream &os) const ;

        // Destructor
        ~Item() ;
    };
}
#endif