#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(string time, int id, int extra)
{
	setTime(time);
	ID = id;
	ExtraCost = extra;
}

void PromotionEvent::setTime(string t)
{
	int idx = 0;
	while (t[idx] != ':') idx++;
	Time = stoi(t.substr(0, idx)) * 24 + stoi(t.substr(idx + 1));
}

int PromotionEvent::getTime() const
{
	return Time;
}


void PromotionEvent::Excute()
{
	// normallist.promote(ID, ExtraCost);
}
