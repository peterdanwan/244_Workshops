#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "soda.h"

namespace sdds
{
   Soda::Soda(int mL, double price, const char* name)
   {
      // Works because we've told the compiler how to cast a
      // Soda object as a bool.
      if (set(mL, price, name))
      {
         std::cout << "SUCCESS: Soda details have been set up properly.\n";
      }
      else
      {
         std::cout << "ERROR: Incorrect soda details.\n";
      }
   }

   Soda::Soda(const Soda& soda)
   {
      // Reusing the copy assignment operator's logic.
      *this = soda;
   }

   Soda& Soda::operator=(const Soda& soda)
   {
      // Self-assignment check
      if (this != &soda)
      {
         /*****************************************
         * Deep Copy                              *
         ******************************************/
         // Delete existing dynamic memory
         delete[] m_name;  // How you create dynamic memory is how you delete it
                           //(i.e., if you created dynamic memory with [] you must delete with [])

         m_name = nullptr; // necessary.

         // Check if m_name stores a non-nullptr address, and the first character 
         if (soda.m_name)
         {
            // necessary 
            m_name = new char[std::strlen(soda.m_name) + 1];
            std::strcpy(m_name, soda.m_name);
         }

         /*****************************************
         * Static memory                          *
         ******************************************/
         m_mL = soda.m_mL;
         m_price = soda.m_price;

      }

      return *this;
   }

   Soda& Soda::set(int mL)
   {
      if (mL >= 100 && mL <= 255)
      {
         m_mL = mL;
      }
      else
      {
         setEmpty();
      }

      return *this;
   }

   Soda& Soda::set(double price)
   {
      if (price >= 0.0)
      {
         m_price = price;
      }
      else
      {
         setEmpty();
      }

      return *this;
   }

   Soda& Soda::set(const char* name)
   {
      if (name && name[0])
      {
         delete[] m_name;
         m_name = new char[std::strlen(name) + 1];
         m_name = std::strcpy(m_name, name);
      }
      else
      {
         setEmpty();
      }

      return *this;
   }

   Soda& Soda::set(int ml, double price, const char* name)
   {
      set(ml);
      set(price);
      set(name);
      
      return *this;
   }

   Soda& Soda::setEmpty()
   {
      if (m_name)
      {
         delete[] m_name;
         m_name = nullptr;
      }

      m_mL = 0;
      m_price = 0.0;

      return *this;
   }

   std::ostream& Soda::display(std::ostream& os) const
   {
      if (*this)
      {
         os << "-------------------------------------------------\n";
         os << "| Soda Name    | Volume (mL)       | Price       \n";
         os << "-------------------------------------------------\n";

         os << '|' << std::setw(14) << m_name
            << '|' << std::setw(19) << m_mL
            << '|' << std::setw(13) << m_price << std::endl;
         os << "-------------------------------------------------\n";
      }
      else
      {
         os << "Invalid Soda Details! Set the Soda object.\n";
      }


      return os;
   }

   std::istream& Soda::read(std::istream& is)
   {
      char tempName[50 + 1]{};
      double tempPrice{};
      int tempMl{};

      is.getline(tempName, 50 + 1, ',');

      if (m_name)
      {
         delete[] m_name;
      }

      if (tempName && tempName[0]) {
         m_name = new char[std::strlen(tempName) + 1];
         std::strcpy(m_name, tempName);
      }

      is >> tempPrice;
      is.ignore();

      is >> tempMl;
      is.ignore();

      if (tempPrice > 0.0) {
         m_price = tempPrice;
      }

      if (tempMl >= 100 && tempMl <= 255) {
         m_mL = tempMl;
      }

      return is;
   }

   // To allow casting of a Soda object to a bool
   Soda::operator bool() const
   {
      return m_mL >= 100 && m_mL <= 255 && m_price > 0.0 && (m_name && m_name[0]);
   }

   Soda::~Soda()
   {
      delete[] m_name;
   }

   std::istream& operator>>(std::istream& is, Soda& soda)
   {
      return soda.read(is);
   }

   std::ostream& operator<<(std::ostream& os, const Soda& soda)
   {
      return soda.display(os);
   }


}