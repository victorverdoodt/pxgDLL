class MatrixArea
{
public:
	MatrixArea(uint32_t _rows, uint32_t _cols)
	{
		centerX = centerY = 0;
		rows = _rows;
		cols = _cols;

		data_ = new bool*[rows];
		for (uint32_t row = 0; row < rows; ++row)
		{
			data_[row] = new bool[cols];
			for (uint32_t col = 0; col < cols; ++col)
				data_[row][col] = 0;
		}
	}

	MatrixArea(const MatrixArea& rhs)
	{
		centerX = rhs.centerX;
		centerY = rhs.centerY;
		rows = rhs.rows;
		cols = rhs.cols;

		data_ = new bool*[rows];
		for (uint32_t row = 0; row < rows; ++row)
		{
			data_[row] = new bool[cols];

			for (uint32_t col = 0; col < cols; ++col)
				data_[row][col] = rhs.data_[row][col];
		}
	}

	virtual ~MatrixArea()
	{
		for (uint32_t row = 0; row < rows; ++row)
			delete[] data_[row];

		delete[] data_;
	}

	void setValue(uint32_t row, uint32_t col, bool value) const { data_[row][col] = value; }
	bool getValue(uint32_t row, uint32_t col) const { return data_[row][col]; }

	void setCenter(uint16_t y, uint16_t x) { centerX = x; centerY = y; }
	void getCenter(uint16_t& y, uint16_t& x) const { x = centerX; y = centerY; }

	size_t getRows() const { return rows; }
	size_t getCols() const { return cols; }

	inline const bool* operator[](uint32_t i) const { return data_[i]; }
	inline bool* operator[](uint32_t i) { return data_[i]; }

protected:
	uint16_t centerX, centerY;
	uint32_t rows, cols;
	bool** data_;
};