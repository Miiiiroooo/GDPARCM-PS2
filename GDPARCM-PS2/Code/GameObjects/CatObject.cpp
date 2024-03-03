#include "CatObject.h"

CatObject::CatObject(std::string name, AGameObject* mouseObj) : AGameObject(name), mouseObj(mouseObj)
{

}

CatObject::CatObject(std::string name) : AGameObject(name)
{

}

CatObject::~CatObject()
{

}

void CatObject::Initialize()
{

}