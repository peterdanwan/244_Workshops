#ifndef SDDS_SODA_H
#define SDDS_SODA_H
#include <iostream>
namespace sdds
{
   class Soda
   {
      int m_mL{};
      double m_price{};
      char* m_name{};
   public:
      Soda(int mL, double price, const char* name = nullptr); // How many signatures do we have?
      Soda() = default;
      Soda(const Soda& soda);
      Soda& operator=(const Soda& soda);
      Soda& set(int ml);
      Soda& set(double price);
      Soda& set(const char* name);
      Soda& set(int ml, double price, const char* name);
      Soda& setEmpty();
      std::ostream& display(std::ostream& os = std::cout)const;
      std::istream& read(std::istream& is = std::cin);
      operator bool()const;
      virtual ~Soda();
   };




   std::istream& operator>>(std::istream& is, Soda& soda);
   std::ostream& operator<<(std::ostream& os, const Soda& soda);

}

#endif // !SDDS_SODA_H