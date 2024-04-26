#ifndef GAMEOVERSTATE_H_
#define GAMEOVERSTATE_H_
#include "BaseState.h"

#include "Background.h"
class GameOverState :
    public BaseState
{
public:
    GameOverState();
    ~GameOverState();

    virtual void processData();
    virtual void renderState();
    virtual bool startState();
    virtual bool exitState();
    virtual std::string getStateID() const { return m_sGameOverID; }

private:
    static const std::string m_sGameOverID;
    //std::vector<ObjectModel*> mObjects;
    //std::vector<std::string> textureID;
    std::vector<callback> mCallback;
    std::vector<Texture> mTexture;
    std::vector<Info> mButton;
    ObjectModel* font;
    Background* background;
    static void m_sGameOverToPlay();
    static void m_sGameOverToHome();
};
#endif

