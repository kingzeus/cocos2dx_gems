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
#include "ccMacros.h"

#include "spriteframecache.h"

#include "cocoa/CCNS.h"

#include "textures/CCTextureCache.h"

#include "spriteframe.h"
#include "CCSprite.h"
#include "support/TransformUtils.h"
#include "platform/CCFileUtils.h"
#include "CCString.h"
#include "CCDictionary.h"


using namespace cocos2d;


void CSpriteFrameCache::addSpriteFramesWithDictionary(CCDictionary* dictionary, CCTexture2D *pobTexture,const char *szSet)
{
    /*
    Supported Zwoptex Formats:

    ZWTCoordinatesFormatOptionXMLLegacy = 0, // Flash Version
    ZWTCoordinatesFormatOptionXML1_0 = 1, // Desktop Version 0.0 - 0.4b
    ZWTCoordinatesFormatOptionXML1_1 = 2, // Desktop Version 1.0.0 - 1.0.1
    ZWTCoordinatesFormatOptionXML1_2 = 3, // Desktop Version 1.0.2+
    */

    CCDictionary *metadataDict = (CCDictionary*)dictionary->objectForKey("metadata");
    CCDictionary *framesDict = (CCDictionary*)dictionary->objectForKey("frames");
    int format = 0;

    // get the format
    if(metadataDict != NULL) 
    {
        format = metadataDict->valueForKey("format")->intValue();
    }

    // check the format
    CCAssert(format >=0 && format <= 3, "format is not supported for CCSpriteFrameCache addSpriteFramesWithDictionary:textureFilename:");

    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(framesDict, pElement)
    {
        CCDictionary* frameDict = (CCDictionary*)pElement->getObject();
        std::string spriteFrameName = pElement->getStrKey();

        
        if (m_spriteFrames.find(spriteFrameName)!=m_spriteFrames.end())
        {
            continue;
        }
        CCSpriteFrame* pSpriteFrame = NULL;
        if(format == 0) 
        {
            float x = frameDict->valueForKey("x")->floatValue();
            float y = frameDict->valueForKey("y")->floatValue();
            float w = frameDict->valueForKey("width")->floatValue();
            float h = frameDict->valueForKey("height")->floatValue();
            float ox = frameDict->valueForKey("offsetX")->floatValue();
            float oy = frameDict->valueForKey("offsetY")->floatValue();
            int ow = frameDict->valueForKey("originalWidth")->intValue();
            int oh = frameDict->valueForKey("originalHeight")->intValue();
            // check ow/oh
            if(!ow || !oh)
            {
                CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the CCSpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
            }
            // abs ow/oh
            ow = abs(ow);
            oh = abs(oh);
            // create frame
            pSpriteFrame = new CCSpriteFrame();
			pSpriteFrame->m_strSetName = szSet;
            pSpriteFrame->initWithTexture(pobTexture, 
                                        CCRectMake(x, y, w, h), 
                                        false,
                                        CCPointMake(ox, oy),
                                        CCSizeMake((float)ow, (float)oh)
                                        );
			// add sprite frame
			AddSpriteFrame(pSpriteFrame,spriteFrameName.c_str());
        } 
        else if(format == 1 || format == 2) 
        {
            CCRect frame = CCRectFromString(frameDict->valueForKey("frame")->getCString());
            bool rotated = false;

            // rotation
            if (format == 2)
            {
                rotated = frameDict->valueForKey("rotated")->boolValue();
            }

            CCPoint offset = CCPointFromString(frameDict->valueForKey("offset")->getCString());
            CCSize sourceSize = CCSizeFromString(frameDict->valueForKey("sourceSize")->getCString());

            // create frame
            pSpriteFrame = new CCSpriteFrame();
			pSpriteFrame->m_strSetName = szSet;
            pSpriteFrame->initWithTexture(pobTexture, 
                frame,
                rotated,
                offset,
                sourceSize
                );
			// add sprite frame
			AddSpriteFrame(pSpriteFrame,spriteFrameName.c_str());
        } 
        else if (format == 3)
        {
            // get values
            CCSize spriteSize = CCSizeFromString(frameDict->valueForKey("spriteSize")->getCString());
            CCPoint spriteOffset = CCPointFromString(frameDict->valueForKey("spriteOffset")->getCString());
            CCSize spriteSourceSize = CCSizeFromString(frameDict->valueForKey("spriteSourceSize")->getCString());
            CCRect textureRect = CCRectFromString(frameDict->valueForKey("textureRect")->getCString());
            bool textureRotated = frameDict->valueForKey("textureRotated")->boolValue();

			// create frame
			pSpriteFrame = new CCSpriteFrame();
			pSpriteFrame->m_strSetName = szSet;
			pSpriteFrame->initWithTexture(pobTexture,
				CCRectMake(textureRect.origin.x, textureRect.origin.y, spriteSize.width, spriteSize.height),
				textureRotated,
				spriteOffset,
				spriteSourceSize);
			// add sprite frame
			AddSpriteFrame(pSpriteFrame,spriteFrameName.c_str());
            // get aliases
            CCArray* aliases = (CCArray*) (frameDict->objectForKey("aliases"));
            CCString * frameKey = new CCString(spriteFrameName);


            CCObject* pObj = NULL;
            CCARRAY_FOREACH(aliases, pObj)
            {
                std::string oneAlias = ((CCString*)pObj)->getCString();
                AddSpriteFrame(oneAlias.c_str(),spriteFrameName.c_str());
            }
            frameKey->release();

        }

    }
}

void CSpriteFrameCache::AddSpriteFramesFromFile(const char *pszPlist, CCTexture2D *pobTexture)
{
    if (m_loadedFileNames.find(pszPlist) == m_loadedFileNames.end())
	{
		std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszPlist);
		CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());

		m_loadedFileNames.insert(std::make_pair(pszPlist,0));
		addSpriteFramesWithDictionary(dict, pobTexture,pszPlist);
		
		dict->release();
	}else{
	}
}

void CSpriteFrameCache::AddSpriteFramesFromFile(const char* plist, const char* textureFileName)
{
    CCAssert(textureFileName, "texture name should not be null");
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(textureFileName);

    if (texture)
    {
        AddSpriteFramesFromFile(plist, texture);
    }
    else
    {
        CCLOG("cocos2d: CCSpriteFrameCache: couldn't load texture file. File not found %s", textureFileName);
    }
}

void CSpriteFrameCache::AddSpriteFramesFromFile(const char *pszPlist)
{
    CCAssert(pszPlist, "plist filename should not be NULL");

    if (m_loadedFileNames.find(pszPlist) == m_loadedFileNames.end())
    {
        std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszPlist);
        CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());

        string texturePath("");

        CCDictionary* metadataDict = (CCDictionary*)dict->objectForKey("metadata");
        if (metadataDict)
        {
            // try to read  texture file name from meta data
            texturePath = metadataDict->valueForKey("textureFileName")->getCString();
        }

        if (! texturePath.empty())
        {
            // build texture path relative to plist file
            texturePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(texturePath.c_str(), pszPlist);
        }
        else
        {
            // build texture path by replacing file extension
            texturePath = pszPlist;

            // remove .xxx
            size_t startPos = texturePath.find_last_of("."); 
            texturePath = texturePath.erase(startPos);

            // append .png
            texturePath = texturePath.append(".png");

            CCLOG("cocos2d: CCSpriteFrameCache: Trying to use file %s as texture", texturePath.c_str());
        }

        CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(texturePath.c_str());

        if (pTexture)
        {
            m_loadedFileNames.insert(std::make_pair(pszPlist,0));
            addSpriteFramesWithDictionary(dict, pTexture,pszPlist);
        }
        else
        {
            CCLOG("cocos2d: CCSpriteFrameCache: Couldn't load texture");
        }

        dict->release();
    }

}

void CSpriteFrameCache::AddSpriteFrame(CCSpriteFrame *pSpriteFrame, const char *szFrameName)
{
    if(!pSpriteFrame)
		return;
    m_spriteFrames.insert(std::make_pair(szFrameName,std::shared_ptr<CCSpriteFrame>(pSpriteFrame)));
	auto itFiles = m_loadedFileNames.find(pSpriteFrame->m_strSetName);
	if(itFiles!= m_loadedFileNames.end())
	{
		itFiles->second ++ ;
	}
}

void cocos2d::CSpriteFrameCache::AddSpriteFrame( const char *pszAliasName, const char *pszFrameName )
{
    // 
	if(m_spriteFrames.find(pszAliasName)!=m_spriteFrames.end())
		return;
	auto it = m_spriteFrames.find(pszFrameName);
	if(it==m_spriteFrames.end())
		return;
	m_spriteFrames[pszAliasName]=it->second;

	auto itFiles = m_loadedFileNames.find(it->second->m_strSetName);
	if(itFiles!= m_loadedFileNames.end())
	{
	    itFiles->second ++ ;
	}
}

void CSpriteFrameCache::AddSpriteFrame( CCTexture2D *pTexture, const char *szFrameName )
{
	CCAssert(pTexture,"CCSpriteFrameCache::AddTexture texture is null");
	if (m_spriteFrames.find(szFrameName)!=m_spriteFrames.end())
        return;
	
	CCSpriteFrame* spriteFrame = new CCSpriteFrame();

	CCSize size = pTexture->getContentSize();
	spriteFrame->initWithTexture(pTexture, 
		CCRectMake(0, 0, size.width, size.height), 
		false,
		CCPointMake(0, 0),
		size
		);
	AddSpriteFrame(spriteFrame,szFrameName);
}

void CSpriteFrameCache::RemoveAllSpriteFrames(void)
{
    m_spriteFrames.clear();
	m_loadedFileNames.clear();
}

void CSpriteFrameCache::RemoveUnusedSpriteFrames(void)
{
    for(auto it = m_spriteFrames.begin();it!=m_spriteFrames.end();)
	{
	    if (it->second->retainCount()==1)
		{
		    auto itFiles = m_loadedFileNames.find(it->second->m_strSetName);
			if(itFiles!= m_loadedFileNames.end())
			{
			    itFiles->second -- ;
				if(itFiles->second ==0)
					m_loadedFileNames.erase(itFiles);
			}
		    it = m_spriteFrames.erase(it);
		}else
			it++;
	}
}


void CSpriteFrameCache::RemoveSpriteFrame(const char *pszName)
{
    // explicit nil handling
    if( !pszName )
        return;
	auto it = m_spriteFrames.find(pszName);
	if(it!=m_spriteFrames.end())
	{
	    auto itFiles = m_loadedFileNames.find(it->second->m_strSetName);
	    if(itFiles!= m_loadedFileNames.end())
		{
		    itFiles->second -- ;
			if(itFiles->second ==0)
				m_loadedFileNames.erase(itFiles);
		}
	    m_spriteFrames.erase(it);
	}
		
}



void CSpriteFrameCache::RemoveSpriteFrameFromSet(const char* plist)
{

	auto itFiles = m_loadedFileNames.find(plist);
	if(itFiles!= m_loadedFileNames.end())
	{
	    for(auto it = m_spriteFrames.begin();it!=m_spriteFrames.end();)
		{
		    if (it->second->IsSetName(plist))
			{
			    it = m_spriteFrames.erase(it);
				itFiles->second -- ;
			}else
				it++;
		}
		if(itFiles->second ==0)
			m_loadedFileNames.erase(itFiles);
		else{
			CCLOGERROR("CSpriteFrameCache::removeSpriteFramesFromFile number is>0");
		}

	}
}



void CSpriteFrameCache::RemoveSpriteFrameFromTexture(CCTexture2D* texture)
{
	for(auto it = m_spriteFrames.begin();it!=m_spriteFrames.end();)
	{
	    if (it->second->getTexture()==texture)
	    {
		    // 检查文件
		    auto itFiles = m_loadedFileNames.find(it->second->m_strSetName);
		    if(itFiles!= m_loadedFileNames.end())
			{
			    itFiles->second -- ;
				if(itFiles->second ==0)
					m_loadedFileNames.erase(itFiles);
			}
		    it = m_spriteFrames.erase(it);
	    }else
			it++;
	}
}

CCSpriteFrame* CSpriteFrameCache::GetSpriteFrame(const char *pszName)
{
    // 直接查找图片
    auto it = m_spriteFrames.find(pszName);
    if (it != m_spriteFrames.end())
        return it->second.get();


    CCLOG("cocos2d: CSpriteFrameCache: Frame '%s' not found", pszName);
    return nullptr;

}

