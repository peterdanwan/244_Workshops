#include <iostream>
#include <iomanip>
#include <fstream>
#include "soda.h"
#include "soda.h" // Intentional - test for header guards
#include "VendingMachine.h"

void printBanner(const char* msg, char c, int len)
{
   if (len < std::strlen(msg))
   {
      len = std::strlen(msg);
   }

   for (int i = 0; i < (len + 4); i++) {
      std::cout << c;
   }

   std::cout << std::endl;
   std::cout << c << std::left << ' ' << std::setw(len) << msg << ' ' << c << std::endl;

   for (int i = 0; i < (len + 4); i++) {
      std::cout << c;
   }
   std::cout << std::endl;
}

void printReport(std::ostream& os = std::cout){
   os << "-------------------------------------------------\n";
   os << "| Soda Name     | Volume (mL)       | Price ($)  \n";
   os << "-------------------------------------------------\n";
}


void test1()
{
   printBanner("Test 1: Test Default Constructor", '*', 20);
   sdds::Soda s1;
   s1.display();
   std::cout << std::endl;
}

void test2()
{
   printBanner("Test 2: Testing the overloaded \"set\" methods", '*', 20);
   
   // Set valid data individually
   sdds::Soda s2a;
   s2a.set(255);
   s2a.set(1.99);
   s2a.set("Coke");
   s2a.display(std::cout);

   // Set invalid data all at once
   sdds::Soda s2b;
   s2b.set(-1, 1.99, "Dr. Pepper");
   s2b.display(std::cout);

   std::cout << std::endl;
}

void test3() {
   printBanner("Test 3: Copy Constructor", '*', 20);
   sdds::Soda s3a(255, 2.00, "Cream Soda");
   sdds::Soda s3b(s3a);
   s3a.display();
   s3b.display();
   std::cout << std::endl;

   sdds::Soda s3c(500, 1.50, "Dr. Pepper");
   sdds::Soda s3d(s3c);
   s3c.display();
   s3d.display();

   std::cout << std::endl;
}

void test4() {
   printBanner("Test 4: Copy Assignment", '*', 20);
   sdds::Soda s1(255, 1.00, "Water");
   sdds::Soda s2;
   s2 = s1;
   s1.display();
   s2.display();
   std::cout << std::endl;

   sdds::Soda s3(-500, 1.50, "Dr. Pepper");
   sdds::Soda s4(215, 2.50, "Gatorade");
   s4 = s3;
   s3.display();
   s4.display();

   sdds::Soda s5(150, 1.50, "Dr. Pepper");
   sdds::Soda s6;
   s5 = s6;
   s5.display();
   s6.display();

   std::cout << std::endl;
}

int main()
{
   //// Test soda logic
   //test1();
   //test2();
   //test3();
   //test4();

   //// Test vending machine logic
   //sdds::Soda* sodas{};
   //std::streampos beg{};
   //int recCount{};

   //// Test
   //std::ifstream sodaFile("sodas.txt");
   //std::ofstream updatedSodas("updatedSodas.txt");
   //
   //// 
   //std::cout << "Reading sodas.txt\n";

   //char line[99 + 1]{};

   //// PW: 
   //// store init pos of the file cursor    
   ////beg = sodaFile.tellg();

   //while (sodaFile.getline(line, 99 + 1, '\n'))
   //{
   //   recCount++;
   //};

   //// PW: 
   //sodaFile.clear();
   //sodaFile.seekg(0);
   ////sodaFile.seekg(beg);

   //sodas = new sdds::Soda[recCount];

   //// Read and then display

   //printReport(std::cout);

   //for (int i = 0; i < recCount && sodaFile; i++)
   //{
   //   sodaFile >> sodas[i];
   //   sodas[i].display();
   //}
   //std::cout << std::endl;
   //// Write to the file

   //printReport(updatedSodas);
   //for (int i = 0; i < recCount; i++)
   //{
   //   updatedSodas << sodas[i];
   //}
   //std::cout << std::endl;

   
   sdds::Soda sodas[]{
      {255, 1.50, "Coke"},
      {255, 1.50, "Cream Soda"},
      {255, 1.50, "Mountain Dew"},
      {255, 1.50, "Cream Soda"}
   };

   sdds::VendingMachine vm(sodas, 4);


   return 0;
}