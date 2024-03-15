#pragma once
#include "BaseState.h"

#include <vector>

#include "ObjectModel.h"

class PauseState :
    public BaseState
{
public:
    virtual void processData();
    virtual void renderState();
    virtual bool startState();
    virtual bool exitState();
    virtual std::string getStateID() const { return m_sPause; }

private:
    static const std::string m_sPause;
    std::vector<ObjectModel*> mObjects;
    static void m_sPauseToPlay();
    static void m_sPauseToHome();

};

