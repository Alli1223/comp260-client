#pragma once
#include "GUI.h"
#include "Texture.h"
class Icon : public GUI
{
public:
	//! Constructor
	Icon();
	//! Destructor
	~Icon();

	int getIconID() { return iconID; }
	int setIconID(int newIconID) { return iconID = newIconID; }

private:
	int iconID;
};

