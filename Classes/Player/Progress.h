#ifndef __PROGRESS_H__  
#define __PROGRESS_H_  

#include "cocos2d.h"  

using namespace cocos2d;
class Progress : public CCNode
{
public:
	Progress();

public:

	void Background(const char *pName);
	void Fill(const char *pName);
	void Total_progress(float total);
	void Current_progress(float progress);


private:
	void setForegroundTextureRect(const Rect &rect);

private:
	Sprite * m_progressBackground;
	Sprite *m_progressForeground;
	float  m_totalProgress;
	float  m_currentProgress;
	float  m_scale;
};

#endif