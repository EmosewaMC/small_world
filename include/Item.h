#pragma once

class Item : public GameObject {

	public:
		Item(const std::string & id_, const std::string name_, const std::string & desc_) : GameObject(id_, name_, desc_) {}

		virtual isItem() const { return true; }
		virtual bool canBeTaken() const { return true; }

};
