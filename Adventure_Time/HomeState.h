#ifndef HOMESTATE_H_
#define HOMESTATE_H_

#include "BaseState.h"
#include "Background.h"


class HomeState :
    public BaseState
{
public:
    HomeState();
    ~HomeState();

    virtual void processData();
    virtual void renderState();
    virtual bool startState();
    virtual bool exitState();
    virtual std::string getStateID() const { return m_sHomeID; }

private:
    static const std::string m_sHomeID;
    //std::vector<ObjectModel*> mObjects;
    //std::vector<std::string> textureID;
    std::vector<callback> mCallback;
    std::vector<Texture> mTexture;
    std::vector<Info> mButton;
    ObjectModel* font;
    Background* background;
    static void m_sHomeToPlay();
    static void m_sExitHome();
    static void m_sHomToScore();
};

#endif //HOMESTATE_H_

