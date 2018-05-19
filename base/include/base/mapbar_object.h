#ifndef _MAPBAR_OBJECT_H_
#define _MAPBAR_OBJECT_H_

#include "base/mapbar_basic_types.h"

namespace MapBarDL
{
	class MbObject
	{
	public:
		MbObject();
		virtual ~MbObject();
		
		/* 申请空间 */
		void alloc(size_t size);
		size_t getSize() { return m_bufferSize; }		/* 空间大小只能获取。修改请使用alloc */

		/* 增加引用计数 */
		void addRef() { ++m_refCount; }
		void removeRef() { --m_refCount; }
		size_t getRefCount() { return m_refCount; }

		/* 设定申请空间的步长 */
		void setStep(size_t step) { m_bufferStep = step; }
		size_t getStep() { return m_bufferStep; }

	private:
		MbObject(const MbObject&);
		MbObject& operator=(const MbObject&);

		void recycle(size_t size);

		void* m_buffer;
		size_t m_bufferSize;
		size_t m_bufferStep;	/* 默认1k */
		size_t m_refCount;
	};
}

#endif // !_MAPBAR_OBJECT_H_