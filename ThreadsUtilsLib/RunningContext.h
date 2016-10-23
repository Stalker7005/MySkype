#pragma once
#include <mutex>

namespace ThreadsUtils {
class RunningContext
{
public:
    RunningContext();
    virtual ~RunningContext();

public:
    virtual void Start();
    virtual void Stop();
    virtual bool IsRunning();
   
protected:
    virtual bool StartInternal() = 0;
    virtual bool StopInternal() = 0;
    virtual bool IsCanStart() = 0;

private:
    bool m_isRunning;
    std::mutex m_runningMutex;
};
}