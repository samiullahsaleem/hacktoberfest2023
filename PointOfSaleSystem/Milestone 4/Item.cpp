#include "Item.h"

using namespace sdds;

sdds::Item::Item(const char *sku, const char *name, double price, bool taxed, int quantity){
    this->m_price = price;
    this->m_taxed = taxed;
    this->m_quantity = quantity;
    strncpy(m_sku, sku, MAX_SKU_LEN);
    m_sku[MAX_SKU_LEN] = '\0';
    m_name = new char[MAX_NAME_LEN + 1];
    strncpy(m_name, name, MAX_NAME_LEN);
    m_name[MAX_NAME_LEN] = '\0';
    DisplayType = 0;
    ErrorState = nullptr; // initialize ErrorState to nullptr
}

void sdds::Item::set(char *sku, char *name, double price, bool taxed, int quantity){
    this->m_price = price;
    this->m_taxed = taxed;
    this->m_quantity = quantity;
    strncpy(m_sku, sku, MAX_SKU_LEN);
    m_sku[MAX_SKU_LEN] = '\0';
    strncpy(m_name, name, MAX_NAME_LEN);
    m_name[MAX_NAME_LEN] = '\0';
}

// Copy constructor
sdds::Item::Item(const Item& other) {
    // Copy all non-pointer member variables
    strncpy(m_sku, other.m_sku, MAX_SKU_LEN);
    m_name = other.m_name;
    m_price = other.m_price;
    m_taxed = other.m_taxed;
    m_quantity = other.m_quantity;
    if(other.ErrorState!= NULL){
        ErrorState  =  new Error(other.ErrorState->GetError());
        ErrorState->setError(other.ErrorState->GetError());
    }
    else
        ErrorState = nullptr;
}

// Copy assignment operator
Item& sdds::Item::operator=(const Item& other) {
    if (this != &other) {
        // Copy all non-pointer member variables
        strncpy(m_sku, other.m_sku, MAX_SKU_LEN);
        delete[] m_name;
        m_name = new char[MAX_NAME_LEN + 1];
        strncpy(m_name, other.m_name, MAX_NAME_LEN);
        m_price = other.m_price;
        m_taxed = other.m_taxed;
        m_quantity = other.m_quantity;
        if(ErrorState != NULL) {
            delete ErrorState;
            ErrorState = NULL;
        }
        if(other.ErrorState!= NULL){
            ErrorState = new Error(other.ErrorState->GetError());
        }
        else
            ErrorState = NULL;
    }
    return *this;
}

bool sdds::Item::operator > (const Item& other) const {
    return (strcmp(m_name, other.m_name) > 0);
}

//Adds from data member quantity from the object
int sdds::Item::operator+=(int value)
{
    if (m_quantity + value > MAX_STOCK_NUMBER)
    {
        m_quantity = MAX_STOCK_NUMBER;
        if(ErrorState == NULL)
            ErrorState = new Error(ERROR_POS_QTY);
        else
            ErrorState->setError(ERROR_POS_QTY);
    }
    else
    {
        m_quantity += value;
    }
    return m_quantity;
}

//subtracts from data member quantity from the object
int sdds::Item::operator-=(int quantity)
{
    m_quantity -= quantity;
    if (m_quantity < 0)
    {
        m_quantity = 0;
        if(ErrorState == NULL)
            ErrorState = new Error(ERROR_POS_STOCK);
        else
            ErrorState->setError(ERROR_POS_STOCK);
    }
    return m_quantity;
}

/*This function simply returns the opposite of the status of the ErrorState attribute.
 If ErrorState is not nullptr (meaning an error has occurred), then !ErrorState will be false,
 which means the item is not valid. Otherwise, will be true, which means the item is valid*/

sdds::Item::operator bool() const {
    if(ErrorState!=NULL && ErrorState->operator bool())
        return false;
    return true;
}

Item& sdds::Item::displayType(int type) {
    DisplayType = type;
    return *this;
}

double sdds::Item::cost() const {
    return m_taxed ? m_price * (1 + TAX) : m_price;
}

int sdds::Item::quantity() const {
    return m_quantity;
}

Item& sdds::Item::clear() {
    ErrorState->clear();
    return *this;
}

bool sdds::Item::operator==(const char* sku) const {
    return strcmp(m_sku, sku) == 0;
}

void sdds::Item::write(ostream& os) const {
    if(ErrorState!= NULL && ErrorState->operator bool()){
        ErrorState->display(cout);
    }

    else if (DisplayType==1) {
        string name_substr = string(m_name).substr(0, 20);
        os << left << setw(MAX_SKU_LEN) << m_sku << "|"
           << left << setw(20) << name_substr << "|"
           << right << fixed << setprecision(2) << setw(7) << m_price << "|"
           << (m_taxed ? " X " : "   ") << "|"
           << setw(4) << m_quantity << "|"
           << setw(9) << cost() * m_quantity << "|";
    }
    else if(DisplayType == 2){
        os << "=============v" << endl;
        os << "Name:        " << m_name << endl
           << "Sku:         " << m_sku << std::endl
           << "Price:       " << fixed << setprecision(2) << m_price << endl
           << "Price + tax: ";
        if (m_taxed) {
            os << setw(10) << fixed << cost() << endl;
        }
        else {
            os << "N/A" << endl;
        }
        os << "Stock Qty:   " << m_quantity << endl;
    }
}

void sdds::Item::save(ofstream& ofs) const {
    ofs << itemType() << "," << m_sku << "," << m_name << "," << fixed << setprecision(2) << m_price << ","
        << m_taxed << "," << m_quantity;
    if (ErrorState != NULL  && ErrorState->operator bool()) {
        ErrorState->display(cerr);
    }
}

istream& sdds::Item::read(istream& is){
    string sku;
    cout << "Sku\n> ";
    while (getline(is, sku)) {
        if (sku.length() > MAX_SKU_LEN) {
            cout << ERROR_POS_SKU << endl;
            cout << "> ";
        }

        else {
            sku.copy(m_sku, MAX_SKU_LEN);
            break;
        }
    }

    string name;
    cout << "Name\n> ";
    while (getline(is, name)) {
        if (name.length() > MAX_NAME_LEN) {
            cout << ERROR_POS_NAME << endl;
            cout << "> ";
        }
        else {
            strncpy(m_name, name.c_str(), MAX_NAME_LEN);
            break;
        }
    }

    double price;
    cout << "Price\n";
    while (true) {
        cout << "> ";
        if (is >> price) {
            if (price < 0.01) {
                cout << ERROR_POS_PRICE << endl;
            } else {
                m_price = price;
                break;
            }
        } else {
            cout << ERROR_POS_PRICE << endl;
            is.clear();
            is.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    char taxed;
    string input;

    cout << "Taxed?\n";
    cin.ignore();
    cout << "(Y)es/(N)o: ";
    while (true) {
        getline(cin, input);
        if (input.length() == 1) {
            taxed = input.front();
            if (taxed == 'Y' || taxed == 'y') {
                m_taxed = true;
                break;
            } else if (taxed == 'N' || taxed == 'n') {
                m_taxed = false;
                break;
            }
        }
        cout << "Only 'y' and 'n' are acceptable: ";
    }

    int quantity;
    string in;

    cout << "Quantity\n";
    while (true) {
        cout << "> ";
        getline(cin, in);
        try {
            quantity = stoi(in);
            if (quantity <= 0 || quantity > MAX_STOCK_NUMBER) {
                cout << ERROR_POS_QTY << endl;
            } else {
                m_quantity = quantity;
                break;
            }
        } catch (...) {
            cout << ERROR_POS_QTY << endl;
        }
    }

    return is;
}

void sdds::Item::load(ifstream& ifs){
    char comma;
    string sku, name;
    double price;
    int tax;
    int quantity;
    if(ErrorState != NULL) {
        delete ErrorState;
        ErrorState = NULL;
    }
    // Read data from the file into local variables
    if(!getline(ifs, sku, ','))
        return;
    getline(ifs, name, ',');
    ifs >> price >> comma >> tax >> comma >> quantity;
    // Validate the data
    if (sku.length() > MAX_SKU_LEN) {
        if(ErrorState == NULL)
            ErrorState = new Error(ERROR_POS_SKU);
        else
            ErrorState->setError(ERROR_POS_SKU);
    }
    else if (name.length() > MAX_NAME_LEN) {
        if(ErrorState == NULL)
            ErrorState = new Error(ERROR_POS_NAME);
        else
            ErrorState->setError(ERROR_POS_NAME);
    }
    else if (price < 0.01) {
        if(ErrorState == NULL)
            ErrorState = new Error(ERROR_POS_PRICE);
        else
            ErrorState->setError(ERROR_POS_PRICE);
    }

    else if (tax > 1 || tax < 0) {
        if(ErrorState == NULL)
            ErrorState = new Error(ERROR_POS_TAX);
        else
            ErrorState->setError(ERROR_POS_TAX);
    }

    else if (quantity < 0 || quantity > MAX_STOCK_NUMBER) {
        if(ErrorState == NULL)
            ErrorState = new Error(ERROR_POS_QTY);
        else
            ErrorState->setError(ERROR_POS_QTY);
    }

    // If no validation errors, set the attributes
    else if (ErrorState==NULL || !ErrorState->operator bool()) {
        bool t = tax;
        char mSku[MAX_SKU_LEN + 1];
        char n[MAX_NAME_LEN + 1];

        mSku[0] = '\0';
        n[0] = '\0';
        strncpy(mSku, sku.c_str(),MAX_SKU_LEN);
        strncpy(n, name.c_str(), MAX_NAME_LEN);

        // Add the null terminator to the character array
        n[name.length()] = '\0';
        mSku[sku.length()] = '\0';
        set(mSku, n, price, t, quantity);
    }
}

ostream& sdds::Item::bprint(std::ostream& os) const {
    string name_substr = string(m_name).substr(0, 20);
    os << "| " << setw(20) << left << name_substr << "| ";
    if (m_taxed) {
        os << fixed << setprecision(2) << setw(9) << right << cost() << " |  T  |";
    }
    else {
        os << fixed << setprecision(2) << setw(9) << right << m_price << " |     |";
    }

    os << endl;
    return os;
}

// Destructor
sdds::Item::~Item() {
    delete[] m_name;
    if(ErrorState!=NULL) {
        ErrorState->clear();
        delete ErrorState;
    }
}
