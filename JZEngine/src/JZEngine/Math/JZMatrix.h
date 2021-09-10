#pragma once

namespace JZEngine
{
	template <typename TYPE, size_t ROW, size_t COLUMN>
	struct Matrix
	{
		TYPE data_[COLUMN][ROW]{ 0 };

		TYPE* operator[](unsigned int column)
		{
			return data_[column];
		}

		template <typename OStream>
		friend OStream& operator<<(OStream& os, const Matrix& matrix)
		{
			os << "\n";
			for (int c = 0; c < COLUMN; ++c)
			{
				os << "| ";
				for (int r = 0; r < ROW; ++r)
				{
					os << matrix.data_[c][r] << " ";
				}
				os << "|\n";
			}
			return os;
		}
	};
}