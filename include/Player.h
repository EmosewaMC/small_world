#ifndef __PLAYER__H__
#define __PLAYER__H__

#include <string>
#include "Character.h"

class Player : public Character {
public:
	Player(const std::string& id_, const std::string& name_, const std::string& desc_);
};

#endif  //!__PLAYER__H__
