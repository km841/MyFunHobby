#pragma once
#include "Object.h"
class Mesh :
    public Object
{
public:
    Mesh();
    virtual ~Mesh();

    void Init(const std::vector<Vertex>& vVertexBuffer, const std::vector<uint32>& vIndexBuffer);
    void Render(uint32 iInstanceCount = 1);
    void RenderInstanced(uint32 iInstanceCount = 1);

public:
    void CreateVertexBuffer(const std::vector<Vertex>& vBuffer);
    void CreateIndexBuffer(const std::vector<uint32>& vBuffer);

public:

private:
    ComPtr<ID3D11Buffer> m_pVertexBuffer;
    ComPtr<ID3D11Buffer> m_pIndexBuffer;
    
    uint32               m_iIndexCount;
};

