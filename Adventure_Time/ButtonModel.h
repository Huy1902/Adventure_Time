#ifndef BUTTONMODEL_H_
#define BUTTONMODEL_H_

#include "ObjectModel.h"

class ButtonModel :
    public ObjectModel
{
public:
	ButtonModel();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);
	void setCallback(void(*callback)()) { mCallback = callback; }

	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	void(*mCallback)();
	bool m_bReleased;
};

#endif //BUTTONMODEL_H_

