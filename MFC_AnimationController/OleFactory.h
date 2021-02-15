#pragma once
#include <afxdisp.h>

/*AfxOleInit must be initialize once.*/
class OleFactoryClass
{
    public:
    static OleFactoryClass& getInstance()
    {
        if (instance_ == nullptr)
        {
            static OleFactoryClass instance;
            instance_ = &instance;
        }

        return *instance_;
    }

    private:
    static OleFactoryClass* instance_;
    OleFactoryClass() {
        AfxOleInit();
    };

    ~OleFactoryClass() {
        AfxOleTerm(FALSE);
    }
};

OleFactoryClass* OleFactoryClass::instance_ = nullptr;