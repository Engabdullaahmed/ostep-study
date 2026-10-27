#include <iostream>
using namespace std;
// core idea of that lab
// The program takes a Virtual Address as input and translates it into the corresponding Physical Address using a Page Table
int main()
{
    /**
     *  virtual page 0 → physical Page 5
        virtual page 1 → physical Page 2
        virtual page 2 → physical Page 8
        virtual page 3 → physical Page 1
     */
    int page_table[] = {5, 2, 8, 1};
    // each page has page size
    int page_size = 4;

    int virtual_address;
    cout << "Enter Virtual Address: ";
    cin >> virtual_address;
    int page_number = virtual_address / page_size;
    int offset = virtual_address % page_size;

    int phsical_page = page_table[page_number];

    int physical_address = phsical_page * page_size + offset;

    cout << "page Number: " << page_number << endl;
    cout << "offset: " << offset << endl;
    cout << "physical page: " << phsical_page << endl;
    cout << "physical address: " << physical_address << endl;

    return 0;
}