#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned int depthMapID)
	: m_DepthMapID(depthMapID)
{
	GLCall(glGenFramebuffers(1, &m_RendererID));
}

FrameBuffer::~FrameBuffer()
{

}

void FrameBuffer::Bind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthMapID, 0));
	GLCall(glClear(GL_DEPTH_BUFFER_BIT));
	GLCall(glDrawBuffer(GL_NONE));
	GLCall(glReadBuffer(GL_NONE));
}

void FrameBuffer::Unbind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}
