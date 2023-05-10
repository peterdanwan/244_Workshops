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

   VendingMachine::VendingMachine(int maxSlots, int sodasPerCell, Soda* sodas, int numSodas)
   {
      bool exists{};
      int index{};

      if (maxSlots > 0 && sodasPerCell > 0 && sodas && numSodas > 0)
      {
         m_maxSlots = maxSlots;
         for (int i = 0; i < numSodas && !exists; i++)
         {
            if (sodas)
            {
               
            }

         }

      }
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
      for (int i = 0; i < m_maxSlots - 1; i++)
      {
         for (int j = 0; j < m_maxSlots - i - 1; j++)
         {
            if (ascending)
            {
               if (m_sodas[j].getPrice() > m_sodas[j + 1].getPrice())
               {
                  // Swap m_sodas[j] and m_sodas[j+1]
                  swap(m_sodas[j], m_sodas[j + 1]);
               }
            }
            else
            {
               if (m_sodas[j].getPrice() < m_sodas[j + 1].getPrice())
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
         for (int i = 0; i < m_maxSlots && !canAdd; i++)
         {
            if (std::strcmp(m_sodas[i].getName(), soda.getName()))
            {
               if (m_sodasPerCell[i] < 5)
               {
                  canAdd = true;
                  m_sodasPerCell[i] += 1;
               }
            }
         }

         if (!canAdd && m_currentSlotsFilled < m_maxSlots)
         {
            Soda* tempSodas = new Soda[m_currentSlotsFilled + 1];
            for (int i = 0; i < m_maxSlots; i++)
            {
               tempSodas[i] = m_sodas[i];
            }

            tempSodas[m_currentSlotsFilled] = soda;
            m_currentSlotsFilled++;
            m_sodasPerCell[m_currentSlotsFilled] += 1;

         }
      }

      return *this;
   }

   std::ostream& VendingMachine::display(std::ostream& os)const
   {
      for (int i = 0; i < m_maxSlots; i++)
      {
         std::cout << m_sodas[i];
      }

      return os;
   }
}