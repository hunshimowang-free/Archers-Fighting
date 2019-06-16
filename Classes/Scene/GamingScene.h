#ifndef __GAMING_SCENE_H__
#define __GAMING_SCENE_H__

#include"cocos2d.h"
#include"Scene/Map.h"
#include"Player/Player.h"
#include"Player/Weapon.h"
#include"Player/Exp_Progress.h"

#include <vector>
#include<iostream>
#define MAX_NUM_BLOOD 50
#define MAX_NUM_EXE 100
USING_NS_CC;
using namespace std;
typedef enum {
	player01 = 1,
	player02 = 2,
	player03 = 3,
	player04 = 4
}Player_TAG;



class Gaming :public cocos2d::Layer
{
public:
	cocos2d::Sprite *blood[MAX_NUM_BLOOD];
	cocos2d::Sprite *exe[MAX_NUM_EXE];

	cocos2d::TMXTiledMap *_tileMap;     //地图
	cocos2d::TMXLayer * _collision;    //碰撞层
	cocos2d::Vec2 my_player_pos;        //人物坐标
	cocos2d::Vec2 monster_pos;         //怪物坐标
	cocos2d::Vec2 expPro_pos;      //经验条坐标
	cocos2d::Vec2 offset_pos;     //地图坐标偏移量

	unsigned long long Time = 0;


	static cocos2d::Scene *createScene();
	virtual bool init();
	CREATE_FUNC(Gaming);

	virtual void update(float delta);
	MAP * map;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	void init_map();
	void init_player();
	void init_expPro();
	void mouse_listener();
	void keyboard_listener();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void keyPressedDuration(EventKeyboard::KeyCode code);

	void FakekeyPressedDuration_monster(int direction);//AI移动

	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	void player_move();
	void monster_random_move();



	bool touchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void touchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	float calculate_angle(cocos2d::Vec2 startpos, cocos2d::Vec2 endpos);
	cocos2d::Vec2 calculate_pos(cocos2d::Vec2 startpos, cocos2d::Vec2 endpos, float length);

	void menuCloseCallback(cocos2d::Ref* pSender);
	void setViewpointCenter(cocos2d::Vec2 position);
	cocos2d::Vec2 random_map();
	void add_something(int name);
	void find_something(int name);
	

	void init_monster();
	void monster_attack();

private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	Size size;
	Point pos;
	Sprite* sprite;
	Player* my_player = Player::create();
	Player* monster = Player::create();
	ExpProgress *expPro;
	std::vector<Player*>player_sum;
	std::vector<Weapon*>arrow_sum;
	void Level_up();


};

#endif //__GAMING_SCENE_H__