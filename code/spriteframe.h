/****************************************************************************
Copyright [2014] Fan Yefei
Copyright [2010-2011] cocos2d-x.org
Copyright [2008-2011] Ricardo Quesada
Copyright [2011]      Zynga Inc.

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


#ifndef __SPRITEFRAME_H__
#define __SPRITEFRAME_H__




#include "CCNode.h"
#include "CCProtocols.h"
#include "CCObject.h"

namespace   cocos2d {
class CCRect;
class CCPoint;
class CCSize;
class CCTexture2D;
class CCZone;

/** @brief A CCSpriteFrame has:
	- texture: A CCTexture2D that will be used by the CCSprite
	- rectangle: A rectangle of the texture


 You can modify the frame of a CCSprite by doing:
 
	CCSpriteFrame *frame = CCSpriteFrame::frameWithTexture(texture, rect, offset);
	sprite->setDisplayFrame(frame);
 */
class CC_DLL CCSpriteFrame : public CCObject
{
 public:
	// attributes

    inline const CCRect& getRectInPixels(void) { return m_obRectInPixels; }
	void setRectInPixels(const CCRect& rectInPixels);

	inline bool isRotated(void) { return m_bRotated; }
	inline void setRotated(bool bRotated) { m_bRotated = bRotated; }

	/** get rect of the frame */
	inline const CCRect& getRect(void) { return m_obRect; }
	/** set rect of the frame */
	void setRect(const CCRect& rect);

	/** get offset of the frame */
	inline const CCPoint& getOffsetInPixels(void) { return m_obOffsetInPixels; }
	/** set offset of the frame */
	inline void setOffsetInPixels(const CCPoint& offsetInPixels) { m_obOffsetInPixels = offsetInPixels; }

	/** get original size of the trimmed image */
	inline const CCSize& getOriginalSizeInPixels(void) { return m_obOriginalSizeInPixels; }
	/** set original size of the trimmed image */
	inline void setOriginalSizeInPixels(const CCSize& sizeInPixels) { m_obOriginalSizeInPixels = sizeInPixels; }

	/** get texture of the frame */
	inline CCTexture2D* getTexture(void) { return m_pobTexture; }
	/** set texture of the frame, the texture is retained */
	inline void setTexture(CCTexture2D* pobTexture)
	{
		CC_SAFE_RETAIN(pobTexture);
		CC_SAFE_RELEASE(m_pobTexture);
		m_pobTexture = pobTexture;
	}

public:
    CCSpriteFrame();
	~CCSpriteFrame(void);
	virtual CCObject* copyWithZone(CCZone *pZone);

	/** Create a CCSpriteFrame with a texture, rect in points.
	 It is assumed that the frame was not trimmed.
	 */
	static CCSpriteFrame* frameWithTexture(CCTexture2D* pobTexture, const CCRect& rect);

	/** Create a CCSpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
	 The originalSize is the size in points of the frame before being trimmed.
	 */
    static CCSpriteFrame* frameWithTexture(CCTexture2D* pobTexture, const CCRect& rect, bool rotated, const CCPoint& offset, const CCSize& originalSize);

public:
	/** Initializes a CCSpriteFrame with a texture, rect in points.
	 It is assumed that the frame was not trimmed.
	 */
	bool initWithTexture(CCTexture2D* pobTexture, const CCRect& rect);

	/** Initializes a CCSpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
	The originalSize is the size in points of the frame before being trimmed.
	*/
	bool initWithTexture(CCTexture2D* pobTexture, const CCRect& rect, bool rotated, const CCPoint& offset, const CCSize& originalSize);
protected:
	CCRect m_obRectInPixels;
	bool   m_bRotated;
	CCRect m_obRect;
	CCPoint m_obOffsetInPixels;
	CCSize m_obOriginalSizeInPixels;
	CCTexture2D *m_pobTexture;
public:
    enum EUVType
    {
        E_UV_BL =0,
        E_UV_BR,
        E_UV_TL,
        E_UV_TR,
        E_UV_MAX,
    };
protected:
    void updateUV();
    ccTex2F m_uv[E_UV_MAX];
public:
	inline bool IsSetName(const std::string& name ) const{return m_strSetName == name;}
protected:
    std::string m_strSetName;    // 对应的数据文件名称
    friend class CSpriteFrameCache;
};

}//namespace   cocos2d 

#endif  // __SPRITEFRAME_H__
