// this is the Shell-Metzner sort an adaptation of the Shell sort by Marlene Metzner
// the fastest sort on the planet
#include "CLEditSM.h"
CLEditSM::CLEditSM()
{
    //ctor
}

CLEditSM::~CLEditSM()
{
    //dtor
}
void CLEditSM::SortSM()
{

    rowcnt--; // the number of elements in the array offset by one

    m = rowcnt;

    while (m > 0)
    {
        m /= 2;
        k = rowcnt - m;
        j = 0;
        do
        {
            Loop();
        }
        while (j <= k);
    }

}
void CLEditSM::Loop()
{

    i = j;

    do
    {
        LoopLoop();
    }
    while (i >= 0);

    j++;

}
void CLEditSM::LoopLoop()
{

    l = i + m;


    if (inputfile[i].sortarea > inputfile[l].sortarea)
    {
        Swap();
        i -= m;
    }
    else
    {
        i = -1;
    }

}
void CLEditSM::Swap()
{

    temp = inputfile[i];

    inputfile[i] = inputfile[l];

    inputfile[l] = temp;

}

