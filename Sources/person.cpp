#include "..\Headers\person.h"

Person::Person(std::string fullName, Gender gender) {
    this->fullName = fullName;
    this->gender = gender;
}

std::string Person::getFullName() const {
    return fullName;
}

Person::Gender Person::getGender() const {
    return gender;
}

int Patient::getInsuranceId() const {
    return insuranceId;
}

int Patient::getAge() const {
    return age;
}

Patient::Patient(std::string fullName, Gender gender, int age, int insuranceId) : Person(fullName, gender) {
    this->age = age;
    this->insuranceId = insuranceId;
}

std::string Patient::getPersonInfo() {
    return "Patient " + fullName + "(" + ((gender) ? "Female" : "Male") + "). Age: " + std::to_string(age) + " years. Insurance ID: " + std::to_string(insuranceId);
}

Medic::Medic(std::string fullName, Gender gender, std::string qualification, int experience, Grade grade) : Person(fullName, gender) {
    this->qualification = qualification;
    this->experience = experience;
    this->grade = grade;
}

std::string Medic::getPersonInfo() {
    return "Medic " + fullName + "(" + ((gender) ? "Female" : "Male") + "). Qualification: " + qualification + "(" + ((grade == 0) ? "First" : (grade == 1) ? "Second" : "Highest") + "). Experience: " + std::to_string(experience) + " years";
}