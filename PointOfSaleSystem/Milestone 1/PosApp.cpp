#include "PosApp.h"
#include "Utils.h"
#include <iostream>
#include <cstring>

using namespace std;

namespace sdds {

    PosApp::PosApp(const char* filename) {
        if (filename != nullptr && strlen(filename) <= 255) {
            m_filename = new char[strlen(filename) + 1];
            strcpy(m_filename, filename);
        }
        else {
            m_filename[0] = '\0';
        }
    }

    PosApp::~PosApp() {
        delete[] m_filename;
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
            std::cout << "5- Point of Sale" << std::endl;
            std::cout << "0- exit program" << std::endl;
            std::cout << "> ";
            option = getInt(0, 5);
            switch (option) {
            case 0:
                saveRecs();
                exit = true;
                break;
            case 1:

                listItems();
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

                POS();
                break;
            default:
                break;
            }
        }
    }



    void PosApp::listItems() {
        cout << ">>>> Listing Items..........................................................." << endl;
        cout << "Running listItems()" << endl;

    }

    void PosApp::addItem() {
        cout << ">>>> Adding Item to the store................................................" << endl;
        cout << "Running addItem()" << endl;
    }




    void PosApp::removeItem() {
        cout << ">>>> Remove Item............................................................." << endl;
        cout << "Running removeItem()" << endl;

    }
    void PosApp::stockItem() {
        cout << ">>>> Select an item to stock................................................." << endl;
        cout << "Running stockItem()" << endl;
    }
    void PosApp::POS() {
        cout << ">>>> Starting Point of Sale.................................................." << endl;
        cout << "Running POS()" << endl;
    }

    void PosApp::saveRecs() {
        cout << ">>>> Saving Data............................................................." << endl;
        cout << "Saving data in " << m_filename << endl;
        cout << "Goodbye!" << endl;

    }

    void PosApp::loadRecs() {
        cout << ">>>> Loading Items..........................................................." << endl;
        cout << "Loading data from " << m_filename << endl;
    }


}



