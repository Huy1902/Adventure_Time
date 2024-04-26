#pragma once
#include "BaseState.h"

#include <vector>

#include "ObjectModel.h"
#include "Background.h"

class PauseState :
    public BaseState
{
public:
    PauseState();
    ~PauseState();

    virtual void processData();
    virtual void renderState();
    virtual bool startState();
    virtual bool exitState();
    virtual std::string getStateID() const { return m_sPauseID; }

private:
    static const std::string m_sPauseID;
    //std::vector<ObjectModel*> mObjects;
    //std::vector<std::string> textureID;
    std::vector<callback> mCallback;
    std::vector<Texture> mTexture;
    std::vector<Info> mButton;
    ObjectModel* font;
    Background* background;

    static void m_sPauseToHome();
    static void m_sPauseToPlay();

};