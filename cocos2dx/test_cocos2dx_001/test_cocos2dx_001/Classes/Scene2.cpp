//
//  Scene2.cpp
//  test_cocos2dx_001
//
//  Created by chenshengtai on 12-12-29.
//
//


#include "Scene2.h"

#include "CCArray.h"


using namespace cocos2d;

using namespace cocos2d::extension;

CCScene * Scene2::scene()
{
    CCScene * scene = CCScene::create();
    CCLayer * layer = Scene2::create();
    scene -> addChild( layer );
    return scene;
}                                                                                                                                                                                                                                                                                                                        

bool Scene2::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CCLabelTTF * label = CCLabelTTF::create();
    label -> setFontSize(50);
    label -> setString("chenshengtai");
    label -> setColor(ccc3(255, 255, 255));
    label -> setPosition(ccp(300,300));
    this -> addChild( label );
    
    //添加Menu
    CCMenuItemImage * mItem = CCMenuItemImage::create("CloseNormal.png",
                                                      "CloseSelected.png",
                                                      this,
                                                      menu_selector(Scene2::close)
                                                      );
    mItem -> setPosition(ccp(0,0));
    CCMenuItemImage * mItem2 = CCMenuItemImage::create("Icon.png", "Icon.png", this, menu_selector(Scene2::stopActions));
    mItem2 -> setPosition(ccp(100,0));
    CCMenu * menu = CCMenu::create(mItem,mItem2,NULL);
    menu -> setPosition(ccp(200,200));
    this -> addChild( menu );
    
    sprite1 = CCSprite::create("Icon-Small.png");
    sprite1 -> setPosition(ccp(150,150));
    this -> addChild(sprite1);
    
    
    
    
    CCMoveTo * moveTo = CCMoveTo::create(1, ccp(20,20));
    //CCMoveTo 的坐标是最终位置，CCMoveBy是向量，填多少移动多少
    
    CCRotateBy * rotateBy = CCRotateBy::create(1, 180);
    
    CCSkewTo * skewTo = CCSkewTo::create(1, 30,30);
    
    CCActionEase * ease = CCActionEase::create(moveTo);
    
    CCEaseBackIn * easeBackIn = CCEaseBackIn::create(moveTo);
    
    CCEaseRateAction * easeRate = CCEaseRateAction::create(moveTo, 1);
    
    CCEaseBounceIn * easeBoundce = CCEaseBounceIn::create(moveTo);
    
    CCDelayTime * delayTime = CCDelayTime::create(1);
    
    CCJumpBy * jumpBy = CCJumpBy::create(1, ccp(100,100), 50, 3);
    
    CCScaleTo * scaleTo = CCScaleTo::create(1.0, 2);
    
    CCWaves * waves = CCWaves::create(3, 12, false, true, ccg(9,6), 3);//create(波浪数，振幅，x轴是否扭曲，y轴是否扭曲，分格的大小，时间);
    
    CCShaky3D * shaky3D = CCShaky3D::create(3, true, ccg(9,6), 3);
    
    
    //sprite1 -> runAction(skewTo);
    //sprite1 -> runAction(moveTo);
    //sprite1 -> runAction(rotateBy);
    //sprite1 ->runAction(ease);
    //sprite1 -> runAction(easeBackIn);
    //sprite1 -> runAction(easeRate);
    //sprite1 -> runAction(easeBoundce);
    
    CCFiniteTimeAction *  sequence = CCSequence::create(shaky3D,rotateBy,delayTime,moveTo,jumpBy,scaleTo,waves,NULL);
    CCRepeatForever * repeatForever = CCRepeatForever::create((CCActionInterval *)sequence);
    
    repeatForever -> setTag(999);
    
    sprite1 -> runAction(repeatForever);

    
    
    //成员函数指针
    void (Scene2:: * method)();
    method = &Scene2::stopActions;
    
    void (Scene2:: * method2)(int a);
    method2 = &Scene2::testVoidPoint;
    
    
    
    
    
    //使用cocosbuilder
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    //ccNodeLoaderLibrary->registerCCNodeLoader("HelloCocosBuilderLayer", CCLayerLoader::loader());
    
    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary,this,this,this);
    
    /* Read a ccbi file. */
    CCNode * node = ccbReader->readNodeGraphFromFile("ccb/HelloCocosBuilder.ccbi",this);
    
    this -> addChild(node);

    ccbReader -> release();
    
    return true;
}

void Scene2::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader)
{
    CCLog("CCB init: onNodeLoaded : %s",  pNode -> description());
    CCLog("is ControlButton  btn_test : %d",pNode -> isEqual(btn_test));
    /*
    pNode -> isScheduled(cccontrol_selector(Scene2::stopAllActions));
    pNode -> isScheduled(menu_selector(Scene2::stopAllActions));
    */
}


SEL_MenuHandler Scene2::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCLog("CCB init: onResolveCCBCCMenuItemSelector");
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", Scene2::onMenuItemClicked);
    
    return NULL;
}

SEL_CCControlHandler Scene2::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCLog("CCB init: onResolveCCBCCControlSelector");
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClicked", Scene2::onClicked);
    
    return NULL;
}

bool Scene2::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCLog("CCB init: onAssignCCBMemberVariable");
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btn_test", CCControlButton *, this->btn_test);
    
    return false;
}

void Scene2::onClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
    CCLog("ControlButton Clicked.");
}

void Scene2::onMenuItemClicked(cocos2d::CCObject * pSender)
{
    CCLog("Menu Item Clicked.");
}

void Scene2:: testVoidPoint(int a)
{
    
}

void Scene2:: stopActions()
{
    sprite1 -> stopActionByTag(999);
    //sprite1 -> stopAllActions();
}

void Scene2:: close()
{
    CCDirector::sharedDirector() -> popScene();
}

