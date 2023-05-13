#pragma once
class Texture;
class Engrave;
struct ObjectInfo
{
	wstring GradeEnumToWstring()
	{
		switch (eGrade)
		{
		case GRADE::NORMAL:
			return L"���";
		case GRADE::RARE:
			return L"����";
		case GRADE::UNIQUE:
			return L"����ũ";
		case GRADE::LEGENDARY:
			return L"��������";
		}
		assert(nullptr);
		return L"";
	}

public:
	shared_ptr<class Texture> pVignetteTexture;
	Vec2					  vVignetteTextureOffset;
	wstring					  szName;
	wstring					  szComment;
	wstring					  szExplanation;
	GRADE					  eGrade;
};



struct EssenceInfo
	: public ObjectInfo
{
	shared_ptr<Texture> pEssenceTexture;
	ESSENCE_TYPE eEssenceType;
	float fCooldown;
	float fDuration;
	wstring szSkillName;
};


struct ItemInfo
	: public ObjectInfo
{
	shared_ptr<Texture> pItemTexture;
	shared_ptr<Engrave> pFirstEngrave;
	shared_ptr<Engrave> pSecondEngrave;
};

struct SkillInfo
	: public ObjectInfo
{
	shared_ptr<Texture> pSkillTexture;
	SKILL_TYPE eSkillType;
	float fCooldown;
	float fDuration;
	bool bUse;
};

struct SkulInfo
	: public ObjectInfo
{
	wstring SkulKindEnumToWstring()
	{
		switch (eSkulKind)
		{
		case SKUL_KIND::LITTLE_BONE:
			return L"��Ʋ ��";
		case SKUL_KIND::HIGH_WARLOCK:
			return L"�븶����";
		}
		assert(nullptr);
		return L"";
	}

	wstring SkulTypeEnumToWstring()
	{
		switch (eSkulType)
		{
		case SKUL_TYPE::SPEED:
			return L"���ǵ�";
		case SKUL_TYPE::BALANCE:
			return L"�뷱��";
		case SKUL_TYPE::POWER:
			return L"�Ŀ�";
		}
		assert(nullptr);
		return L"";
	}

	SKUL_KIND eSkulKind;
	SKUL_TYPE eSkulType;
	SKILL_INDEX eTotalSkills;

	SkillInfo FirstSkillInfo;
	SkillInfo SecondSkillInfo;
	SkillInfo SwapSkillInfo;
};