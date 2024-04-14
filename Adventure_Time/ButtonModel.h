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
	int getCallbackID() const
	{
		return mCallbackID;
	}

	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();
	virtual ~ButtonModel();

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	void(*mCallback)();
	bool m_bReleased;
	int mCallbackID;
};

#endif //BUTTONMODEL_H_