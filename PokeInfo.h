class PokeInfo
{
public:
	char pad_0000[170]; //0x0000
	uint8_t m_pokename_leanght; //0x00AA
	char pad_00AB[1]; //0x00AB
	char m_pokename[15]; //0x00AC
	char pad_00BB[213]; //0x00BB
}; //Size: 0x0190