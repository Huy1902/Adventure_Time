#ifndef INTROSTATE_H_
#define INTROSTATE_H_
#include <string>

#include "BaseState.h"
class IntroState:
    public BaseState
{
public:
    IntroState();
    ~IntroState();

    virtual void processData();
    virtual void renderState();
    virtual bool startState();
    virtual bool exitState();
    virtual std::string getStateID() const { return m_sGameLoading; }

private:
    static const std::string m_sGameLoading;

    void fromIntroToHome();
};
#endif //INTROSTATE_H_

