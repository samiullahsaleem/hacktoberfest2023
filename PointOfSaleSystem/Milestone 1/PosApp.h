#ifndef POSAPP_H
#define POSAPP_H


namespace sdds {

    class PosApp {

    public:
        PosApp(const char* filename);
        ~PosApp();
        void loadRecs();
        void saveRecs();
        void run();
        void listItems();
        void addItem();
        void removeItem();
        void stockItem();
        void POS();

    private:
        char* m_filename;

    };


#endif
}
