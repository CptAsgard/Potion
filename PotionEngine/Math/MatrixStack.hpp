#pragma once

#include <vector>

#include "Matrix.hpp"

namespace Potion
{
	class MatrixStack
	{
	public:
		// Pushes a new element to the top of the stack
		void Push( const Matrix& matrix );

		// Pops the top element of the stack
		void Pop();

		// Clears the stack completely
		void Clear();

		// Gets the combination of all matrices in the stack
		Matrix GetAll() const;

		// How many matrices have been pushed to the stack
		size_t Count() const;

	private:
		std::vector< Matrix > matrices;

	};
}