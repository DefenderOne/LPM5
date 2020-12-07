#ifndef POLYCLINIC_H
#define POLYCLINIC_H

#include <iostream>
#include <functional>
#include <string>
#include <list>
#include "person.h"

class Polyclinic {
private:
    std::function<bool(Person*&)> creteria;
    std::string name;
    std::list<Person*> persons;
    void addPerson(Person* addedPerson);
public:
    Polyclinic(std::string name, const std::function<bool(Person*&)> creteria);
    Polyclinic(std::string filePath, std::string name, const std::function<bool(Person*&)> creteria);
    ~Polyclinic();
    bool hireMedic(Medic* hiredMedic);
    bool fireMedic(std::string name);
    bool addPatient(Patient* addedPatient);
    bool removePatient(std::string name);

    void printAllMembers(std::ostream& stream = std::cout);
    void printAllMedics(std::ostream& stream = std::cout);
    void printAllPatients(std::ostream& stream = std::cout);
};


class Test {
    std::function<bool(int)> creteria;
    public:
    Test(const std::function<bool(int)>& func);
    bool proceed(int num);
};
#endif