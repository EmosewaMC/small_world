#ifndef __PLAYER__H__
#define __PLAYER__H__

#include <string>

#include "Character.h"

class Player : public Character {
public:
	Player(const std::string& id, const std::string& name, const std::string& desc);
};

#endif  //!__PLAYER__H__
