#ifndef __INDEX__H__
#define __INDEX__H__

#include <string>
#include <memory>

// look up objects by their ID.  This is a templated class, we specify the type - in this 
// case, a Room, Player, or Item

template <typename T>
class Index {
private:
	std::map<std::string, std::shared_ptr<T>> index;
public:
	std::shared_ptr<T> get_object(const std::string& id) {
		auto it = index.find(id);
		return it == index.end() ? nullptr : it->second;
	}

	void add_object(std::shared_ptr<T> object) { index[object->GetId()] = object; }

	void clear() { index.clear(); }
};

#endif  //!__INDEX__H__
