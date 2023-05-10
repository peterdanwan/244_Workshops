#include <iostream>
#include "VendingMachine.h"

namespace sdds
{
   // Setting our external variable
   const int MAX_SODAS = 5;
   const int VEND_ROW_LEN = 5;
   const int VEND_COL_LEN = 5;

   VendingMachine::VendingMachine(const VendingMachine& vm)
   {

   }

   VendingMachine& VendingMachine::operator=(const VendingMachine& vm)
   {
      return *this;
   }
                                  // e.g., 8 slots
   VendingMachine::VendingMachine(Soda* sodas, int numSodas)
   {
      bool exists{};
      int index{};
      int newSodaCounter{};
      int duplicate{};

      m_maxSlots = VEND_COL_LEN * VEND_ROW_LEN;

      Soda* tempSodas = sodas;
      //std::cout << tempSodas << std::endl;
      //std::cout << sodas << std::endl;
      

      if (m_maxSlots > 0 && sodas && numSodas > 0)
      {
         if (sodas)
         {

            for (int i = 0; i < numSodas; ++i)
            {
               // Makes a call to the += operator for the Vending machine.
               // The += operator will:
               // - add a soda to a slot under these connections
               //   > 
                *this += sodas[i];
            }

            //for (int i = 0; i < numSodas; i++)
            //{
            //   int existCounter{};

            //   for (int j = 0; j < numSodas; j++)
            //   {
            //      if (std::strcmp(sodas[i].getName(), tempSodas[j].getName()) == 0)
            //      {
            //         existCounter++;
            //      }
            //   }

            //   if (existCounter == 1) //0
            //   {
            //      newSodaCounter++; // duplicate doesn't tell us which duplicate it's for

            //   }
            //}

            //m_sodaCells = new Soda[newSodaCounter];


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
               if (m_sodaCells[j].getPrice() > m_sodaCells[j + 1].getPrice())
               {
                  // Swap m_sodaCells[j] and m_sodaCells[j+1]
                  swap(m_sodaCells[j], m_sodaCells[j + 1]);
               }
            }
            else
            {
               if (m_sodaCells[j].getPrice() < m_sodaCells[j + 1].getPrice())
               {
                  // Swap m_sodaCells[j] and m_sodaCells[j+1]
                  swap(m_sodaCells[j], m_sodaCells[j + 1]);
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
      // Makes a call to the += operator for the Vending machine.
      //   The += operator will:
      //   - add a soda to a slot under these connections
      //        1. The incoming soda's name and the vending machine's cell name match and there are spaces left in the cell to add the soda.
      //           > If there was an initial match in a name, but no spaces left in the cell, we will check if there is another cell with 
      //             a matching name that has space left or has the name "Empty" (see Step 2)
      //        2. The incoming soda's name does NOT match any pre-existing cell names, but there is a slot name "Empty" which will be overwritten to match the new soda.
      //   - in the event that there are no available spaces, the sodas won't be added.

      bool canAdd{};
      int index{};
      if (soda)
      {
         if (m_currentSlotsFilled)
         {

            for (int i = 0; i < m_currentSlotsFilled && !canAdd; i++)
            {
               if (m_sodaCells && std::strcmp(m_sodaCells[i].getName(), soda.getName()) == 0)
               {
                  if (m_sodasInCell[i] < MAX_SODAS)
                  {
                     canAdd = true;
                     m_sodasInCell[i] += 1;
                  }
               }
            }

            if (!canAdd && m_currentSlotsFilled < m_maxSlots)
            {
               Soda* tempSodas = new Soda[m_currentSlotsFilled + 1];
               for (int i = 0; i < m_currentSlotsFilled; i++)
               {
                  tempSodas[i] = m_sodaCells[i];
               }

               tempSodas[m_currentSlotsFilled] = soda;
               m_currentSlotsFilled++;
               m_sodasInCell[m_currentSlotsFilled] += 1;

            }
         }
         else
         {
            // Size the temp soda array
            Soda* tempSodas = new Soda[m_currentSlotsFilled + 1];

            // tempSodas[0] = incSoda obj
            tempSodas[m_currentSlotsFilled] = soda;

            // increment slots
            m_currentSlotsFilled++;

            // Have the member variable point to the same area tempSodas is pointing to
            m_sodaCells = tempSodas;


            m_sodasInCell = new int[m_currentSlotsFilled + 1];
            m_sodasInCell[m_currentSlotsFilled] += 1;
         }
      }

      return *this;
   }

   std::ostream& VendingMachine::display(std::ostream& os)const
   {
      for (int i = 0; i < m_maxSlots; i++)
      {
         std::cout << m_sodaCells[i];
      }

      return os;
   }
}