#include <iostream>
#include "VendingMachine.h"

namespace sdds
{
   // Setting our external variable
   const int MAX_SODAS = 5;

   VendingMachine::VendingMachine(const VendingMachine& vm)
   {

   }

   VendingMachine& VendingMachine::operator=(const VendingMachine& vm)
   {
      return *this;
   }

   VendingMachine& VendingMachine::swap(Soda& left, Soda& right)
   {
      Soda temp = left;
      left = right;
      right = temp;

      return *this;
   }

   VendingMachine& VendingMachine::sort(bool ascending)
   {
      for (int i = 0; i < m_numSodaSlots - 1; i++) 
      {
         for (int j = 0; j < m_numSodaSlots-i-1; j++) 
         {
            if (ascending)
            {
                  if (m_sodas[j].getPrice() > m_sodas[j+1].getPrice()) 
                  {
                     // Swap m_sodas[j] and m_sodas[j+1]
                     swap(m_sodas[j], m_sodas[j + 1]);
                  }
            } 
            else 
            {
                  if (m_sodas[j].getPrice() < m_sodas[j+1].getPrice()) 
                  {
                     // Swap m_sodas[j] and m_sodas[j+1]
                     swap(m_sodas[j], m_sodas[j + 1]);
                  }
            }
         }
       }


      return *this;
   }

   // Used to call sort sodas in descending order by price
   // Returns a copy of a VendingMachine, leaving the original VendingMachine untouched  
   VendingMachine VendingMachine::operator-()const
   {
      VendingMachine old = *this;

      return VendingMachine(old.sort(false)); 
   }

   // Used to call sort sodas in ascending order by price
   // Returns a copy of a VendingMachine, leaving the original VendingMachine untouched  
   VendingMachine VendingMachine::operator+()const
   {
      VendingMachine old = *this;
      return VendingMachine(old.sort(true)); 
   }

   VendingMachine& VendingMachine::operator+=(const Soda& soda)
   {
      bool canAdd{};
      int index{};
      if (soda)
      {
         for (int i = 0; i < m_numSodaSlots && !canAdd; i++)
         {
            if (std::strcmp(m_sodas[i].getName(), soda.getName()))
            {
               if (m_sodasPerCell[i] < 5)
               {
                  canAdd = true;
                  m_sodasPerCell[i]++;
               }
            }
         }


      }

      return *this;
   }

   std::ostream& VendingMachine::display(std::ostream& os)const
   {


      return os;
   }
}