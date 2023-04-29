#pragma once
#include "UI.h"
class InfoUI;
class DetailInfoUI;
class InventoryUI :
    public UI
{
public:
    InventoryUI();
    virtual ~InventoryUI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    virtual void Enable();
    virtual void Disable();

private:
    void CreateChildUIAndAddedToScene();
    void CreateSkulInfoUI();
    void CreateArtifactInfoUI();
    void CreateItemInfoUI();
    void CreateDarkAbilInfoUI();
    void CreateDetailInfoUI();

private:
    std::vector<shared_ptr<InfoUI>> m_vSkulInfoUI;
    std::vector<shared_ptr<InfoUI>> m_vItemInfoUI;
    std::vector<shared_ptr<InfoUI>> m_vArtifactInfoUI;
    std::vector<shared_ptr<InfoUI>> m_vDarkAbilInfoUI;

    shared_ptr<DetailInfoUI> m_pDetailInfoUI;

    // Awake���� Child ui�� ��� ���� �߰���Ų��.
    // Child ui�� �θ� ui�� enable�� �� ���� enable��
    // ��ǥ��� �θ��� ��ǥ�踦 ������
    // active�� ������ ���� �Ǵ� ������ �� �ϳ��̸�, 
    // active�� ������ nullptr�� �ƴ� ��� �ش� ������ ������ ǥ���Ѵ�.
    // ǥ�ô� ������ ��ġ�� �ؽ�Ʈ�� �̹����� �ִ� ���
    // �� �ؽ�Ʈ�� �̹����� �������̳� ������ ����
    // SkulInfo = �÷��̾ �������� ���ÿ��� �̹����� �����´�.
    // ItemInfo = �÷��̾ �������� �����ۿ��� �̹����� �����´�.

};
