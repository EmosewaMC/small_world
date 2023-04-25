#ifndef __PICOJSONUTILS__H__
#define __PICOJSONUTILS__H__

#include "picojson.h"

namespace PicoJsonUtils {

	/**
	 * @brief Checks if the obj has a field with the given name
	 * 
	 * @tparam T The type to check for
	 * @param obj The picojson object to check
	 * @param fieldname The name of the field to check for
	 * @return true if the field exists and is of type T, false otherwise
	 */
	template<typename T> bool HasField(const picojson::object& obj, const std::string& fieldname) {
		if (obj.find(fieldname) == obj.end()) return false;
		if (!obj.find(fieldname)->second.is<T>()) return false;
		return true;
	}

	/**
	 * @brief Gets an attribute by T type and returns a default type should it not exist.
	 */
	template<typename TypeToGet>
	TypeToGet GetAttribute(picojson::object& obj, const std::string& attributeName) {
		return HasField<TypeToGet>(obj, attributeName) ? obj.find(attributeName)->second.get<TypeToGet>() : TypeToGet();
	}
}

#endif  //!__PICOJSONUTILS__H__
