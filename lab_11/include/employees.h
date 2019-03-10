#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <cstring>
#include <ostream>
#include <fstream>
class Employee{
public:
    virtual int salary() const = 0;
    Employee(){}
    Employee(char* name, int32_t base_salary);
    virtual ~Employee();
    virtual void term_output(std::ostream& os) const = 0;
    virtual std::ostream & file_output(std::ostream &os) const;
    friend std::ostream& operator<<(std::ostream& os, const Employee& emp);
protected:
    char* _name;
    int32_t _base_salary;
};


class Developer : public Employee{
public:
    int salary() const override {
        int salary = _base_salary;
        if (_has_bonus) { salary += 1000; }
        return salary;
    }
    void term_output(std::ostream& os) const override;
    std::ostream & file_output(std::ostream &os) const override;

    friend std::ostream& operator<<(std::ostream& os, const Developer& dev);
    friend std::istream& operator>>(std::istream& ios, Developer& dev);
    friend std::ifstream& operator>>(std::ifstream& ios, Developer& dev);
private:
    bool _has_bonus;
};


class SalesManager : public Employee{
public:
    int salary() const override {
        return int(_base_salary + _sold_nm * _price * 0.01);
    }
    void term_output(std::ostream& os) const override;

    std::ostream & file_output(std::ostream &os) const override;

    friend std::ostream& operator<<(std::ostream& os, const SalesManager& seller);
    friend std::istream& operator>>(std::istream& ios, SalesManager& seller);
    friend std::ifstream& operator>>(std::ifstream& ios, SalesManager& seller);
private:
    int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
    EmployeesArray();
    ~EmployeesArray();

    void add(Employee *e);

    int total_salary() const;

    friend std::ostream& operator<<(std::ostream& os, const EmployeesArray& array);
    friend std::ofstream& operator<<(std::ofstream& os, const EmployeesArray& array);
    friend std::ifstream& operator>>(std::ifstream& ios, EmployeesArray& array);
private:
    Employee **_employees;
    int _capacity;
    int _size;
};

#endif
