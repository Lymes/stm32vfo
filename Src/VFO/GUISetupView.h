/*
 * GUISetupView.h
 *
 *  Created on: Apr 6, 2018
 *      Author: lymes
 */

#ifndef VFO_GUISETUPVIEW_H_
#define VFO_GUISETUPVIEW_H_

#include "GuiView.h"
#include "GUI/Background.h"


namespace VFO
{

typedef int32_t (*GetConfigValue)();
typedef void (*SetConfigValue)(int32_t);
typedef void (*CommandPtr)();

struct SetupItem {
	const char *name;
	GetConfigValue getter;
	SetConfigValue setter;
	CommandPtr cmd;
	int numChildren;
	SetupItem *children;
};


class GUISetupView : public GUIView
{
	GradientBox *_window;
	GradientBox *_header;
	GradientBox *_btnBack;
	GradientBox *_selection;

	bool _editing = false;
	uint8_t _selectedItem = 0;
	const struct SetupItem *_currentItem;
	GUISetupView *_parent;
	GUISetupView *_selectedChild;
	int16_t _encCounter = 0;


public:
	GUISetupView();
	GUISetupView(SetupItem *item, GUISetupView *parent);
	virtual ~GUISetupView();
	void init();

	virtual void draw();
	virtual void pushEncoderIncrement(int16_t increment);
	virtual void menuKeyPressed();

	void setParent( GUISetupView *p ) { _parent = p; }
	void setSelectedChild( GUISetupView *child );
	void setSelected( uint8_t selected );
	void updateValues();

private:
	void drawBackground();
	void drawWindowTitle(void);
	void drawItemTitle(uint8_t itemIndex, bool selected);
	void drawValue(uint8_t itemIndex, bool selected, bool edited);
	void drawBackButton(bool selected);
};

} /* namespace VFO */

#endif /* VFO_GUISETUPVIEW_H_ */
