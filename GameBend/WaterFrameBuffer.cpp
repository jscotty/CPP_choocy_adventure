#include "WaterFrameBuffer.h"

#include <iostream>

WaterFrameBuffer::WaterFrameBuffer(){
	InitialiseReflectionFrameBuffer();
	InitialiseRefractionFrameBuffer();
}

WaterFrameBuffer::~WaterFrameBuffer(){
	glDeleteFramebuffers(1, &m_reflectionFrameBuffer);
	glDeleteTextures(1, &m_reflectionTexture);
	glDeleteRenderbuffers(1, &m_reflectionDepthBuffer);

	glDeleteFramebuffers(1, &m_refractionFrameBuffer);
	glDeleteTextures(1, &m_refractionTexture);
	glDeleteTextures(1, &m_refractionDepthTexture);
}

void WaterFrameBuffer::BindReflectionFrameBuffer() {
	BindFrameBufferReflection(REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void WaterFrameBuffer::BindRefractionFrameBuffer() {
	BindFrameBufferRefraction(REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void WaterFrameBuffer::UnbindCurrentFrameBuffer() {
	glBindFramebuffer( GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 800, 600);
}

void WaterFrameBuffer::InitialiseReflectionFrameBuffer() {
	CreateReflectionFrameBuffer();
	CreateReflectionTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	CreateReflectionDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	UnbindCurrentFrameBuffer();
}

void WaterFrameBuffer::InitialiseRefractionFrameBuffer() {
	CreateRefractionFrameBuffer();
	CreateRefractionTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	CreateRefractionDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	UnbindCurrentFrameBuffer();
}

void WaterFrameBuffer::BindFrameBufferReflection(int width, int height) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, m_reflectionFrameBuffer);
	glViewport(0, 0, width, height);
}

void WaterFrameBuffer::BindFrameBufferRefraction(int width, int height) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, m_refractionFrameBuffer);
	glViewport(0, 0, width, height);
}

void WaterFrameBuffer::CreateReflectionFrameBuffer() {
	glGenFramebuffers(1, &m_reflectionFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_reflectionFrameBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

void WaterFrameBuffer::CreateRefractionFrameBuffer() {
	glGenFramebuffers(1, &m_refractionFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_refractionFrameBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

void WaterFrameBuffer::CreateReflectionTextureAttachment(int width, int height) {
	glGenTextures(1, &m_reflectionTexture);
	glBindTexture(GL_TEXTURE_2D, m_reflectionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_reflectionTexture, 0);
}

void WaterFrameBuffer::CreateRefractionTextureAttachment(int width, int height) {
	glGenTextures(1, &m_refractionTexture);
	glBindTexture(GL_TEXTURE_2D, m_refractionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_refractionTexture, 0);
}

void WaterFrameBuffer::CreateRefractionDepthTextureAttachment(int width, int height) {
	glGenTextures(1, &m_refractionDepthTexture);
	glBindTexture(GL_TEXTURE_2D, m_refractionDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_refractionDepthTexture, 0);
}

void WaterFrameBuffer::CreateReflectionDepthBufferAttachment(int width, int height) {
	glGenRenderbuffers(1, &m_reflectionDepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_reflectionDepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_reflectionDepthBuffer);
}

