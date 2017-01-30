// OOP244 Workshop ??: ??????????
// File ???????
// Version 1.0
// Date ???????????
// Author ?????????
// Description
// ?????????????????????
//
//
// Revision History
///////////////////////////////////////////////////////////
// Name     Date    Reason
//
///////////////////////////////////////////////////////////


// TODO: header safeguards
#ifndef _SICT_KINGDOM_H
#define _SICT_KINGDOM_H
// TODO: westeros namespace
namespace westeros{
// TODO: define the class Kingdom in the westeros namespace
class Kingdom{
		public:
			char m_name[32];
			int m_population;
	};
// TODO: add the declaration for the function display(...),
//         also in the westeros namespace
void display(Kingdom& kd);
void display(Kingdom Kingdoms[], int num);
void display(Kingdom Kingdoms[], int num, int min);
void display(Kingdom Kingdoms[], int num,const char* name);
}
#endif
