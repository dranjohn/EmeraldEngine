#pragma once

namespace EmeraldEngine {
	class Texture {
	protected:
		Texture() = default;

	public:
		virtual void use(unsigned int slot) = 0;
	};
}
