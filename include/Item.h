#ifndef __ITEM__H__
#define __ITEM__H__

#include "GameObject.h"

class Item: public GameObject {
public:
	Item(const std::string& id_, const std::string name_, const std::string& desc_): GameObject(id_, name_, desc_) {}

	virtual bool isItem() const { return true; }
	virtual bool canBeTaken() const { return true; }

};

#endif  //!__ITEM__H__
