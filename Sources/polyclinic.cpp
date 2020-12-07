#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include "..\Headers\polyclinic.h"
#include "..\Headers\person.h"


Polyclinic::Polyclinic(std::string name, const std::function<bool(Person*&)> func) : creteria(func) {
    this->name = name;
}

Polyclinic::Polyclinic(std::string filePath, std::string name, const std::function<bool(Person*&)> func) : creteria(func) {
    this->name = name;
    std::ifstream stream(filePath);
    if (stream) {
        std::string temp, name;
        while (stream >> temp) {
            name = temp;
            stream >> temp;
            name += ' ' + temp;
            stream >> temp;
            name += ' ' + temp;
            stream >> temp;
            Person::Gender gender = (temp == "M") ? Person::male : Person::female;
            stream >> temp;
            Person* person;
            if (temp == "M") {
                stream >> temp;
                std::string qualification = temp;
                stream >> temp;
                Medic::Grade grade = (temp == "1") ? Medic::first : (temp == "2") ? Medic::second : Medic::highest;
                stream >> temp;
                int experience = std::stoi(temp);
                person = new Medic(name, gender, qualification, experience, grade);
            }
            else {
                stream >> temp;
                int age = std::stoi(temp);
                stream >> temp;
                int insuranceId = std::stoi(temp);
                person = new Patient(name, gender, age, insuranceId); 
            }
            if (creteria(person)) {
                persons.push_back(person);
            }
        }
        persons.sort([](Person*& obj1, Person*& obj2) {
            return obj1->getGender() < obj2->getGender();
        });
    }
    persons.sort([](Person*& obj1, Person*& obj2) {
        return obj1->getGender() < obj2->getGender();
    });
    stream.close();
}

Polyclinic::~Polyclinic() {
    while (!persons.empty()) {
        Person* temp = persons.front();
        persons.erase(persons.begin());
        delete temp;
        temp = nullptr;
    }
}

bool Polyclinic::hireMedic(Medic* hiredMedic) {
    bool success = false;
    auto it = std::find_if(persons.begin(), persons.end(), [&hiredMedic](Person*& obj) {
        return dynamic_cast<Medic*>(obj) != nullptr && obj->getFullName() == hiredMedic->getFullName();
    });
    if (it == persons.end()) {
        success = true;
        addPerson(hiredMedic);
    }
    return success;
}

bool Polyclinic::fireMedic(std::string name) {
    bool success = false;
    auto it = std::find_if(persons.begin(), persons.end(), [&name](Person*& obj) {
        return dynamic_cast<Medic*>(obj) != nullptr && obj->getFullName() == name;
    });
    if (it != persons.end()) {
        success = true;
        Person* temp = *it;
        persons.erase(it);
        delete temp;
        temp = nullptr;
    }
    return success;
}

bool Polyclinic::addPatient(Patient* addedPatient) {
    bool success = false;
    auto it = std::find_if(persons.begin(), persons.end(), [&addedPatient](Person*& obj) {
        return dynamic_cast<Patient*>(obj) != nullptr && ((Patient*)obj)->getFullName() == addedPatient->getFullName() && ((Patient*)obj)->getInsuranceId() == addedPatient->getInsuranceId();
    });
    if (it == persons.end()) {
        success = true;
        addPerson(addedPatient);
    }
    return success;
}

bool Polyclinic::removePatient(std::string name) {
    bool success = false;
    auto it = std::find_if(persons.begin(), persons.end(), [&name](Person*& obj) {
        return dynamic_cast<Patient*>(obj) != nullptr && obj->getFullName() == name;
    });
    if (it != persons.end()) {
        success = true;
        Person* temp = *it;
        persons.erase(it);
        delete temp;
        temp = nullptr;
    }
    return success;
}

void Polyclinic::addPerson(Person* addedPerson) {
    if (creteria(addedPerson)) {
        persons.insert(std::find_if(persons.begin(), persons.end(), [&addedPerson](Person*& obj) {
            return addedPerson->getGender() <= obj->getGender();
        }), addedPerson);
    }    
}

void Polyclinic::printAllMembers(std::ostream& stream) {
    stream << "List of all members: \n";
    std::for_each(persons.begin(), persons.end(), [&stream](Person*& obj) {
        stream << obj->getPersonInfo() << std::endl;
    });
}

void Polyclinic::printAllMedics(std::ostream& stream) {
    std::for_each(persons.begin(), persons.end(), [&stream](Person*& obj) {
        if (dynamic_cast<Medic*>(obj) != nullptr) {
            stream << obj->getPersonInfo() << std::endl;
        }
    });
}

void Polyclinic::printAllPatients(std::ostream& stream) {
    std::for_each(persons.begin(), persons.end(), [&stream](Person*& obj) {
        if (dynamic_cast<Patient*>(obj) != nullptr) {
            stream << obj->getPersonInfo() << std::endl;
        }
    });
}