#ifndef SCORES_H
#define SCORES_H
#include <string>
#include <chrono>

using namespace std;

class Score
{
public:
    Score(const string& inName,const std::chrono::time_point<std::chrono::system_clock>& inDate,const std::chrono::duration<double>& inTime);
    Score(const string& inName,const int inMonth,const int inDay,const int inYear,const int inSeconds);
    bool operator<(const Score& rhs) const;
    string getScore()const;
    string toFile()const;
    ~Score();
private:
    string name;
    int month;
    int day;
    int year;
    int time;
};


#endif // SCORES_H
