#ifndef __SINGLETON__H__
#define __SINGLETON__H__

template <typename T>
class Singleton {
public:
	static T& Instance() {
		static T instance{};
		return instance;
	}

	virtual ~Singleton() = default;
protected:
	Singleton() = default;
};

#endif  //!__SINGLETON__H__
