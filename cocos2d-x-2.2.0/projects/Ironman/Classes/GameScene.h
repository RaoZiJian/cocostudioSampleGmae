//
//  GameScene.h
//  Ironman
//
//  Created by Ken on 13-10-10.
//
//

#ifndef Ironman_GameScene_h
#define Ironman_GameScene_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameSceneMapLayer.h"
#include "GameScenePlayLayer.h"
#include "GameSceneMonster.h"
#include "GameSceneMenuLayer.h"
#include "GameSceneOverLayer.h"

USING_NS_CC;

using namespace extension;
class GameSceneMapLayer;
class GameScenePlayLayer;
class GameSceneMonster;
class GameSceneMenuLayer;
class GameSceneOverLayer;

class GameScene : public cocos2d::CCScene
{
public:
    
    bool init();
	static GameScene * shareGameScene();
	void destroy();
	void gameOver();

	GameSceneMapLayer * gameSceneMapLayer;
    GameScenePlayLayer* playLayer;
	GameSceneMonster * gameSceneMonster;
	GameSceneMenuLayer* menuLayer;
};

#endif
