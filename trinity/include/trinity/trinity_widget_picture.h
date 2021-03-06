#ifndef _TRINITY_WIDGET_PICTURE_H_
#define _TRINITY_WIDGET_PICTURE_H_

#include "trinity_widget_object.h"

namespace NextAI
{
	/*
	 * 图片控件，支持BMP，JPG等多种图片格式。
	 * 内部使用FreeImage支持图片的加载
	 */
	class WidgetPicture : public WidgetObject
	{
	public:
	
		/* 利用一张图片形成多个WidgetPicture */
		static bool allocPictures(const std::wstring& path, int32 size, std::vector<std::shared_ptr<WidgetPicture>>& pictures);
		
		/* 构造函数 */
		WidgetPicture(ObjectId id);
		virtual ~WidgetPicture();
		
		/* 描画 */
		virtual void drawImpl();
		
		/* 图片路径
		 * 不要频繁调用本函数，会涉及到纹理的申请和释放 */
		virtual void setPath(const std::wstring& path);
		virtual std::wstring getPath();
		
		/* 当前是否是可用的 */
		virtual bool isValid() { return m_picture != INVALID_TEXTURE_ID; }
		
	private:
	
		/* 禁用构造函数 */
		DISABLE_CLASS_COPY(WidgetPicture);
		
		/* 释放纹理 */
		void release();
		
	private:
	
		/* 图片资源纹理 */
		PICTURE_TEXTURE_ID m_picture;
		
		/* 文件路径 */
		std::wstring m_path;
		
	};
}

#endif // !_TRINITY_WIDGET_PICTURE_H_