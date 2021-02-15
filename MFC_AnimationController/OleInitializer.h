#pragma once
#include <afxwin.h>
#include "OleFactory.h"

class OleInitializer 
{
public:
    OleInitializer()
    {
        OleFactoryClass::getInstance();
    }
};

