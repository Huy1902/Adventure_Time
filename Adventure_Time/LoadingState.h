#pragma once
#include "BaseState.h"

#include "Background.h"
class LoadingState :
    public BaseState
{
public:
    LoadingState();
    ~LoadingState();

    virtual void processData();
    virtual void renderState();
    virtual bool startState();
    virtual bool exitState();
    virtual std::string getStateID() const { return m_sGameLoading; }

private:
    static const std::string m_sGameLoading;

    int mCountToPlay = 10;
};