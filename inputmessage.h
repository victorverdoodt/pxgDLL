class InputMessage
{
public:
	UINT8 getU8();
	UINT16 getU16();
	UINT32 getU32();
	UINT64 getU64();
	//std::string getString();
	double getDouble();

private:
	UINT16  m_headerPos;
	UINT16 m_readPos;
	UINT16 m_messageSize;
	UINT8 m_buffer[65536];
};