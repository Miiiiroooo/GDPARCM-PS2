#include "IrisFadeObject.h"
#include "../../Game.h"
#include "../../Components/Renderer.h"
#include "../../Components/Scripts/IrisFadeBehaviorScript.h"
#include <iostream>

IrisFadeObject::IrisFadeObject(AGameObject* mouse) : AGameObject("IrisFadeObject"), mouse(mouse)
{
	irisTexture = NULL;
}

IrisFadeObject::~IrisFadeObject()
{
	delete irisTexture;
}

void IrisFadeObject::Initialize()
{
	IrisFadeBehaviorScript* script = new IrisFadeBehaviorScript();
	this->AttachComponent(script); 
	script->Initialize();
	script->OnFadeOut(); 

	Renderer* renderer = new Renderer("IrisFadeRenderer"); 
	renderer->AssignDrawable(sprite); 
	this->AttachComponent(renderer); 

	this->SetGlobalPosition(mouse->GetGlobalPosition().x, mouse->GetGlobalPosition().y); 
}