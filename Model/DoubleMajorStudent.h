#ifndef TA_19_DOUBLEMAJORSTUDENT_H
#define TA_19_DOUBLEMAJORSTUDENT_H

#include "Student.h"


class DoubleMajorStudent : public Student {

private:
    std::string major2;

public:

    DoubleMajorStudent() : Student() {}   // must be private
    DoubleMajorStudent(const std::string& studentId, std::string first, std::string last , double workHours,
            std::vector<std::string> passedCourses, std::map<std::string, double> currentSemesterCourses,
                       std::string major2);

    double calculateSalary() const override;

};


#endif //TA_19_DOUBLEMAJORSTUDENT_H
