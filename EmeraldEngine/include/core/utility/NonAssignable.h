#pragma once

namespace EmeraldEngine {
	template<typename Type>
	class NonAssignable {
	private:
		Type* nonAssignableObject;

	public:
		NonAssignable& operator=(const NonAssignable&) = delete;

		
		NonAssignable(Type* nonAssignableObject) : nonAssignableObject(nonAssignableObject) {}

		Type* operator->() {
			return nonAssignableObject;
		}
	};
}
