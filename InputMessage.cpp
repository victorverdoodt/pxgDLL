#include "stdafx.h"
#include "inputmessage.h"
#include <Windows.h>
#include <string>

UINT8 InputMessage::getU8()
{
	UINT8 v = m_buffer[m_readPos];
	m_readPos += 1;
	return v;
}
