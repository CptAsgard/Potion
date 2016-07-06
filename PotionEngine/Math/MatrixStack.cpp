#include "MatrixStack.hpp"

namespace Potion
{
	void MatrixStack::Push( const Matrix & matrix )
	{
		matrices.push_back( matrix );
	}

	void MatrixStack::Pop()
	{
		matrices.pop_back();
	}

	void MatrixStack::Clear()
	{
		matrices.clear();
	}

	Matrix MatrixStack::GetAll() const
	{
		Matrix retVal;

		for( const auto& it : matrices )
		{
			retVal = retVal * it;
		}

		return retVal;
	}

	size_t MatrixStack::Count() const
	{
		return matrices.size();
	}
}