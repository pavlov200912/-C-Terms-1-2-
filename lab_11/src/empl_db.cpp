#include "employees.h"
#include <string>
#include <iostream>
#include <fstream>

int main() {
    EmployeesArray employeesArray;
    while(true) {
        std::string command;
        std::cin >> command;
        if(command == "load") {
            std::string file_name;
            std::cin >> file_name;
            std::ifstream input(file_name, std::ios::binary);
            input >> employeesArray;
        } else if(command == "list") {
            std::cout << employeesArray;
        } else if(command == "add") {
            int type = 0;
            std::cin >> type;
            if (type == 1) {
                Developer* dev = new Developer();
                std::cin >> *dev;
                employeesArray.add(dev);
            } else if (type == 2) {
                SalesManager* seller = new SalesManager();
                std::cin >> *seller;
                employeesArray.add(seller);
            }
        } else if(command == "save") {
            std::string file_name;
            std::cin >> file_name;
            std::ofstream output(file_name, std::ios::binary);
            output << employeesArray;
        } else if(command == "exit") {
            break;
        }
    }
}
