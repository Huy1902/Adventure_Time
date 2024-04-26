#ifndef SCORESTATE_H_
#define SCORESTATE_H
#include "BaseState.h"

#include "ObjectModel.h"
#include "Background.h"

class ScoreState :
    public BaseState
{
public:
    ScoreState();
    ~ScoreState();

    virtual void processData();
    virtual void renderState();
    virtual bool startState();
    virtual bool exitState();
    virtual std::string getStateID() const { return m_sScoreID; }

private:
    static const std::string m_sScoreID;
    //std::vector<ObjectModel*> mObjects;
    //std::vector<std::string> textureID;
    std::vector<callback> mCallback;
    std::vector<Texture> mTexture;
    std::vector<Info> mButton;
    std::vector<int> mStanding;
    ObjectModel* font;
    Background* background;

    static void m_sScoreToHome();
};

#endif //SCORESTATE_H

