#ifndef PLAYINGSTATE_H_
#define PLAYINGSTATE_H_
#include "BaseState.h"

#include <vector>

#include "Map.h"

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
    //std::vector<ObjectModel*> mObjects;

    //static void m_sPlayingToHome();
    static void m_sPlayingToPause();
    static void m_sPlayingToGameOver();
    Map* mMap;

    bool m_bSetupDying = false;

    bool m_bSetupRevive = true;
};



#endif //PLAYINGSTATE_H_

