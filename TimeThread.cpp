#include "TimeThread.h"
#include <unistd.h>

TimeThread::TimeThread(QObject*)
{
    stopped = true;
}

void TimeThread::run()
{
    stopped = false;
    while(!stopped)
    {
        updateWindow->update();
        usleep(500000);

    }
}

void TimeThread::setWindow(QMainWindow *inWindow)
{
    updateWindow = inWindow;
}

void TimeThread::stop()
{
    stopped = true;
}

bool TimeThread::isRunning()const
{
    return stopped;
}
