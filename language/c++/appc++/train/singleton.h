#ifndef __SINGLETON_H
#define __SINGLETON_H

#include <stdexcept>

template<typename T>
class Singleton
{
public:
	template<typename... Args>
	static void CreateInstance(Args&&... args) {
		if (pInstance_ == nullptr)
			pInstance_ = new T(std::forward<Args>(args)...);
	}

	static T *GetInstance() {
		if (pInstance_ == nullptr)
			throw std::logic_error("logical error");

		return pInstance_;
	}

	static void DestroyInstance() {
		delete pInstance_;
		pInstance_ = nullptr;
	}

private:
	static T *pInstance_;
};

template<typename T>
T * Singleton<T>::pInstance_ = nullptr;

#endif
