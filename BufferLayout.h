#pragma once
#include <vector>
#include "glad/glad.h"

namespace Aroa
{
	
	struct BufferElement
	{
		BufferElement(unsigned int type,unsigned int count, unsigned char normalized)
		: type(type),count(count),normalized(normalized){}
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int type) {

			switch (type)
			{
				case GL_FLOAT: return 4;
				case GL_UNSIGNED_INT: return 4;
				case GL_UNSIGNED_BYTE: return 1;
			default:
				printf("No Size");
				break;
			}
			return 0;
		}
	};

	class BufferLayout 
	{
	public:
		
		BufferLayout(): m_Stride(0){}

		template<typename T>
		void Push(unsigned int count) {
			static_assert(false);
		}

		template<>
		void Push<float>(unsigned int count) {
			m_Elements.push_back(BufferElement(GL_FLOAT,count,GL_FALSE));
			m_Stride += BufferElement::GetSizeOfType(GL_FLOAT) * count;
		}

		template<>
		void Push<unsigned int>(unsigned int count) {
			m_Elements.push_back(BufferElement(GL_UNSIGNED_INT, count, GL_FALSE));
			m_Stride += BufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;

		}

		template<>
		void Push<unsigned char>(unsigned int count) {
			m_Elements.push_back(BufferElement(GL_UNSIGNED_BYTE, count, GL_TRUE));
			m_Stride += BufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;

		}

		inline unsigned int GetStride()const{ return m_Stride; }
		inline const std::vector<BufferElement> GetElements() const { return m_Elements; }
	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride;
	};
}