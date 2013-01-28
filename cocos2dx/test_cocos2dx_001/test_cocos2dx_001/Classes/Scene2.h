//
//  Scene2.h
//  test_cocos2dx_001
//
//  Created by chenshengtai on 12-12-29.
//
//

#ifndef __test_cocos2dx_001__Scene2__
#define __test_cocos2dx_001__Scene2__

#include "cocos2d.h"
#include "cocos-ext.h"

class Scene2 : public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
public:
    virtual bool init();
    
    static cocos2d::CCScene * scene();
    
    
    void stopActions();
    void close();
    void testVoidPoint(int a);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    
    
    void onClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);

    void onMenuItemClicked(cocos2d::CCObject * pSender);
    
    CREATE_FUNC(Scene2);
    
private:
    cocos2d::CCSprite * sprite1;
    cocos2d::extension::CCControlButton * btn_test;
};

#endif /* defined(__test_cocos2dx_001__Scene2__) */
