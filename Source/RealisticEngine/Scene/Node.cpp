#include "RealisticEngine/Scene/Node.h"
#include <iostream>
#include "RealisticEngine/Renderer/DrawInterface.h"
#include "RealisticEngine/Renderer/Asset.h"

using namespace RealisticEngine::Scene;


/*
 * Public methods for class Node
 */

Node::Node()
{
  mParent = NULL;
  mTransform = glm::mat4(1);
  mPrevGlobalTransform = glm::mat4(1);
}

void Node::SetLocalTransform(glm::mat4 transform)
{
  mTransform = transform;
}

glm::mat4 Node::GetLocalTransform()
{
  return mTransform;
}


glm::mat4 Node::GetGlobalTransform()
{
  if(mParent == NULL)
  {
    return mTransform;
  }

  return mParent->GetGlobalTransform() * mTransform;
}

glm::mat4* Node::GetGlobalInterpolator()
{
  return &mInterpolator;
}
glm::mat3* Node::GetNormalMatrix()
{
  return &mNormalMatrix;
}

void Node::SetParent(Node *parent)
{
  mParent = parent;
}

int Node::AddChild(Node* child)
{
  child->SetParent(this);
  mChildren.push_back(child);
  return mChildren.size();
}

int Node::RemoveChild(Node *child)
{
  int i;
  for(i = 0; i < mChildren.size(); i++)
  {
    if(mChildren[i] == child)
    {
      mChildren.erase(mChildren.begin() + i);
      return i;
    }
  }

  return -1;
}

int Node::AddAction(Action *action)
{
  mActions.push_back(action);
  return mActions.size();
}

int Node::RemoveAction(Action *action)
{
  int i;
  for(i = 0; i < mActions.size(); i++)
  {
    if(mActions[i] == action)
    {
      mActions.erase(mActions.begin() + i);
      return i;
    }
  }

  return -1;
}

int Node::AddDrawInterface(Renderer::DrawInterface *drawInterface)
{
  mDrawInterfaces.push_back(drawInterface);
  return mDrawInterfaces.size();
}

int Node::RemoveDrawInterface(Renderer::DrawInterface *drawInterface)
{
  int i;
  for(i = 0; i < mDrawInterfaces.size(); i++)
  {
    if(mDrawInterfaces[i] == drawInterface)
    {
      mDrawInterfaces.erase(mDrawInterfaces.begin() + i);
      return i;
    }
  }

  return -1;
}

int Node::AddAsset(Renderer::Asset* asset)
{
  mAssets.push_back(asset);
}

int Node::RemoveAsset(Renderer::Asset *asset)
{
  int i;
  for(i = 0; i < mAssets.size(); i++)
  {
    if(mAssets[i] == asset)
    {
      mAssets.erase(mAssets.begin() + i);
      return i;
    }
  }

  return -1;
}

Node* Node::GetParent()
{
  return mParent;
}

int Node::GetChildren(Node** children)
{
  for(int i = 0; i < mChildren.size(); i++)
    children[i] = mChildren[i];

  return mChildren.size();
}

void Node::Update()
{
  mPrevGlobalTransform = GetGlobalTransform();

  for(int i = 0; i < mChildren.size(); i++)
  {
    mChildren[i]->Update();
  }
  for(int i = 0; i < mActions.size(); i++)
  {
    mActions[i]->performAction();
  }
}

void Node::Draw(float delta)
{
  glm::mat4 globalTransform = GetGlobalTransform();

  mInterpolator = globalTransform * delta + mPrevGlobalTransform * (1-delta);
  mNormalMatrix = glm::mat3(glm::transpose(glm::inverse(mInterpolator)));

  for(int i = 0; i < mAssets.size(); i++)
  {
    mAssets[i]->Bind();
  }

  for(int i = 0; i < mDrawInterfaces.size(); i++)
  {
    mDrawInterfaces[i]->Draw();
  }

  for(int i = 0; i < mAssets.size(); i++)
  {
    mAssets[i]->UnBind();
  }

  for(int i = 0; i < mChildren.size(); i++)
  {
    mChildren[i]->Draw(delta);
  }


}