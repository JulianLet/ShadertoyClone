#pragma once
#include "Common.h"

class FrameBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_DepthMapID;
public:
	FrameBuffer(unsigned int depthMapID);
	~FrameBuffer();

	void Bind() const;
	void Unbind() const;
};