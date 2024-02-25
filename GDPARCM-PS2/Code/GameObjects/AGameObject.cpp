#include "AGameObject.h"
#include "../Components/Input/GenericInputController.h"

#pragma region Constructor-Destructor
AGameObject::AGameObject(std::string name)
{
	this->name = name;
	this->parent = NULL; 
}

AGameObject::~AGameObject()
{
	for (size_t i = 0; i < this->childList.size(); i++)
	{
		delete this->childList[i];
	}

	for (size_t i = 0; i < this->componentList.size(); i++) 
	{
		delete this->componentList[i]; 
	}

	this->childList.clear();
	this->childList.shrink_to_fit(); 
	this->componentList.clear(); 
	this->componentList.shrink_to_fit(); 
	 
	if (this->parent != NULL) 
	{
		this->parent = NULL; 
	}

	if (this->sprite != NULL) 
	{
		delete this->sprite; 
		this->sprite = NULL; 
	}

	if (this->texture != NULL)
	{
		this->texture = NULL; 
	}
}
#pragma endregion


#pragma region Game-related methods
void AGameObject::ProcessInputs(sf::Event event)
{
	if (this->enabled)
	{
		std::vector<AComponent*> componentList = this->GetComponentsOfType(EComponentTypes::Input);

		for (size_t i = 0; i < componentList.size(); i++)
		{
			GenericInputController* inputController = (GenericInputController*)componentList[i];
			inputController->AssignEvent(event); 
			inputController->Perform(); 
		}

		for (size_t i = 0; i < this->childList.size(); i++)
		{
			this->childList[i]->ProcessInputs(event); 
		}
	}
}

void AGameObject::Update(sf::Time dt) 
{
	if (this->enabled)
	{
		std::vector<AComponent*> componentList = this->GetComponentsOfType(EComponentTypes::Script); 

		for (size_t i = 0; i < componentList.size(); i++)
		{
			componentList[i]->SetDeltaTime(dt);  
			componentList[i]->Perform(); 
		}


		for (size_t i = 0; i < childList.size(); i++)
		{
			childList[i]->Update(dt);  
		}
	}
}

void AGameObject::Draw(sf::RenderWindow* window, sf::RenderStates renderStates)
{
	if (this->enabled) 
	{
		std::vector<AComponent*> rendererList = this->GetComponentsOfType(EComponentTypes::Renderer); 
		renderStates.transform *= this->transformable.getTransform();

		for (size_t i = 0; i < rendererList.size(); i++) 
		{
			Renderer* renderer = (Renderer*)rendererList[i];  
			renderer->AssignTargetWindow(window); 
			renderer->SetRenderStates(renderStates); 
			renderer->Perform();
		}

		for (size_t i = 0; i < childList.size(); i++) 
		{
			this->childList[i]->Draw(window, renderStates); 
		}
	}
}

std::string AGameObject::GetName()
{
	return this->name;
}

bool AGameObject::IsEnabled()
{
	return enabled;
}

void AGameObject::SetEnabled(bool flag)
{
	enabled = flag;
}
#pragma endregion


#pragma region SFML-related methods
sf::Sprite* AGameObject::GetSprite()
{
	return this->sprite;
}

sf::Transformable* AGameObject::GetTransformable()
{
	return &this->transformable;
}

sf::Transform AGameObject::GetGlobalTransform()
{
	AGameObject* parentObj = this; 
	std::vector<AGameObject*> parentList; 

	while (parentObj != NULL) 
	{
		parentList.push_back(parentObj); 
		parentObj = parentObj->GetParent();  
	}

	sf::Transform transform = sf::Transform::Identity; 
	int startIdx = parentList.size() - 1; 

	for (int i = startIdx; i >= 0; i--) 
	{
		transform = transform * parentList[i]->GetTransformable()->getTransform(); 
	}

	return transform;
}

void AGameObject::SetLocalPosition(float x, float y)
{
	this->transformable.setPosition(x, y);
}

void AGameObject::SetGlobalPosition(float x, float y)
{
	AGameObject* parentObj = this;
	std::vector<AGameObject*> parentList;

	while (parentObj != NULL)
	{
		parentList.push_back(parentObj);
		parentObj = parentObj->GetParent();
	}

	sf::Transform transform = sf::Transform::Identity;
	int startIdx = parentList.size() - 1;

	for (int i = startIdx; i >= 0; i--)
	{
		transform = transform * parentList[i]->GetTransformable()->getTransform();
	}

	sf::Vector2f newPos = sf::Vector2f(x, y) - transform.transformPoint(0, 0);
	this->transformable.setPosition(newPos); 
}

sf::Vector2f AGameObject::GetLocalPosition()
{
	return this->transformable.getPosition();
}

sf::Vector2f AGameObject::GetGlobalPosition()
{
	return GetGlobalTransform().transformPoint(0,0);
}
#pragma endregion


#pragma region Inheritance-related methods
void AGameObject::AttachChild(AGameObject* child)
{
	if (child == this)
	{
		return;
	}

	this->childList.push_back(child); 
	child->SetParent(this);
	child->Initialize(); 
}

void AGameObject::DetachChild(AGameObject* child)
{
	int index = -1;

	for (size_t i = 0; i < this->childList.size(); i++)
	{
		if (this->childList[i] == child) 
		{
			index = (int)i; 
		}
	}

	if (index != -1)
	{
		this->childList.erase(this->childList.begin() + index); 
	}

	child->SetParent(NULL); 

	//this->childList.erase(std::remove(this->childList.begin(), this->childList.end(), child), this->childList.end());
}

AGameObject* AGameObject::GetParent()
{
	return this->parent;
}

void AGameObject::SetParent(AGameObject* parent) 
{
	this->parent = parent; 
}
#pragma endregion


#pragma region Component-related methods
void AGameObject::AttachComponent(AComponent* component)
{
	this->componentList.push_back(component);  
	component->AttachOwner(this);  
}

void AGameObject::DetachComponent(AComponent* component)
{
	int index = -1; 

	for (size_t i = 0; i < this->componentList.size(); i++) 
	{
		if (this->componentList[i] == component) 
		{
			index = (int)i; 
			this->componentList[i]->DetachOwner(); 
			break;
		}
	}

	if (index != -1) 
	{
		this->componentList.erase(this->componentList.begin() + index); 
	}
}

AComponent* AGameObject::FindComponentByName(std::string name)
{
	for (size_t i = 0; i < componentList.size(); i++) 
	{
		if (this->componentList[i]->GetName() == name) 
		{
			return this->componentList[i]; 
		}
	}

	return NULL;
}

AComponent* AGameObject::FindComponentByType(EComponentTypes type, std::string name)
{
	for (size_t i = 0; i < componentList.size(); i++)
	{
		if (this->componentList[i]->GetType() == type && this->componentList[i]->GetName() == name) 
		{
			return this->componentList[i]; 
		}
	}

	return NULL; 
}

std::vector<AComponent*> AGameObject::GetComponentsOfType(EComponentTypes type)
{
	std::vector<AComponent*> foundList; 

	for (size_t i = 0; i < this->componentList.size(); i++)
	{
		if (this->componentList[i]->GetType() == type)
		{
			foundList.push_back(this->componentList[i]); 
		}
	}

	return foundList; 
}

////recursive implementation; also searches through its children
//std::vector<AComponent*> AGameObject::GetComponentsOfTypeRecursive(AComponent::ComponentType type)
//{
//	std::vector<AComponent*> foundList; 
//
//	for (size_t i = 0; i < this->componentList.size(); i++)
//	{
//		if (this->componentList[i]->getType() == type)
//		{
//			foundList.push_back(this->componentList[i]);
//		}
//	}
//
//	for (size_t i = 0; i < childList.size(); i++)
//	{
//		foundList = this->GetComponentRecursiveProper(this->childList[i], type, foundList); 
//	}
//
//	return foundList;
//}
//
//std::vector<AComponent*> AGameObject::GetComponentRecursiveProper(AGameObject* object, AComponent::ComponentType type, std::vector<AComponent*> foundList)
//{
//	return foundList; 
//}
#pragma endregion