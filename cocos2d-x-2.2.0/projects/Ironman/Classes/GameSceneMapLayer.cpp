//
//  GameSceneMapLayer.cpp
//  Ironman
//
//  Created by cocos2d on 13-10-16.
//
//

#include "GameSceneMapLayer.h"

//
const static char* map0[3] = {"bg0_0.tmx", "bg0_1.tmx", "bg0_2.tmx"};
const static char* map1[3] = {"bg1_0.tmx", "bg1_1.tmx", "bg1_2.tmx"};
const static char* map2[3] = {"bg2_0.tmx", "bg2_1.tmx", "bg2_2.tmx"};
const static float g_w = 480.0;
static int g_map_move_speed = 3;   //map move speed.

//load one tiledmap.
bool TiledMap::initMap(int index, int mapIdx)
{
    //CCLog("tiled map init.");
    //CCTMXTiledMap* tile = CCTMXTiledMap::create("bg0_0.tmx");
    CCTMXTiledMap* tile;
    switch (mapIdx) {
        case 1:
            tile = CCTMXTiledMap::create(map1[index]);
            break;
        case 2:
            tile = CCTMXTiledMap::create(map2[index]);
            break;
        default:
            tile = CCTMXTiledMap::create(map0[index]);
            break;
    }
    this->addChild(tile);
    //_objects = CCArray::create();
    _objects = tile->getObjectGroups();
    //CCLog("TiledMap _objects: %d, %x", _objects->count(), _objects->lastObject());
    
    return true;
}

CCArray* TiledMap::getObjects()
{
    return _objects;
}

//load one group tiledmap.
bool MapGet::initMap(int mapIdx)
{
    //CCLog("MapGet init.");
    _objects = CCArray::create();
    for (int i=2; i>=0; i--) {
        TiledMap* map = TiledMap::create();
        map->initMap(i, mapIdx);
        map->setPositionX(g_w * i);
        this->addChild(map);
        
        _objects->addObjectsFromArray(map->getObjects());
    }
    //CCLog("MapGet _objects: %d", _objects->count());
    
    _length = 3 * g_w;
    
    _bInMap = true;
    
    return true;
}

float MapGet::getW()
{
    return _length;
}

void MapGet::update()
{
    if (!_bInMap) {
        return;
    }
    float p_x = this->getPositionX();
    if (p_x <= -this->_length) {
        ((GameSceneMapLayer*)this->getParent())->refreshMap();
    }
    if (p_x == -g_w) {
        ((GameSceneMapLayer*)this->getParent())->addNextMap();
    }
    p_x -= g_map_move_speed;
    if (p_x >= -this->_length) {
        this->setPositionX(p_x);
    }
}


bool MapGet::isInMap(){
    return _bInMap;
}
void MapGet::setInMap(bool b){
    _bInMap = b;
}

CCArray* MapGet::getObjects()
{
    return _objects;
}

//move map for game.
bool GameSceneMapLayer::init()
{
    CCLayerColor* colorLy = CCLayerColor::create(ccc4(43,49,62,0));
    this->addChild(colorLy);
    
    MapGet* map0 = MapGet::create();
    map0->initMap(1);
    this->addChild(map0);
    _curW = map0->getW();
    
    _maps[0] = map0;
    _maps[1] = NULL;
    
    _lastIdx = 1;
    
    this->scheduleUpdate();
    bMove = false;
    
    return true;
}

void GameSceneMapLayer::update(float dt)
{
    if(bMove)
    {
        for (int i=0; i<2; i++) {
            if (_maps[i] != NULL && _maps[i]->isInMap()) {
                //CCLog("_map %d, %x.", i, _maps[i]);
                _maps[i]->update();
            }
        }
        
        _distance += g_map_move_speed;
    }
}

void GameSceneMapLayer::getObjects()
{
    return;
}

void GameSceneMapLayer::addNextMap()
{
    //CCLog("addNextMap.");
    int idx = getRandN(2);
    if( idx == _lastIdx )
    {
        idx = 2;
    }
    MapGet* map_n = MapGet::create();
    map_n->initMap(idx);
    
    map_n->setPositionX(_curW + _maps[0]->getPositionX());
    addChild(map_n);
    _curW = map_n->getW();
    _maps[1] = map_n;
    _lastIdx = idx;
    //CCLog("addNextMap end, %x, %x.", _maps[0], _maps[1]);
}

void GameSceneMapLayer::refreshMap()
{
    //CCLog("refreshMap, %x, %x.", _maps[0], _maps[1]);
    _maps[0]->removeFromParentAndCleanup(true);
    _maps[0] = _maps[1];
    _maps[1] = NULL;
    //CCLog("refreshMap end, %x, %x.", _maps[0], _maps[1]);
}

int GameSceneMapLayer::getRandN(int n)
{
    return CCRANDOM_0_1()*n;
}

void GameSceneMapLayer::stop()
{
    bMove = false;
}
void GameSceneMapLayer::move()
{
    bMove = true;
}
float GameSceneMapLayer::getDistance()
{
    return _distance;
}
void GameSceneMapLayer::setMovedSpeed(float speed)
{
    g_map_move_speed = speed;
}
