#ifndef POSAPP_H
#define POSAPP_H

#include "Bill.h"
#include "Date.h"
#include "Error.h"
#include "Item.h"
#include "NonPerishable.h"
#include "Perishable.h"
#include "Utils.h"
#include <iostream>
#include <vector>

namespace sdds {

    class PosApp {

    public:
        PosApp(const char* filename);
        ~PosApp();
        void loadRecs();
        void saveRecs();
        void run();
        void listItems(bool isSelect);
        void addItem();
        int selectItem();
        void removeItem();
        void stockItem();

    private:
        char m_filename[128];
        Item* Iptr[MAX_NO_ITEMS];
        int nptr;
        string actionTitle;

        void selectionSort() {
            int i, j, min_idx;

            for (i = 0; i < nptr - 1; i++) {
                // Find the minimum element in unsorted array
                min_idx = i;
                for (j = i + 1; j < nptr; j++) {
                    if (strcmp(Iptr[j]->GetName(), Iptr[min_idx]->GetName()) < 0) {
                        min_idx = j;
                    }
                }

                // Swap the found minimum element with the first element
                if (min_idx != i)
                {
                    Item* temp = Iptr[i];
                    Iptr[i] = Iptr[min_idx];
                    Iptr[min_idx] = temp;
                }
            }
        }
    };


#endif
}
