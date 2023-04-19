#pragma once
#include "GameObject.h"
class AnimationLocalEffect :
    public GameObject
{
public:
    AnimationLocalEffect();
    virtual ~AnimationLocalEffect();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void ReturnToPool() override;

private:
    //DECLARE_POOL(AnimationLocalEffect);

public:
	friend class AnimationLocalEffectPool;
	static shared_ptr<AnimationLocalEffect> Get()
	{
		if (!m_pPool)
			m_pPool = make_unique<AnimationLocalEffectPool>();
		return m_pPool->Get();
	}
static void Release(shared_ptr<AnimationLocalEffect> pAnimationLocalEffect)
{
m_pPool->Release(pAnimationLocalEffect);
}
private:
	class AnimationLocalEffectPool
	{
	public:
		AnimationLocalEffectPool()
			: m_vUse(INITIAL_POOL_COUNT, false)
		{
			m_vPool.reserve(INITIAL_POOL_COUNT);
			for (int i = 0; i < INITIAL_POOL_COUNT; ++i)
			{
				m_vPool.emplace_back(make_shared<AnimationLocalEffect>());
			}
		}
		~AnimationLocalEffectPool() = default;
	public:
		shared_ptr<AnimationLocalEffect> Get()
		{
			for (uint32 i = 0; i < m_vUse.size(); ++i)
			{
				if (!m_vUse[i])
				{
					m_vUse[i] = true;
					return m_vPool[i];
				}
			}
			m_vPool.emplace_back(make_shared<AnimationLocalEffect>());
			m_vUse.push_back(true);
			return m_vPool.back();
		}
		void Release(shared_ptr<AnimationLocalEffect> pAnimationLocalEffect)
		{
			for (uint32 i = 0; i < m_vUse.size(); ++i)
			{
				if (pAnimationLocalEffect == m_vPool[i])
				{
					m_vUse[i] = false;
					break;
				}
			}
		}
	private:
		std::vector<shared_ptr<AnimationLocalEffect>> m_vPool;
		std::vector<bool> m_vUse;
	};
	static unique_ptr<AnimationLocalEffectPool> m_pPool;
private:
	bool m_bUse = false;
};

