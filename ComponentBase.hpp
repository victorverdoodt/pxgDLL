#pragma once
#ifndef  COMPONENTBASE
#define COMPONENTBASE
//team
extern std::vector<DWORD>pComponents;

class pComponent
{
public:
	pComponent() {};
	~pComponent() {};
	virtual void onStart(Game game) = 0;
	virtual void onUpdate(Game game) = 0;
	virtual void onMenu() = 0;
	void Add()
	{
		pComponents.push_back(reinterpret_cast<DWORD>(this));
	}

	static void ComponentsEvent_onUpdate(Game game)
	{


		for (DWORD pPtr : pComponents)
		{
			pComponent*component = reinterpret_cast<pComponent*>(pPtr);
			component->onUpdate(game);
		}
	}
	static void ComponentEvents_onStart(Game game)
	{
		for (DWORD pPtr : pComponents)
		{
			pComponent*component = reinterpret_cast<pComponent*>(pPtr);
			component->onStart(game);
		}
	}
	static void ComponentEvents_onMenu()
	{


		for (DWORD pPtr : pComponents)
		{
			pComponent*component = reinterpret_cast<pComponent*>(pPtr);
			component->onMenu();
		}
	}

	char classname[255];
	char version[255];

private:
};


#endif // ! COMPONENTBASE