#ifndef POSIO
#define POSIO

#include <iostream>
#include <fstream>

using namespace std;

namespace sdds {
    class PosIO {
    public:
        virtual void write(ostream &os) const = 0;

        virtual istream &read(istream &is) = 0;

        virtual void save(ofstream &ofs) const = 0;

        virtual void load(ifstream &ifs) = 0;

        virtual ~PosIO() {} // empty virtual destructor

        // insertion operator overload to work with ostream
        friend std::ostream &operator<<(ostream &os, const PosIO &obj) {
            obj.write(os);
            return os;
        }

// insertion operator overload to work with ofstream
        friend std::ofstream &operator<<(ofstream &ofs, const PosIO &obj) {
            obj.save(ofs);
            return ofs;
        }

// extraction operator overload to work with istream
        friend std::istream &operator>>(istream &is, PosIO &obj) {
            obj.read(is);
            return is;
        }

// extraction operator overload to work with ifstream
        friend std::ifstream &operator>>(ifstream &ifs, PosIO &obj) {
            obj.load(ifs);
            return ifs;
        }
    };
}
#endif



