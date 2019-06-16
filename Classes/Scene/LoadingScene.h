#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include"cocos2d.h"
#include"ui/CocosGUI.h"

class LoadingScene :public cocos2d::Layer
{
private:
	void endLoading(float dt);
	void createBackground();
	void loadSound();
	void loadImage();
	void loadSpriteFrame();

	cocos2d::ui::LoadingBar* createLoadingBar();
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(LoadingScene);
};

#endif //__LOADING_SCENE_H__
