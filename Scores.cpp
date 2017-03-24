#include "Scores.h"
#include <sstream>
#include <ctime>
#include <math.h>
using namespace std;

Score::Score(const string &inName, const std::chrono::time_point<chrono::_V2::system_clock> &inDate, const std::chrono::duration<double> &inTime):
    name(inName)
{
    time_t theDate = chrono::system_clock::to_time_t(inDate);
    tm* dateFormat = localtime(&theDate);
    month = dateFormat->tm_mon;
    day = dateFormat->tm_mday;
    year = dateFormat->tm_year+1900;
    time = (int)floor(inTime.count());
}

Score::Score(const string &inName, const int inMonth, const int inDay, const int inYear, const int inSeconds):name(inName)
{
    month = inMonth;
    day = inDay;
    year = inYear;
    time = inSeconds;
}

string Score::getScore()const
{
    ostringstream oss;
    oss << month << "/" << day << "/" << year << "   " << name << "         " << time << "s";

    return oss.str();
}
string Score::toFile()const
{
    ostringstream oss;
    oss << month << endl << day << endl << year << endl << name << endl << time << endl;
    return oss.str();
}

Score::~Score()
{}
