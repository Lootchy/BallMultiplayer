#pragma once
#include <iostream>     
#include <string>       
#include "Runnable.h"


class Thread : public Runnable
{
public:
    Thread(const std::string& printMessage) : message(printMessage) {}
    void newthread();
    DWORD run() override;

private:
    std::string message;
};
