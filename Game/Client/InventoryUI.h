#pragma once
#include "UI.h"
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

private:
    void CreateChildUIAndAddedToScene();
    void CreateSkulInfoUI();
    void CreateItemInfoUI();

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

