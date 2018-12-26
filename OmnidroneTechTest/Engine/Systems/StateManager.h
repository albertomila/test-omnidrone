#pragma once

#include <Engine/IUpdatable.h>

#include <vector>
#include <memory>

class IState;

class CStateManagerBase : public IUpdatable
{
public:
	CStateManagerBase();

	template<class T>
	void RegisterState();

	void Init() override;
	void Update() override;
	void Shutdown() override;

private:
	std::vector<std::unique_ptr<IState>> mStates;
	std::size_t mCurrentStateIndex;
};


template<class T>
class CStateManager : public CStateManagerBase
{
public:
	CStateManager();
};

template<class T>
CStateManager<T>::CStateManager()
{
	static_assert(std::is_base_of<IState, T>::value, "T must derive from IState");
}