#include "pch.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Controller.h"
#include "Engine.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Physical.h"

RigidBody::RigidBody()
	: Component(COMPONENT_TYPE::RIGIDBODY)
{

}

RigidBody::~RigidBody()
{
}

void RigidBody::Awake()
{

}

void RigidBody::FinalUpdate()
{
}
