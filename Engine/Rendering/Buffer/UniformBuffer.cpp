#include "UniformBuffer.h"

#include <glad/glad.h>

namespace OrbEngine
{
	UniformBuffer::UniformBuffer(int bindPoint, int byteSize) :
		m_UBO(0), m_BindPoint(bindPoint)
	{
		glGenBuffers(1, &m_UBO);
		glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
		glBufferData(GL_UNIFORM_BUFFER, byteSize, nullptr, GL_STATIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, m_BindPoint, m_UBO);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	UniformBuffer::~UniformBuffer()
	{
		glDeleteBuffers(1, &m_UBO);
	}

	void UniformBuffer::UpdateBuffer(int offset, int size, const void* data)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}