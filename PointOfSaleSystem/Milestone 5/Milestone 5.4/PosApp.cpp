#include "PosApp.h"
#include "Utils.h"
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

namespace sdds {

    PosApp::PosApp(const char* filename)
    {
        nptr = 0;
        strcpy(this->m_filename, filename);
        for(int i=0; i<MAX_NO_ITEMS; i++)
            Iptr[i] = NULL;
        actionTitle = "";
    }

    PosApp::~PosApp() {
        for(int i=0; i<nptr; i++)
        {
            delete Iptr[i];
            Iptr[i] = NULL;
        }
        nptr = 0;
    }


    void PosApp::run() {
        bool exit = false;
        int option;
        loadRecs();
        while (!exit) {
            std::cout << "The Sene-Store" << std::endl;
            std::cout << "1- List items" << std::endl;
            std::cout << "2- Add item" << std::endl;
            std::cout << "3- Remove item" << std::endl;
            std::cout << "4- Stock item" << std::endl;
            std::cout << "5- POS" << std::endl;
            std::cout << "0- exit program" << std::endl;
            std::cout << "> ";
            option = getInt(0, 5, "Enter the row number: ");
            switch (option) {
            case 0:
                saveRecs();
                exit = true;
                break;
            case 1:

                listItems(false);
                break;
            case 2:

                addItem();
                break;
            case 3:

                removeItem();
                break;
            case 4:

                stockItem();
                break;
            case 5:

                cout << "POS Function\n";
                break;
            default:
                break;
            }
        }
    }



    void PosApp::listItems(bool isSelect) {
        actionTitle.clear();
        actionTitle = "Listing Items";
        while (actionTitle.length() < 72) {
            actionTitle.push_back('.');
        }
        cout << ">>>> " << actionTitle << '\n';

        selectionSort();

        cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |\n";
        cout << "-----|--------|--------------------|-------|---|----|---------|-------------|\n";

        double totalAsset = 0.0;

        for(int i=0; i<nptr; i++)
        {
            Iptr[i]->displayType(POS_LIST);
            cout << setw(4) << right << i+1 << " |" << *Iptr[i] << endl;
            totalAsset += (Iptr[i]->cost() * Iptr[i]->quantity());
        }

        cout << "-----^--------^--------------------^-------^---^----^---------^-------------^\n";
        if(!isSelect) {
            cout << "                               Total Asset: $  |" << setw(14) << fixed << setprecision(2)
                 << right << totalAsset << "|\n";
            cout << "-----------------------------------------------^--------------^\n\n";
        }
    }

    void PosApp::addItem() {
        char ch;
        actionTitle.clear();
        actionTitle = "Adding Item to the store";
        while (actionTitle.length() < 72) {
            actionTitle.push_back('.');
        }
        cout << ">>>> " << actionTitle << '\n';

        if(nptr == MAX_NO_ITEMS)
        {
            cout << "Inventory Full!\n";
            return;
        }

        Item* item;

        cout << "Is the Item perishable? (Y)es/(N)o: ";
        cin >> ch;

        if(ch == 'y')
            item = new Perishable();
        else if(ch == 'n')
            item = new NonPerishable();
        else
            return;

        cin.ignore();
        while(true)
        {
            cin >> *item;
            if(*item)
                break;

            cin.clear();
            std::fflush(stdin);

            cout << *item;
            cout << ", try again...\n";
        }

        Iptr[nptr] = item;
        nptr++;

        actionTitle.clear();
        actionTitle = "DONE!";
        while (actionTitle.length() < 72) {
            actionTitle.push_back('.');
        }
        cout << ">>>> " << actionTitle << '\n';
    }

    int PosApp::selectItem() {
        actionTitle.clear();
        actionTitle = "Item Selection by row number";
        while (actionTitle.length() < 72) {
            actionTitle.push_back('.');
        }
        cout << ">>>> " << actionTitle << '\n';
        cout << "Press <ENTER> to start....";
        getchar();
        listItems(true);
        cout << "Enter the row number: ";
        int option = getInt(1, nptr,"Enter the row number: ");
        return option-1;
    }


    void PosApp::removeItem() {
        actionTitle.clear();
        actionTitle = "Remove Item";
        while (actionTitle.length() < 72) {
            actionTitle.push_back('.');
        }
        cout << ">>>> " << actionTitle << '\n';
        int index = selectItem();

        cout << "Removing....\n";
        Iptr[index]->displayType(POS_FORM);
        cout << *Iptr[index];
        delete Iptr[index];

        for(int i=index; i<nptr-1; i++)
            Iptr[i] = Iptr[i+1];
        Iptr[nptr-1] = NULL;
        nptr--;

        actionTitle.clear();
        actionTitle = "DONE!";
        while (actionTitle.length() < 72) {
            actionTitle.push_back('.');
        }
        cout << ">>>> " << actionTitle << '\n';
    }
    void PosApp::stockItem() {
        cout << ">>>> Select an item to stock................................................." << endl;
        int index = selectItem();
        Iptr[index]->displayType(POS_FORM);
        cout << "Selected Item:\n" << *Iptr[index];
        cout << "Enter quantity to add: ";
        int option = getInt(1, MAX_STOCK_NUMBER - Iptr[index]->quantity(),"Enter quantity to add: ");
        Iptr[index]->setQuantity(Iptr[index]->quantity()+option);
    }

    void PosApp::saveRecs() {
        ofstream outFile(m_filename);
        actionTitle.clear();
        actionTitle = "Saving Data";
        while (actionTitle.length() < 72) {
            actionTitle.push_back('.');
        }
        cout << ">>>> " << actionTitle << '\n';
        cout << "Goodbye!\n";
        for(int i=0; i<nptr; i++) {
            Iptr[i]->save(outFile);
            outFile << endl;
        }

        outFile.close();
    }

    void PosApp::loadRecs() {
        char obj, comma;

        ifstream input(m_filename);

        if(input.fail())
        {
            ofstream file(m_filename);
            file.close();
            input.open(m_filename);
        }

        if(nptr != 0)
        {
            for(int i=0; i<nptr; i++)
            {
                delete Iptr[i];
                Iptr[i] = NULL;
            }
            nptr = 0;
        }

        actionTitle.clear();
        actionTitle = "Loading Items";
        while (actionTitle.length() < 72) {
            actionTitle.push_back('.');
        }
        cout << ">>>> " << actionTitle << '\n';

        while( !input.eof() && nptr < MAX_NO_ITEMS )
        {
            input >> obj >> comma;
            if(input.eof())
                break;

            if(obj == 'N')
                Iptr[nptr] = new NonPerishable();
            else if(obj == 'P')
                Iptr[nptr] = new Perishable();

            Iptr[nptr]->load(input);
            nptr++;
        }
    }
}



