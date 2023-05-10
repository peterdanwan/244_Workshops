#ifndef SDDS_VENDING_MACHINE_H
#define SDDS_VENDING_MACHINE_H
#include <iostream>
#include "soda.h"

namespace sdds 
{
    const int extern MAX_SODAS;

    class VendingMachine
    {
       int m_maxSlots{};  // A1 A2 A3 A4
                              // B1 B2 B3

       int* m_sodasPerCell{}; // all cells can hold up to 5 sodas 

       int m_currentSlotsFilled{};
                             
       // m_sodasPerCell[0] == A1; // can range from 0-5;
       // m_sodasPerCell[1] == A2; // can range from 0-5;
       Soda* m_sodas{}; //Soda m_sodas[7];
    public:
       VendingMachine() = default;
 
       VendingMachine(int maxSlots, int sodasPerCell, Soda* sodas, int numSodas);
       VendingMachine(const VendingMachine& vm);
       VendingMachine& operator=(const VendingMachine& vm);
       VendingMachine& sort(bool ascending);
       VendingMachine& swap(Soda& left, Soda& right);
       VendingMachine operator-()const;
       VendingMachine operator+()const;
       VendingMachine& operator+=(const Soda& soda);
       std::ostream& display(std::ostream& os = std::cout)const;

    };
}
#endif
