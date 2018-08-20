#include "stdafx.h"
#include "trinity/trinity_widget_manager.h"
#include "base/nextai_log.h"
#include "trinity/trinity_widget_surface.h"

namespace NextAI 
{
	WidgetManager* WidgetManager::getInstance()
	{
		static WidgetManager obj;
		return &obj;
	}

	void WidgetManager::init()
	{
		NEXTAI_TRACE_LOG_START();

		m_root = AllocNiObject(WidgetObject, 0);
		m_root->addChild(AllocNiObject(WidgetSurface, OBJECT_ID_SURFACE_BASE));
		m_root->addChild(AllocNiObject(WidgetSurface, OBJECT_ID_SURFACE_VIEW));
		m_root->addChild(AllocNiObject(WidgetSurface, OBJECT_ID_SURFACE_ONS));
		m_root->addChild(AllocNiObject(WidgetSurface, OBJECT_ID_SURFACE_INTERRUPT));
	}

	void WidgetManager::cleanup()
	{
		NEXTAI_TRACE_LOG_START();

		ReleaseNiObject(m_root);
	}

	void WidgetManager::addView(SURFACE_ID surface, WidgetView* view)
	{
		NEXTAI_INFO_LOG("surface[%d] view[%p]", surface, view);
		if (surface >= SURFACE_ID_BASE && surface < SURFACE_ID_MAX && view != NULL)
			m_root->getItem(surface)->addChild(view);
		else
			NEXTAI_WARNING_LOG("Invalid SURFACE_ID[%d] view[%p]", surface, view);
	}

	void WidgetManager::removeView(SURFACE_ID surface, WidgetView* view)
	{
		NEXTAI_INFO_LOG("surface[%d] view[%p]", surface, view);
		if (surface >= SURFACE_ID_BASE && surface < SURFACE_ID_MAX && view != NULL)
			m_root->getItem(surface)->removeChild(view);
		else
			NEXTAI_WARNING_LOG("Invalid SURFACE_ID[%d] view[%p]", surface, view);
	}

	void WidgetManager::draw()
	{
		size_t loopIdx;
		for (loopIdx = 0; loopIdx < SURFACE_ID_MAX; ++loopIdx)
		{
			if (m_root->getItem(loopIdx) != NULL)
				m_root->getItem(loopIdx)->draw();
		}
	}

	WidgetManager::WidgetManager()
	{
		NEXTAI_TRACE_LOG_START();
		m_root = NULL;
	}

	WidgetManager::~WidgetManager()
	{
		NEXTAI_TRACE_LOG_START();
	}

	BOOL WidgetManager::hardkey(HardkeyID key)
	{
		NEXTAI_INFO_LOG("key[%d]", key);
		// TODO
		return FALSE;
	}

	BOOL WidgetManager::touch(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		NEXTAI_INFO_LOG("touch[%d] touchCount[%d] touchId[%d] touchPos[%d,%d]", touch, touchCount, touchId[0], touchPos[0].x, touchPos[0].y);
		BOOL ret = FALSE;
		size_t loopIdx;
		for (loopIdx = SURFACE_ID_MAX - 1; (loopIdx >= 0) && (ret == FALSE); --loopIdx)
		{
			if (m_root->getItem(loopIdx) != NULL)
				ret = m_root->getItem(loopIdx)->hit(touch, touchCount, touchId, touchPos);
			NEXTAI_INFO_LOG("touch surface[%u,%p] ret[%d]", loopIdx, m_root[loopIdx], ret);
		}
		return ret;
	}

}