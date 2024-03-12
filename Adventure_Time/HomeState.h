#ifndef HOMESTATE_H_
#define HOMESTATE_H_

#include "BaseState.h"

#include <vector>
#include "ObjectModel.h"

class HomeState :
    public BaseState
{
public:
    virtual void processData();
    virtual void renderState();
    virtual bool startState();
    virtual bool exitState();
    virtual std::string getStateID() const { return m_sHomeID; }

private:
    static const std::string m_sHomeID;
    std::vector<ObjectModel*> mObjects;
    static void m_sHomeToPlay();
    static void m_sExitHome();
};

#endif //HOMESTATE_H_

