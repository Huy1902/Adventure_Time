#ifndef PLAYINGSTATE_H_
#define  PLAYINGSTATE_H_
#include "BaseState.h"

#include <vector>

#include "ObjectModel.h"

class PlayingState :
    public BaseState
{
public:
    virtual void processData();
    virtual void renderState();
    virtual bool startState();
    virtual bool exitState();
    virtual std::string getStateID() const { return m_sPlaying; }

private:
    static const std::string m_sPlaying;
    std::vector<ObjectModel*> mObjects;
    static void m_sHomeToPlay();
    static void m_sExitHome();
};



#endif //PLAYINGSTATE_H_

