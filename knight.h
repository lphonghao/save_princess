#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);

void ev_1to5(int event_code, int event_order, int & HP, int & level, int & phoenixdown, int & rescue);
void ev_6(int event_order, int & HP, int & level, int & remedy, int  & rescue);
void ev_7(int event_order, int & HP, int & level, int & maidenkiss, int  & rescue);
void ev_11(int & HP, int & level, int & phoenixdown);
void ev_12(int & HP);
void ev_99(int & level, int & rescue);
void ev_13(int event_code, string file_mush_ghost, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue)  ;
void ev_19(bool & metAsclepius, string file_asclepius_pack, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown);
void ev_18(bool & metMerlin, string file_merlin_pack, int & HP);
#endif // __KNIGHT_H__