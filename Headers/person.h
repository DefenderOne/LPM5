#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person {
public:
    enum Gender {
        male,
        female
    };
protected:
    std::string fullName;
    Gender gender;
public:
    Person(std::string fullName, Gender gender);
    std::string getFullName() const;
    Gender getGender() const;;
    virtual std::string getPersonInfo() = 0;
};

class Patient : public Person {
private:
    int age;
    int insuranceId;
public:
    Patient(std::string fullName, Gender gender, int age, int insuranceId);
    int getInsuranceId() const;
    int getAge() const;
    std::string getPersonInfo();
};


class Medic : public Person {
public:
enum Grade {
    first,
    second,
    highest
};
private:
    std::string qualification;
    int experience;
    Grade grade;
public:
    Medic(std::string fullName, Gender gender, std::string qualification, int experience, Grade grade);
    std::string getPersonInfo();
};

#endif