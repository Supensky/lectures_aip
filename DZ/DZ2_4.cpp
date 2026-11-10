#include <ctime>
#include <iostream>
#include <string>
#include <vector>

struct Date {
    Date(int d=0, int m=0, int y=-9900000) {
        day = d;
        month = m;
        year = y;
    }

    int day;
    int month;
    int year;

    // Расчет возраста (полных лет)
    int age(Date today) const {
        if (year==-9900000)return -9900000;
        if ((today.month > month) || (today.month == month && today.day >= day)) {
            return today.year - year;
        } else {
            return today.year - year - 1;
        }
    }

    // Получение сегодняшней даты
    static Date today() {
        std::time_t t = std::time(nullptr);
        std::tm* lt = std::localtime(&t);
        return Date(lt->tm_mday, lt->tm_mon + 1, lt->tm_year + 1900);
    }
};

class Person {
private:
    std::string lastName;
    std::string firstName;
    std::string middleName;
    std::string gender;
    Date birthDate;

public:
    // Конструкторы
    Person() : lastName(""), firstName(""), middleName(""), gender(""), birthDate{1, 1, 2000} {}
    Person(std::string ln, std::string fn, std::string mn, std::string g,
        int d, int m, int y) {
        lastName = ln;
        firstName = fn;
        middleName = mn;
        gender = g;
        setBirthDate(d, m, y);
    }

    // Геттеры
    std::string getLastName() { return lastName; }
    std::string getFirstName() { return firstName; }
    std::string getMiddleName() { return middleName; }
    std::string getGender() const { return gender; }
    Date getBirthDate() const { return birthDate; }

    // Сеттеры
    void setLastName(std::string ln) { lastName = ln; }
    void setFirstName(std::string fn) { firstName = fn; }
    void setMiddleName(std::string mn) { middleName = mn; }
    void setGender(std::string g) { gender = g; }
    void setBirthDate(int d, int m, int y) {
        birthDate.day = d;
        birthDate.month = m;
        birthDate.year = y;
    }

    // Вывод данных
    void printInfo() const {
        std::cout << "Name: " << lastName << " " << firstName << " " << middleName << "\n"
        << "Gender: " << gender << "\n"
        << "Birth date: " << (birthDate.day < 10 ? "0" : "") << birthDate.day << "."
        << (birthDate.month < 10 ? "0" : "") << birthDate.month << "." << birthDate.year << "\n";
    }


};

class Student : public Person{
private:
    std::string course;
    std::string group;

public:
    // Конструкторы
    Student() : Person(), course(""), group("") {}
    Student(std::string ln, std::string fn, std::string mn, std::string g,
        int d, int m, int y, std::string c, std::string grp)
        : Person(ln, fn, mn, g, d, m, y), course(c), group(grp) {}

    // Геттеры
    std::string getCourse() { return course; }
    std::string getGroup() { return group; }

    // Сеттеры
    void setCourse(std::string c) { course = c; }
    void setGroup(std::string g) { group = g; }

    // Вывод данных
    void printInfo() const {
        Person::printInfo();
        std::cout << "Course: " << course << "\n" << "Group: " << group << "\n";
    }

    // Поиск по возрасту и полу
    friend std::vector<Student> findStudents(std::vector<Student> students, int age, std::string gender) {
        std::vector<Student> result;
        Date today = Date::today();
        for (const Student& s : students) {
            if ((s.getGender() == gender) && (s.getBirthDate().age(today) == age)) {
                result.emplace_back(s);
            }
        }
        return result;
    }

    friend void printList(const std::vector<Student>& students) {
        if (students.empty()) {
            std::cout << "Empty list";
        }
        for (const Student& s : students) {
            s.printInfo();
            std::cout << "\n";
        }
    }
};

int main() {
    std::cout << "Persons\n";
    Person person1("Ivanov", "Ivan", "Ivanovich", "Male", 5, 11, 2007);
    person1.printInfo();
    std::cout << "\n";

    Person person2;
    person2.setLastName("Kuznetsova");
    person2.setFirstName("Kate");
    person2.setMiddleName("Vladimirovna");
    person2.setGender("Female");
    person2.setBirthDate(27, 4, 2007);

    person2.printInfo();
    std::cout << "\n";

    std::cout << "Students\n";
    Student student1("Ivanov", "Ivan", "Ivanovich", "Male", 5, 11, 2007, "2", "IU5-33/6");
    student1.printInfo();
    std::cout << "\n";

    Student student2;
    student2.setLastName("Kuznetsova");
    student2.setFirstName("Kate");
    student2.setMiddleName("Vladimirovna");
    student2.setGender("Female");
    student2.setBirthDate(27, 4, 2007);
    student2.setCourse("2");
    student2.setGroup("SM4-32/6");
    student2.printInfo();
    std::cout << "\n";

    std::vector<Student> students;
    students.emplace_back("Ivanov", "Ivan", "Ivanovich", "Male", 5, 11, 2007, "2", "IU5-33/6");
    students.emplace_back("Kuznetsova", "Kate", "Vladimirovna", "Female", 27, 4, 2007, "2", "SM4-32/6");
    students.emplace_back("Popov", "Vladimir", "Ivanovich", "Male", 7, 11, 2007, "2", "IU5-33/6");
    students.emplace_back("Ivanova", "Anastasia", "Andreevna", "Female", 21, 10, 2007, "2", "SM4-32/6");
    students.emplace_back("Sidorov", "Anrey", "Olegovich", "Male", 12, 8, 2007, "2", "SM4-32/6");
    students.emplace_back("Sidorova", "Maria", "Ivanovna", "Female", 5, 6, 2006, "3", "IU5-53/6");
    students.emplace_back("Kuznetsova", "Natalia", "Alexeevna", "Female", 5, 11, 2006, "3", "SM4-52/6");

    std::cout << "Found students:\n";
    printList(findStudents(students, 19, "Male"));

    return 0;
}
