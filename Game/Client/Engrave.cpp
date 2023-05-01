#include "pch.h"
#include "Engrave.h"
#include "Texture.h"
#include "Resources.h"

Engrave::Engrave(ENGRAVE eEngrave)
	: m_eEngrave(eEngrave)
	, m_eEngraveState(ENGRAVE_STATE::DEACTIVATE)
	, m_iFullCount(0)
{
}

Engrave::~Engrave()
{
}

shared_ptr<Texture> Engrave::GetEngraveTexture(ENGRAVE eEngrave, ENGRAVE_STATE eEngraveState)
{
	switch (eEngrave)
	{
	case ENGRAVE::SUN_AND_MOON:
		break;
	case ENGRAVE::SOUL:
		break;
	case ENGRAVE::WISDOM:
		break;
	case ENGRAVE::RAPIDITY:
		switch (eEngraveState)
		{
		case ENGRAVE_STATE::DEACTIVATE:
			return GET_SINGLE(Resources)->Load<Texture>(L"Rapidity_Deactivation", L"..\\Resources\\Texture\\Engrave\\Rapidity\\Image_Rapidity_Deactivation.png");
		case ENGRAVE_STATE::ACTIVATE:
			return GET_SINGLE(Resources)->Load<Texture>(L"Rapidity_Activation", L"..\\Resources\\Texture\\Engrave\\Rapidity\\Image_Rapidity_Activation.png");
		case ENGRAVE_STATE::FULL_ACTIVATE:
			return GET_SINGLE(Resources)->Load<Texture>(L"Rapidity_Full_Activation", L"..\\Resources\\Texture\\Engrave\\Rapidity\\Image_Rapidity_Activation.png");
		}
		break;
	case ENGRAVE::MAGIC_TOOL:
		break;
	case ENGRAVE::SOAR:
		break;
	case ENGRAVE::MISFORTUNE:
		break;
	case ENGRAVE::ARMS:
		switch (eEngraveState)
		{
		case ENGRAVE_STATE::DEACTIVATE:
			return GET_SINGLE(Resources)->Load<Texture>(L"Arms_Deactivation", L"..\\Resources\\Texture\\Engrave\\Arms\\Image_Arms_Deactivation.png");
		case ENGRAVE_STATE::ACTIVATE:
			return GET_SINGLE(Resources)->Load<Texture>(L"Arms_Activation", L"..\\Resources\\Texture\\Engrave\\Arms\\Image_Arms_Activation.png");
		case ENGRAVE_STATE::FULL_ACTIVATE:
			return GET_SINGLE(Resources)->Load<Texture>(L"Arms_Full_Activation", L"..\\Resources\\Texture\\Engrave\\Arms\\Image_Arms_Activation.png");
		}
		break;
	case ENGRAVE::KNELL:
		break;
	}

	assert(nullptr);
	return nullptr;
}

shared_ptr<Texture> Engrave::GetActivationTexture()
{
	return GetEngraveTexture(m_eEngrave, ENGRAVE_STATE::ACTIVATE);
}

shared_ptr<Texture> Engrave::GetDectivationTexture()
{
	return GetEngraveTexture(m_eEngrave, ENGRAVE_STATE::DEACTIVATE);
}

shared_ptr<Texture> Engrave::GetFullActivationTexture()
{
	return GetEngraveTexture(m_eEngrave, ENGRAVE_STATE::FULL_ACTIVATE);
}