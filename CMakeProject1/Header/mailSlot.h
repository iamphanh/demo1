#ifndef MAIL_SLOT_H
#define MAIL_SLOT_H

#include <tchar.h>
#include <strsafe.h>
#include "myTime.h"
#include "network.h"

class mailSlot : public network {
private:
	static HANDLE hSlot;
	static const LPCTSTR slotName;

public:
	mailSlot();
	~mailSlot();
	HANDLE getSlot() const;
	//HANDLE setSlot(HANDLE hSlot) const;
	BOOL createHandle();
	BOOL writeHandle(LPCTSTR msg);
	int creatFmail();
	BOOL readHandle();
};

#endif // MAIL_SLOT_H