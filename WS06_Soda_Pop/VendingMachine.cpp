#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
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
      *this = vm;
   }

   VendingMachine& VendingMachine::operator=(const VendingMachine& vm)
   {
      if (this != &vm)
      {
         // Clear current object's dynamic memory
         delete[] m_sodaCells;
         m_sodaCells = nullptr;
         delete[] m_sodasInCell;
         m_sodasInCell = nullptr;

         // Deep copy of resources
         //// Resize m_sodaCells
         m_sodaCells = new Soda[vm.m_currentSlotsFilled];

         for (int i = 0; i < vm.m_currentSlotsFilled; i++)
         {
            m_sodaCells[i] = vm.m_sodaCells[i];
         }

         m_sodasInCell = new int[vm.m_currentSlotsFilled];
         for (int i = 0; i < vm.m_currentSlotsFilled; i++)
         {
            m_sodasInCell[i] = vm.m_sodasInCell[i];
         }

         // Shallow copy of resources
         m_maxSlots = vm.m_maxSlots;
         m_currentSlotsFilled = vm.m_currentSlotsFilled;

      }


      return *this;
   }
   // e.g., 8 slots
   VendingMachine::VendingMachine(const Soda* sodas, int numSodas)
   {
      // do we need this anymore 
      m_maxSlots = VEND_COL_LEN * VEND_ROW_LEN;

      if (m_maxSlots > 0 && sodas && numSodas > 0)
      {
         if (sodas)
         {

            for (int i = 0; i < numSodas; ++i)
            {
               *this += sodas[i];
            }

            std::cout << m_maxSlots << std::endl;
            std::cout << m_currentSlotsFilled << std::endl;
            for (int i = 0; i < m_currentSlotsFilled; i++)
            {
               std::cout << m_sodaCells[i].getName() << std::endl;
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

      if (soda)
      {
         //if (m_currentSlotsFilled)
         //{
            //&& std::strcmp(m_sodaCells[i].getName(), soda.getName()) == 0
         for (int i = 0; i < m_currentSlotsFilled && !canAdd; i++)
         {
            if (m_sodaCells)
            {
               if (m_sodaCells[i].getName() && m_sodaCells[i].getName()[0])
               {
                  if (std::strcmp(m_sodaCells[i].getName(), soda.getName()) == 0)
                  {
                     if (m_sodasInCell[i] < MAX_SODAS)
                     {
                        canAdd = true;
                        m_sodasInCell[i] += 1;
                     }
                  }
               }
            }
         }

         if (!canAdd && m_currentSlotsFilled < m_maxSlots)
         {
            Soda* tempSodas = new Soda[m_currentSlotsFilled + 1];
            for (int i = 0; i < m_currentSlotsFilled && m_sodaCells; i++)
            {
               tempSodas[i] = m_sodaCells[i];
            }

            tempSodas[m_currentSlotsFilled] = soda;

            if (m_sodaCells)
            {
               delete[] m_sodaCells;
            }
            m_sodaCells = tempSodas;

            int* tempSodasInCell = new int[m_currentSlotsFilled + 1];
            for (int i = 0; i < m_currentSlotsFilled && m_sodasInCell; i++)
            {
               tempSodasInCell[i] = m_sodasInCell[i];
            }

            tempSodasInCell[m_currentSlotsFilled] = 1;
            m_currentSlotsFilled++;

            delete[] m_sodasInCell;
            m_sodasInCell = tempSodasInCell;

         }
         //}
         //else
         //{
         //   // Size the temp soda array
         //   Soda* tempSodas = new Soda[1]; // m_currentSlotsFilled + 1

         //   // tempSodas[0] = incSoda obj
         //   tempSodas[0] = soda;

         //   // Have the member variable point to the same area tempSodas is pointing to
         //   m_sodaCells = tempSodas;

         //   // Switched this to be above the incrementing part
         //   m_sodasInCell = new int[1];

         //   // Initialize the new slot to have a count of 1
         //   if (m_sodasInCell)
         //   {
         //      m_sodasInCell[0] = 1;
         //   }

         //   // increment slots
         //   m_currentSlotsFilled++;

         //}
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

   VendingMachine::~VendingMachine()
   {
      delete[] m_sodaCells;
      delete[] m_sodasInCell;
   }
}