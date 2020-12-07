#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <list>
#include <string>
#include <Windows.h>
#include "..\Headers\person.h"
#include "..\Headers\polyclinic.h"

void callMenu() {
    std::cout << "1. Print all members of the clinic\n";
    std::cout << "2. Print all medic workers of the clinic\n";
    std::cout << "3. Print all patients of the clinic\n";
    std::cout << "4. Hire a medic worker\n";
    std::cout << "5. Fire a medic worker by name\n";
    std::cout << "6. Add a patient from the list\n";
    std::cout << "7. Remove a patient from the list\n";
    std::cout << "8. Exit program\n";
}

int main() {
    // Доделать вывод кол-ва пациентов и врачей в каждом списке
    std::cout << "Enter a name of an input file: ";
    std::string filePath;
    std::cin >> filePath;

    std::cout << "Specify a polyclinic's name: ";
    std::string clinicName;
    std::cin >> clinicName;

    std::cout << "Type age you want patients with age under be removed from the list: ";
    int age;
    std::cin >> age;
    struct Creteria {
        int age;
        Creteria(int num) : age(num) { }
        bool operator()(Person*& obj) {
            return dynamic_cast<Medic*>(obj) != nullptr || dynamic_cast<Patient*>(obj) != nullptr && (obj->getGender() == Person::female || obj->getGender() == Person::male && ((Patient*)obj)->getAge() <= age);
        }
    };
    Polyclinic poly(filePath, clinicName, Creteria(age));
    char input;
    bool isExit;
    do {
        callMenu();
        std::cin >> input;
        if (input == '8') isExit = true;
        else if (!isExit && input >= '1' && input <= '7') {
            switch (input) {
                case '1': {
                    // tested
                    poly.printAllMedics();
                    break;
                }
                case '2': { 
                    // tested
                    poly.printAllMedics();
                    break;
                }
                case '3': {
                    // tested
                    poly.printAllPatients();
                    break;
                }
                case '4': {
                    std::string temp;
                    std::cout << "Specify hired worker's name: ";
                    std::string name;
                    std::cin >> name;
                    std::getline(std::cin, temp);
                    name += temp;
                    std::cout << "Gender[M(ale)/F(emale)]: ";
                    std::cin >> temp;
                    Person::Gender gender = (temp == "M" || temp == "Male") ? Person::male : Person::female;
                    std::cout << "Qualification: ";
                    std::cin >> temp;
                    std::string qualification = temp;
                    std::cout << "1. First\n2. Second\n3. Highest\n";
                    std::cin >> temp;
                    Medic::Grade grade = (temp == "1") ? Medic::first : (temp == "2") ? Medic::second : Medic::highest;
                    std::cin >> temp;
                    int experience = std::stoi(temp);
                    Medic* medic = new Medic(name, gender, qualification, experience, grade);
                    poly.hireMedic(medic);
                    break;
                }
                case '5': {
                    std::cout << "Specify fired worker's name: ";
                    std::string name, temp;
                    std::cin >> name;
                    std::getline(std::cin, temp);
                    name += temp;
                    if (poly.fireMedic(name)) {
                        std::cout << name << " was fired from the clinic\n";
                    }
                    else {
                        std::cout << "There's no " << name << " working in the clinic\n";
                    }
                    break;
                }
                case '6': {
                    std::cout << "Specify added patient's name: ";
                    std::string name, temp;
                    std::cin >> name;
                    std::getline(std::cin, temp);
                    name += temp;
                    std::cout << "Gender[M(ale)/F(emale)]: ";
                    std::cin >> temp;
                    Person::Gender gender = (temp == "M" || temp == "Male") ? Person::male : Person::female;
                    std::cout << "Age: ";
                    std::cin >> temp;
                    int age = std::stoi(temp);
                    std::cout << "Insurance ID: ";
                    std::cin >> temp;
                    int insuranceId = std::stoi(temp);
                    Patient* patient = new Patient(name, gender, age, insuranceId); 
                    poly.addPatient(patient);
                    break;
                }
                case '7': {
                    std::cout << "Specify removed patient's name: ";
                    std::string name, temp;
                    std::cin >> name;
                    std::getline(std::cin, temp);
                    name += temp;
                    if (poly.removePatient(name)) {
                        std::cout << name << " was removed from the patient list\n";
                    }
                    else {
                        std::cout << "There's no " << name << " in the patient list\n";
                    }
                    break;
                }
            }
        }
        std::cout << std::endl;
    } while (!isExit || input < '1' && input > 8);
}