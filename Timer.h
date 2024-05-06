#pragma once

#include <d3d10.h>

class Timer
{
private:
    INT64 timeStart;
    bool started;

    ID3D10Query* queryDisjoint; 
    ID3D10Query* queryStart;    
    ID3D10Query* queryEnd;    

public:
    Timer();
    ~Timer();

    bool IsStarted() { return started; }
    void Start();
    void Reset();
    INT64 ElapsedTime();
};
