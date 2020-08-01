#include "DoubleMajorStudent.h"
#include <regex>


using namespace std;

bool validate(const string& str, const string& ptn){
    regex pattern{ptn};
    return regex_match(str, pattern);
}


DoubleMajorStudent::DoubleMajorStudent(const std::string& studentId, std::string first, std::string last , double workHours,
                 std::vector<std::string> passedCourses, std::map<std::string, double> currentSemesterCourses,std::string major2)
        : Student(studentId,(std::move(first)), (std::move(last)), workHours , std::move(passedCourses) , std::move(currentSemesterCourses))
        , major2{std::move(major2)}
{
    if( !validate( studentId, "\\d{9}") ) {
        throw invalid_argument("Student ID must have 9 digits!!");
    }
    this->setStudentId(studentId);
}


DoubleMajorStudent::DoubleMajorStudent(const std::string& studentId, std::string first, std::string last , double workHours,
                                       std::vector<std::string> passedCourses, std::map<std::string, double> currentSemesterCourses)
        : Student(studentId,(std::move(first)), (std::move(last)), workHours , std::move(passedCourses) , std::move(currentSemesterCourses))

{
    if( !validate( studentId, "\\d{9}") ) {
        throw invalid_argument("Student ID must have 9 digits!!");
    }
    this->setStudentId(studentId);
}


double DoubleMajorStudent::calculateSalary() const{
    return 6500 * getWorkHours();
}