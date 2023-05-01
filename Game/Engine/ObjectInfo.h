#pragma once
struct ObjectInfo
{
	wstring GradeEnumToWstring()
	{
		switch (eGrade)
		{
		case GRADE::NORMAL:
			return L"노멀";
		case GRADE::RARE:
			return L"레어";
		case GRADE::UNIQUE:
			return L"유니크";
		case GRADE::REGENDARY:
			return L"레전더리";
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
	ESSENCE_TYPE eEssenceType;
	float fCooldown;
	float fDuration;
};


struct ItemInfo
	: public ObjectInfo
{
	shared_ptr<class Texture> pItemTexture;
	shared_ptr<class Engrave> pFirstEngrave;
	shared_ptr<class Engrave> pSecondEngrave;
};

struct SkillInfo
	: public ObjectInfo
{
	shared_ptr<class Texture> pSkillTexture;
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
			return L"리틀 본";
		case SKUL_KIND::HIGH_WARLOCK:
			return L"대마도사";
		}
		assert(nullptr);
		return L"";
	}

	wstring SkulTypeEnumToWstring()
	{
		switch (eSkulType)
		{
		case SKUL_TYPE::SPEED:
			return L"스피드";
		case SKUL_TYPE::BALANCE:
			return L"밸런스";
		case SKUL_TYPE::POWER:
			return L"파워";
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