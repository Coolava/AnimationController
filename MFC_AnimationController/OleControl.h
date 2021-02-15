#pragma once
#include <afxwin.h>
#include "OleFactory.h"

class OleControl :
    public CWnd
{
public:
    OleControl()
    {
        OleFactoryClass::getInstance();
    }
};

