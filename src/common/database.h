#pragma once
#include "tier0/memdbgon.h"

class ThreadOperation
{
public:
    ThreadOperation()
    {
        created = std::chrono::steady_clock::now();
    }

    virtual ~ThreadOperation() = default;

    virtual void RunThreadPart() = 0;
    virtual void CancelThinkPart() = 0;
    virtual void RunThinkPart() = 0;

    int timeout_ms = -1; // -1 = disabled
    std::chrono::steady_clock::time_point created;

    bool IsTimedOut() const
    {
        if (timeout_ms <= 0)
            return false;

        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   now - created)
                   .count() > timeout_ms;
    }

    virtual void OnTimeout()
    {
        Warning("Failed: operation timed out\n");
    }
};