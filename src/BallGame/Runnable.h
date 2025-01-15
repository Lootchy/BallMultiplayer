#pragma once
#include <Windows.h>


class Runnable
{
public:
    virtual ~Runnable() {}
    static DWORD WINAPI run_thread(LPVOID args)
    {
        Runnable* prunnable = static_cast<Runnable*>(args);
        return 0;
    }
protected:
    virtual DWORD run() = 0;
};