#include "pch.h"
#include "Context.h"

Context::Context()
{
}

Context::~Context()
{
}

void Context::Init(ComPtr<ID3D11DeviceContext> pContext)
{
	m_pContext = pContext;
}

