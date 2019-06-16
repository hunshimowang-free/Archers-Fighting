#include "Player/Exp_Progress.h"

#define choice_num 16

using namespace cocos2d::ui;

ExpProgress::ExpProgress()
{
}

ExpProgress::~ExpProgress()
{
}

bool ExpProgress::init()
{
	expProgressView = new Progress;
	expProgressView->setPosition(ccp(960,1000));
	expProgressView->setScale(2, 1.0);
	expProgressView->Background("GameItem/Player/expbk.png");
	expProgressView->Fill("GameItem/Player/exp.png");
	expProgressView->Total_progress(1);
	expProgressView->Current_progress(0);
	this->addChild(expProgressView);



	lv = Label::create("LV 1", "Arial", 40);



	lv->setPosition(ccp(960, 1000));
	addChild(lv);

	for (int i = 0; i < choice_num + 1; i++)
		unchoose.push_back(false);

	return true;
}

void ExpProgress::ExpChange(int exp, int limit)
{
	expProgressView->Current_progress((float)exp / limit);
}

void ExpProgress::LvChange(int level)
{
	removeChild(lv);
	if (level == 11)
	{


		lv = Label::create("LV MAX", "Arial", 40);

	}
	else
	{

		lv = Label::create(StringUtils::format("LV%d", level), "Arial", 40);

	}


	lv->setPosition(ccp(960, 1000));
	addChild(lv);

	skillsave++;
	if (skillsave <= 1)
		ButtonAppear();
}

void ExpProgress::ButtonAppear()
{
	srand(time(NULL));

	choice_bk1 = Sprite::create("choice_bk.png");
	choice_bk2 = Sprite::create("choice_bk.png");
	choice_bk3 = Sprite::create("choice_bk.png");

	c1 = rand() % choice_num + 1;
	while (unchoose[c1] == true)
		c1 = rand() % choice_num + 1;
	choice1 = Button::create(StringUtils::format("GameItem/Player/choice%d.png", c1));
	choice1->setPosition(ccp(800, 580));
	choice1->setScale(0.45);
	choice_bk1->setPosition(ccp(800, 567));
	choice_bk1->setScale(0.5);
	choice1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		Choices(c1);
		ButtonRemove();
	});
	addChild(choice_bk1,1000);
	addChild(choice1,1000);

	c2 = rand() % choice_num + 1;
	while (c2 == c1 || unchoose[c2] == true)
		c2 = rand() % choice_num + 1;
	choice2 = Button::create(StringUtils::format("GameItem/Player/choice%d.png", c2));
	choice2->setPosition(ccp(950, 580));
	choice2->setScale(0.45);
	choice_bk2->setPosition(ccp(950, 567));
	choice_bk2->setScale(0.5);
	choice2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		Choices(c2);
		ButtonRemove();
	});
	addChild(choice_bk2,1000);
	addChild(choice2,1000);

	c3 = rand() % choice_num + 1;
	while (c3 == c1 || c3 == c2 || unchoose[c3] == true)
		c3 = rand() % choice_num + 1;
	choice3 = Button::create(StringUtils::format("GameItem/Player/choice%d.png", c3));
	choice3->setPosition(ccp(1100, 580));
	choice3->setScale(0.45);
	choice_bk3->setPosition(ccp(1100.6, 567));
	choice_bk3->setScale(0.5);
	choice3->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		Choices(c3);
		ButtonRemove();
	});
	addChild(choice_bk3,1000);
	addChild(choice3,1000);
}

void ExpProgress::ButtonRemove()
{
	removeChild(choice1);
	removeChild(choice2);
	removeChild(choice3);
	removeChild(choice_bk1);
	removeChild(choice_bk2);
	removeChild(choice_bk3);

	skillsave--;

	if (skillsave > 0)
		ButtonAppear();
}

void ExpProgress::Choices(int i)
{


	ifchose = 1;
	switch (i)
	{
	case 1://fire
		player->weapon = 2;
		break;
	case 2://��
		player->weapon = 3;
		break;
	case 3://�ӹ�����
		player->power += 0.3;
		break;
	case 4://�����
		player->attack_len += 0.2;                          //��������
		break;
	case 5://�ӷ���
		player->defend -= 0.2;
		break;
	case 6://��ǰ��
		player->front++;
		break;
	case 7://�Ӻ�
		player->back++;
		break;
	case 8://������
		player->left++;
		player->right++;
		break;
	case 9://�������Ӹ���hp
		player->HP_UP += 0.5;
		break;
	case 10://���Ӹ��ྭ��
		player->EXP_UP += 0.5;
		break;
	case 11://���ٶ�
		player->speed += 1;
		break;
	case 12://Ѫ����
		player->Hp_limit += 10;
		break;
	case 13://��Ѫ���޼ӹ�����
		player->Hp_limit -= 10;
		player->power += 0.7;
		break;
	case 14://������CD
		player->attack_CD -= 0.15;
		break;
	case 15://�ѻ�����
		player->attack_len += 0.5;
		player->speed -= 1;
		break;
	case 16://ȫ��������
		player->power += 0.1;
		player->attack_len += 0.1;
		player->defend -= 0.1;
		break;

	}

	char hero_mess[40];
	sprintf(hero_mess, "%d %d %d %d %d %d %d %d %d %d ",
		static_cast<int>(player->speed * 10), static_cast<int>(player->_lifevalue * 10), player->Hp_limit,
		static_cast<int>(player->power * 10), static_cast<int>(player->attack_len * 10),
		static_cast<int>(player->defend * 10),
		player->front, player->left, player->right, player->back);

	//hero_nature = hero_mess;

	for (int i = 1; i <= 2; i++)
		unchoose[i] = false;
	unchoose[player->weapon - 1] = true;

	if (player->left == 1)
		unchoose[8] = true;

	if (player->speed <= 2)
		unchoose[15] = true;
	else unchoose[15] = false;

	if (player->attack_CD <= 0.4)
		unchoose[14] = true;


}
