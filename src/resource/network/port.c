/******************************************************
* Author       : fengzhimin
* Create       : 2016-11-11 09:04
* Last modified: 2016-11-11 09:06
* Email        : 374648064@qq.com
* Filename     : port.c
* Description  : 
******************************************************/

#include "resource/network/port.h"
#include "common/strOper.h"
#include "common/fileOper.h"

char port_symbol[][20] = {"Listen", "port"};

int GetPort_SymbolNum()
{
	return sizeof(port_symbol)/sizeof(port_symbol[0]);
}
