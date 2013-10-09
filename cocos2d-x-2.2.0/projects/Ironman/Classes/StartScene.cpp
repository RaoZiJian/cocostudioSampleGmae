#include "StartScene.h"

USING_NS_CC;

CCScene* StartScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StartScene *layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    StartScene::registerWithTouchDispatcher();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("ImCrouch.ExportJson", this, schedule_selector(StartScene::ImCrouch));
    

	
    return true;
}
void StartScene::ImCrouch(float t)
{
	armature = CCArmature::create("ImCrouch");
	armature->getAnimation()->play("crouch");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(0.6f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
}

void StartScene::IMRun(float t)
{
	armature = CCArmature::create("IMRun");
	armature->getAnimation()->play("Runing");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(0.6f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
}

void StartScene::menuCloseCallback(CCObject* pSender)
{
		armature->setPosition(amaturePosition);
	

		CCActionInterval * splitCols = CCMoveTo::create(1.0,CCPointMake(armature->getPosition().x+300,armature->getPosition().y));

		armature->runAction(splitCols);

	
	/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
	*/
}


void StartScene::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void StartScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
     CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
        //��λ�ñ��浽����m_tBeginPos�С�
    m_tBeginPos = touch->getLocation();    
	
}

void StartScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	/*
          //��ȡ��һ������λ��
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
        //ȡ�����λ������һ֡�ƶ���Yֵ֮������ݷ����ƫ�ơ�
    CCPoint touchLocation = touch->getLocation();    
    float nMoveY = touchLocation.y - m_tBeginPos.y;
        //����˵����ݷ�����Ҳ�ƶ���Ӧֵ�����λ�á�
    CCPoint curPos  = armature->getPosition();
    CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);
        //�������λ�õ���Ч��Χ�����޶�
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if (nextPos.y < 0.0f)
    {
        armature->setPosition(CCPointZero);
        return;
    }
	
    if (nextPos.y > ((TESTS_COUNT + 1)* LINE_SPACE - winSize.height))
    {
        armature->setPosition(ccp(0, ((TESTS_COUNT + 1)* LINE_SPACE - winSize.height)));
        return;
    }
	
        //���²˵�����λ��
    armature->setPosition(nextPos);

        //��¼��ǰλ��Ϊ��λ�á�
    m_tBeginPos = touchLocation;
    s_tCurPos   = nextPos;
	*/
}

void StartScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
        //��ȡ��һ������λ��
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
        //ȡ�����λ������һ֡�ƶ���Yֵ֮������ݷ����ƫ�ơ�
    CCPoint touchLocation = touch->getLocation();    
    float nMoveX = touchLocation.x - m_tBeginPos.x;
	float nMoveY = touchLocation.y - m_tBeginPos.y;
	CCLog("m_tBeginPos.x = %f",m_tBeginPos.x);
	CCLog("touchLocation.x = %f",touchLocation.x);
	CCLog("nMoveX = %f ,nMoveY = %f",nMoveX,nMoveY);
	if(nMoveX>0 && tan(nMoveY/nMoveX)<fabs(sqrt(3)/3))
	{
		armature->stopAllActions();
		armature->removeFromParentAndCleanup(false);
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("IMRun.ExportJson", this, schedule_selector(StartScene::IMRun));
	}

}

void StartScene::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
}