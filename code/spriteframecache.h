/****************************************************************************
Copyright [2014]      Fan Yefei
Copyright [2010-2011] cocos2d-x.org
Copyright [2008-2011] Ricardo Quesada
Copyright [2011]      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __SPRITEFRAMECACHE_H__
#define __SPRITEFRAMECACHE_H__



/*
 * To create sprite frames and texture atlas, use this tool:
 * http://zwoptex.zwopple.com/
 */


#include <string>
#include <unordered_map>


#include "kzlib/singleton.h"


namespace cocos2d {



/**
 * @addtogroup sprite_nodes
 * @{
 */

/** @brief Singleton that handles the loading of the sprite frames.
 It saves in a cache the sprite frames.
 @since v0.9
 */
// 概念：
// set          集合 ，一般对应一个 plist 的数据文件或者数据库中的一组数据
// alias        别名，对应了某个 SpriteFrame
// texture      贴图，一个set一般存在一个贴图
// textureName  贴图名称，和贴图一一对应（绑定）
// SpriteFrame  图片，指贴图中的一块区域
// 关系：
// set : SpriteFrame   是一对多的关系
// SpriteFrame : alias 是一对多的关系
// set : texture       是一对一的关系



class CC_DLL CSpriteFrameCache : public kzlib::TSingleton<CSpriteFrameCache>
{

public:
    virtual ~CSpriteFrameCache(void){}
protected:
    /* Adds multiple Sprite Frames with a dictionary. 
       The texture will be associated with the created sprite frames.
     */
    void addSpriteFramesWithDictionary(class CCDictionary* pDictionary,class CCTexture2D *pTexture,const char *szSet);
public:

    void AddSpriteFramesFromFile(const char *szSet);
    void AddSpriteFramesFromFile(const char *szSet, const char* textureFileName);
    void AddSpriteFramesFromFile(const char *szSet,class CCTexture2D *pobTexture);


    void AddSpriteFrame(class CCSpriteFrame *pobFrame, const char *pszFrameName);
	void AddSpriteFrame(const char *pszAliasName, const char *pszFrameName);
    void AddSpriteFrame(class CCTexture2D *pTexture, const char *pszFrameName);
   
    void RemoveAllSpriteFrames(void);
    void RemoveUnusedSpriteFrames(void);
    void RemoveSpriteFrame(const char *pszName);
    void RemoveSpriteFrameFromSet(const char* szSet);
    void RemoveSpriteFrameFromTexture(class CCTexture2D* texture);

    /** Returns an Sprite Frame that was previously added.
     If the name is not found it will return nil.
     You should retain the returned copy if you are going to use it.
     */
    class CCSpriteFrame* GetSpriteFrame(const char *pszName);
protected:
    // 图片名字 => 数据
    std::unordered_map<std::string,std::shared_ptr<class CCSpriteFrame> > m_spriteFrames;
	// 集合名称 => 图片数量
	std::unordered_map<std::string,int>   m_loadedFileNames;
};

// end of sprite_nodes group
/// @}

}
#endif  // __SPRITEFRAMECACHE_H__


