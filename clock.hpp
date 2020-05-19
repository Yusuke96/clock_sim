#include "main.hpp"

class Clock{
private:
    double time=0.0;
public:
    Clock();
    ~Clock();
    double GetTime();
    void Advance();
}
