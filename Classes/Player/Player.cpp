#include "Player/Player.h"
#include "Scene/GamingScene.h"
#include"Player/IEntity.h"
#include"Player/Weapon.h"
#include"Scene/Map.h"
#include "SimpleAudioEngine.h"
#include "Scene/DefeatScene.h"
#include "Scene/VictoryScene.h"

using namespace CocosDenshion;
//#define up  (EventKeyboard::KeyCode)38
//#define down (EventKeyboard::KeyCode)40
//#define left (EventKeyboard::KeyCode)37
//#define right (EventKeyboard::KeyCode)39

USING_NS_CC;
using namespace std;
bool Player::init()
{
	//创建血条
	setlifeValue(_lifevalue);
	loadingBar = LoadingBar::create("GameItem/Player/planeHP.png");
	loadingBar->setScale(0.1f);
	//	loadingBar->setPercent(60);
	loadingBar->setScale(0.1f);
	loadingBar->setDirection(LoadingBar::Direction::LEFT);
	Vec2 pos = Vec2(getPosition().x, getPosition().y);
	loadingBar->setPosition(Vec2(pos.x + 15, pos.y + 20));
	setHP(loadingBar);
	loadingBar->setPercent(100.0f*_lifevalue / Hp_limit);
	this->addChild(getHP(), 1);
	setHPInterval
	(getHP()->getPercent() / (float)getlifeValue());
	
	this->schedule(schedule_selector(Player::update), 0.02f);
	
	return true;


}


void Player::update(float delta)
{
	loadingBar->setPercent(100.0f*_lifevalue / Hp_limit);


}
/*****************************************受到攻击函数*************************************************/
bool Player::hurt(float attack)
{
	_lifevalue -= attack * defend;
	if (_lifevalue <= 0)
	{
		if (enemy->ID == 0)//我死亡
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, DefeatScene::createScene()));
		}
		else
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, VictoryScene::createScene()));
		}
		//GG(x_coord, y_coord);
		return true;
	}
	return false;
}
/*********************************************判定人物死亡函数*******************************************/
void Player::GG(int restart_x, int restart_y)
{


	restart_pos.x = restart_x;
	restart_pos.y = restart_y;

	this->setAnchorPoint(Point(0.5, 0));
	this->setPosition(x_coord, y_coord - 35);
	x_coord = restart_x;
	y_coord = restart_x;
	auto * rotateto = RotateTo::create(0.3, 90);
	CCActionInterval * delaytime = CCDelayTime::create(1.0f);

	auto callbackFunc = [&]()
	{
		restart(restart_pos.x, restart_pos.y);
	};
	CallFunc* callFunc = CallFunc::create(callbackFunc);

	Action* actions = Sequence::create(/*rotateto, */delaytime, callFunc, NULL);

	this->runAction(actions);
}
/*************************************************复活函数************************************************************/
void Player::restart(int restart_x, int restart_y)
{


	_lifevalue = 50;


	this->setAnchorPoint(Point(0.5, 0.5));
	x_coord = restart_x;
	y_coord = restart_y;

	this->setPosition(x_coord, y_coord);

	auto * rotateto = RotateTo::create(0, 0);
	Blink *blink = Blink::create(3, 6);

	//Action* actions = Sequence::create(rotateto, NULL);

	//this->runAction(actions);
}
/************************************************************创建精灵动画函数****************************************/
void Player::player_action(int Tag)
{
	switch (Tag) {
	case  1:
		front_Animation = Animation::create();
		for (int i = 0; i < 4; i++) {
			char nameSize[100] = { 0 };
			sprintf(nameSize, "GameItem/Player/Player%d/player%d_%d.png", ID, ID, i + 1);
			front_Animation->addSpriteFrameWithFile(nameSize);
		}
		front_Animation->setDelayPerUnit(0.02f);
		front_Animate = Animate::create(front_Animation);
		sprite->runAction(front_Animate);
		break;
	case  2:
		left_Animation = Animation::create();
		for (int i = 0; i < 4; i++) {
			char nameSize[100] = { 0 };
			sprintf(nameSize, "GameItem/Player/Player%d/player%d_%d.png", ID, ID, i + 5);
			left_Animation->addSpriteFrameWithFile(nameSize);
		}
		left_Animation->setDelayPerUnit(0.02f);
		left_Animate = Animate::create(left_Animation);
		sprite->runAction(left_Animate);
		break;
	case  3:
		right_Animation = Animation::create();
		for (int i = 0; i < 4; i++) {
			char nameSize[100] = { 0 };
			sprintf(nameSize, "GameItem/Player/Player%d/player%d_%d.png", ID, ID, i + 9);
			right_Animation->addSpriteFrameWithFile(nameSize);
		}
		right_Animation->setDelayPerUnit(0.02f);
		right_Animate = Animate::create(right_Animation);
		sprite->runAction(right_Animate);
		break;
	case  4:
		behind_Animation = Animation::create();
		for (int i = 0; i < 4; i++) {
			char nameSize[100] = { 0 };
			sprintf(nameSize, "GameItem/Player/Player%d/player%d_%d.png", ID, ID, i + 13);
			behind_Animation->addSpriteFrameWithFile(nameSize);
		}
		behind_Animation->setDelayPerUnit(0.02f);
		behind_Animate = Animate::create(behind_Animation);
		sprite->runAction(behind_Animate);
		break;
	default:break;
	}
}

/************************************************加血函数*******************************************************/
void Player::Hp_Up(int num)
{
	_lifevalue += HP_UP * num * 10;

	if (_lifevalue >= Hp_limit)
		_lifevalue = Hp_limit;
}
/***********************************************加经验函数********************************************************/
bool Player::Exp_Up(int num)
{
	exp += EXP_UP * num * 2;
	bool whether = 0;
	while (exp >= Exp_limit() && level <= 10)
	{
		exp -= Exp_limit();
		level++;
		whether = 1;
	}
	
	return whether;
}
int Player::Exp_limit()
{
	if (level == 1)
		return 100;
	
	return (5 * level*level + 15 * level);
}
/**********************************************攻击间隔函数*******************************************************/
void Player::attack_interval()
{
	attackcd = 1;

	MoveBy* moveBy = MoveBy::create(attack_CD, ccp(0, 0));
	auto callbackFunc = [&]()
	{
		attackcd = 0;
	};
	CallFunc* callFunc = CallFunc::create(callbackFunc);

	Action* actions = Sequence::create(moveBy, callFunc, NULL);
	this->runAction(actions);
}



void Player::attack(Player* player, Point point)
{
	Point pos;
	pos.x = player->x_coord;
	pos.y = player->y_coord;

	attackweapon(player, player->front, point, 1);
	attackweapon(player, player->left, point, 2);
	attackweapon(player, player->right, point, 3);
	attackweapon(player, player->back, point, 4);

}
void Player::attackweapon(Player* player, float weapon_num, Point point, int Tag)
{
	if (weapon_num == 0)
		return;

	Point atkpoint = point;                 //发射子弹的坐标
	float angle = 0;

	switch (Tag) {
	case 1:
		angle = calculate_angle(Vec2(player->x_coord, player->y_coord), point) - 90.0f;//正面旋转角度 
		atkpoint = calculate_pos(Vec2(player->x_coord, player->y_coord), point, 150.0, Tag);//正面攻击终点坐标
		break;
	case 2:
		angle = calculate_angle(Vec2(player->x_coord, player->y_coord), point) - 180.0f;//左面旋转角度 
		atkpoint = calculate_pos(Vec2(player->x_coord, player->y_coord), point, 150.0, Tag);//左面攻击终点坐标
		break;
	case 3:
		angle = calculate_angle(Vec2(player->x_coord, player->y_coord), point);//右面旋转角度 
		atkpoint = calculate_pos(Vec2(player->x_coord, player->y_coord), point, 150.0, Tag);//右面攻击终点坐标
		break;
	case 4:
		angle = calculate_angle(Vec2(player->x_coord, player->y_coord), point) + 90.0f;//后面旋转角度 
		atkpoint = calculate_pos(Vec2(player->x_coord, player->y_coord), point, 150.0, Tag);//后面攻击终点坐标
		break;
	default:break;
	}


	for (int i = 0; i < weapon_num; i++)
	{
		auto Abullet = Weapon::create();     //创建武器		
		//武器精灵创建 
		switch (player->weapon) {
		case 1:
			Abullet->bind_Sprite(Sprite::create("GameItem/Weapon/arrow.png"));
			break;
		case 2:
			Abullet->bind_Sprite(Sprite::create("GameItem/Weapon/fire.png"));
			break;
		case 3:
			Abullet->bind_Sprite(Sprite::create("GameItem/Weapon/knife1.png"));
			break;
		default:break;
		}
		Abullet->setPosition(Point(player->x_coord, player->y_coord));//武器产生坐标
		_tileMap->addChild(Abullet);
		auto * rotateto = RotateTo::create(0, angle);//武器旋转
		Abullet->runAction(rotateto);

		Abullet->exist = true;    //武器存在
		bubsum.push_back(Abullet);

		//Abullet->map = _map;
		Abullet->enemy = enemy;
		Abullet->_tileMap = _tileMap;
		Abullet->_collision = _collision;
		Abullet->attacking(player, atkpoint);
		Abullet->time = 0;
		Abullet->schedule(schedule_selector(Weapon::update), 0.02f);


	}
}

//计算两点的角度
float Player::calculate_angle(cocos2d::Vec2 startpos, cocos2d::Vec2 endpos)
{
	Vec2 dis = endpos - startpos;
	float angle = Vec2(dis.y, dis.x).getAngle() / 3.14f * 180;
	return angle;
}
//计算武器终点坐标
cocos2d::Vec2 Player::calculate_pos(cocos2d::Vec2 startpos, cocos2d::Vec2 endpos, float length, int Tag)
{
	cocos2d::Vec2 pos;
	float distance = (float)sqrt(pow(endpos.x - startpos.x, 2) + pow(endpos.y - startpos.y, 2));
	pos.x = (length*endpos.x - length * startpos.x + distance * startpos.x) / distance;
	pos.y = (length*endpos.y - length * startpos.y + distance * startpos.y) / distance;
	float mx = pos.x;
	float my = pos.y;
	switch (Tag) {
	case 1:break;
	case 2:
		pos.x = startpos.x + startpos.y - my;
		pos.y = startpos.y - startpos.x + mx;
		break;
	case 3:
		pos.x = startpos.x - startpos.y + my;
		pos.y = startpos.y + startpos.x - mx;
		break;
	case 4:
		pos.x = startpos.x * 2 - mx;
		pos.y = startpos.y * 2 - my;
		break;
	default:break;
	}


	return pos;
}

