#ifndef TIMETHREAD_H
#define TIMETHREAD_H
#include "QThread"
#include "QMainWindow"

class TimeThread : public QThread
{
    Q_OBJECT
public:
    explicit TimeThread(QObject* = 0);
    void setWindow(QMainWindow* inWindow);
    void stop();
    bool isRunning()const;
protected:
    void run();
private:
    volatile bool stopped;
    QMainWindow* updateWindow;
};


#endif // TIMETHREAD_H
