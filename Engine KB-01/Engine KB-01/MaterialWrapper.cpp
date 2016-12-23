#include "MaterialWrapper.h"


	/**
	* Function: MaterialWrapper::MaterialWrapper(D3DMATERIAL9 _material)
	* Description: Constructor
	*/
	MaterialWrapper::MaterialWrapper(D3DMATERIAL9 _material)
	{
		material = _material;
	};

	/**
	* Function: MaterialWrapper::~MaterialWrapper()
	* Description: Destructor
	*/
	MaterialWrapper::~MaterialWrapper()
	{
	};


	/**
	* Function: MaterialWrapper::SetMaterial(D3DMATERIAL9 _material)
	* Description: Sets the material that's contained within this class
	*/
	void MaterialWrapper::SetMaterial(D3DMATERIAL9 _material)
	{
		material = _material;
	};


	/**
	* Function: MaterialWrapper::GetMaterial()
	* Description: Gets the material that's contained within this class
	*/
	D3DMATERIAL9 MaterialWrapper::GetMaterial()
	{
		return material;
	};




