#include "RunningContext.h"
namespace ThreadsUtils {

RunningContext::RunningContext():
m_isRunning(false)
{}

RunningContext::~RunningContext()
{}

void RunningContext::Start()
{
    std::lock_guard<std::mutex> guard(m_runningMutex);
    if (IsCanStart())
    {
        if (!IsRunning())
        {
            m_isRunning = StartInternal();
        }
    }
}

void RunningContext::Stop()
{
    std::lock_guard<std::mutex> guard(m_runningMutex);
    if (IsRunning())
    {
        m_isRunning = StopInternal();
    }
}

bool RunningContext::IsRunning()
{
    return m_isRunning;
}

}