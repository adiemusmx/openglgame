#include "widget_object.h"
#include "util_log.h"
#include <algorithm>

namespace Trinity
{

WidgetObject::WidgetObject(ObjectId id)
{
	m_id = id;

	m_drawableArea = { 0, 0, 0, 0 };
	m_hitableArea = { 0, 0, 0, 0 };

	m_hitEnable = FALSE;
	m_hitTransEnable = TRUE;

	m_visible = TRUE;
	m_needsRefresh = TRUE;
}

WidgetObject::~WidgetObject()
{
	m_children.clear();
}

void WidgetObject::addChild(WidgetObject* child)
{
	if (child == NULL)
	{
		TRI_WARNING_LOG("Add null pointer object!");
		return;
	}
	auto pObj = std::find(m_children.begin(), m_children.end(), child);
	if (pObj == m_children.end())
	{
		m_children.push_back(child);
	}
	else
	{
		TRI_WARNING_LOG("Add same object[%lu], it's weird.", child->m_id);
	}
}

void WidgetObject::removeChild(WidgetObject* child)
{
	if (child == NULL)
	{
		TRI_WARNING_LOG("Remove null pointer object!");
		return;
	}
	auto pObj = std::find(m_children.begin(), m_children.end(), child);
	if (pObj != m_children.end())
	{
		m_children.erase(pObj);
	}
	else
	{
		TRI_WARNING_LOG("Can't find object[%lu], it's weird.", child->m_id);
	}
}

BOOL WidgetObject::isChild(WidgetObject* child)
{
	if (child == NULL)
	{
		TRI_WARNING_LOG("Remove null pointer object!");
		return FALSE;
	}
	auto pObj = std::find(m_children.begin(), m_children.end(), child);
	if (pObj == m_children.end())
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

WidgetObject* WidgetObject::getObjectById(ObjectId id)
{
	if (id == m_id)
		return this;

	WidgetObject* ret = NULL;
	for (auto pObj : m_children)
	{
		ret = pObj->getObjectById(id);
		if (ret != NULL)
		{
			break;
		}
	}
	return ret;
}

void WidgetObject::draw()
{
	for (auto pObj : m_children)
	{
		pObj->draw();
	}
	drawImpl();
}

void WidgetObject::drawImpl()
{
	// TODO
}

void WidgetObject::setDrawableArea(const RECT& area)
{
	m_drawableArea = area;
}

const RECT& WidgetObject::getDrawableArea()
{
	return m_drawableArea;
}

BOOL WidgetObject::hit(HIT_EVENT_TYPE hitEventType, POINT finger1, POINT finger2)
{
	if (!m_visible || !m_hitEnable)
		return false;

	if (!RECT_testPOINT(m_hitableArea, finger1))
		return false;

	for (auto pObj : m_children)
	{
		if (pObj->hit(hitEventType, finger1, finger2) == TRUE)
			return TRUE;
	}

	if (hitImpl(hitEventType, finger1, finger2) || !m_hitTransEnable)
		return TRUE;
	else
		return FALSE;
}

BOOL WidgetObject::hitImpl(HIT_EVENT_TYPE hitEventType, POINT finger1, POINT finger2)
{
	// TODO
	return FALSE;
}

void WidgetObject::setHitableArea(const RECT& area)
{
	m_hitableArea = area;
}

const RECT& WidgetObject::getHitableArea()
{
	return m_hitableArea;
}

void WidgetObject::setVisible(BOOL visible)
{
	m_visible = visible;
}

BOOL WidgetObject::getVisible()
{
	return m_visible;
}

void WidgetObject::setHitEnable(BOOL hitEnable)
{
	m_hitEnable = hitEnable;
}

BOOL WidgetObject::getHitEnable()
{
	return m_hitEnable;
}

void WidgetObject::setHitTransEnable(BOOL hitTransEnable)
{
	m_hitTransEnable = hitTransEnable;
}

BOOL WidgetObject::getHitTransEnable()
{
	return m_hitTransEnable;
}

void WidgetObject::invalidate()
{
	m_needsRefresh = TRUE;
}

BOOL WidgetObject::isNeedsRefresh()
{
	return m_needsRefresh;
}

}