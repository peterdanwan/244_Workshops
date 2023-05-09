#ifndef SDDS_VENDING_MACHINE_H
#define SDDS_VENDING_MACHINE_H
#include "soda.h"

namespace sdds 
{
    class VendingMachine
    {
       int* m_sodasPerCell{}; //all cells can hold 5 sodas 

       // m_sodasPerCell[0] == A1; // can range from 0-5;
       // m_sodasPerCell[1] == A2; // can range from 0-5;
       Soda* m_sodas{};
    public:
       

    };
}
#endif
