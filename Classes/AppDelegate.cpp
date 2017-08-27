#include "AppDelegate.h"
#include "HelloWorldScene.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    auto fileUtils = FileUtils::getInstance( );
    auto screenSize = glview->getFrameSize( );
    std::vector<std::string> resDirOrders;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // check which assets the devices requires
    if ( 2048 == screenSize.width || 2048 == screenSize.height ) // retina iPad
    {
        resDirOrders.push_back( "ipadhd" );
        resDirOrders.push_back( "ipad" );
        resDirOrders.push_back( "iphonehd5" );
        resDirOrders.push_back( "iphonehd" );
        resDirOrders.push_back( "iphone" );
        
        glview->setDesignResolutionSize( 1536, 2048, ResolutionPolicy::NO_BORDER );
    }
    else if ( 1024 == screenSize.width || 1024 == screenSize.height ) // non retina iPad
    {
        resDirOrders.push_back( "ipad" );
        resDirOrders.push_back( "iphonehd5" );
        resDirOrders.push_back( "iphonehd" );
        resDirOrders.push_back( "iphone" );
        
        glview->setDesignResolutionSize( 768, 1024, ResolutionPolicy::NO_BORDER );
    }
    else if ( 1136 == screenSize.width || 1136 == screenSize.height ) // retina iPhone (5 and 5S)
    {
        resDirOrders.push_back("iphonehd5");
        resDirOrders.push_back("iphonehd");
        resDirOrders.push_back("iphone");
        
        glview->setDesignResolutionSize( 640, 1136, ResolutionPolicy::NO_BORDER );
    }
    else if ( 960 == screenSize.width || 960 == screenSize.height ) // retina iPhone (4 and 4S)
    {
        resDirOrders.push_back( "iphonehd" );
        resDirOrders.push_back( "iphone" );
        
        glview->setDesignResolutionSize( 640, 960, ResolutionPolicy::NO_BORDER );
    }
    else // non retina iPhone and Android devices
    {
        if ( 1080 < screenSize.width && 1080 < screenSize.height ) // android devices that have a high resolution
        {
            resDirOrders.push_back( "iphonehd" );
            resDirOrders.push_back( "iphone" );
            
            glview->setDesignResolutionSize( 640, 960, ResolutionPolicy::NO_BORDER );
        }
        else // non retina iPhone and Android devices with lower resolutions
        {
            resDirOrders.push_back( "iphone" );
            
            glview->setDesignResolutionSize( 320, 480, ResolutionPolicy::NO_BORDER );
        }
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    resDirOrders.push_back( "ipad" );
    resDirOrders.push_back( "iphonehd5" );
    resDirOrders.push_back( "iphonehd" );
    resDirOrders.push_back( "iphone" );
    
    glview->setFrameSize( 768, 1024 );
    glview->setDesignResolutionSize( 768, 1024, ResolutionPolicy::NO_BORDER );
#endif
    
    fileUtils->setSearchPaths(resDirOrders);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
