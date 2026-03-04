#include <Arduino.h>
#include <Bounce2.h>

#ifndef UTILS_H
#define UTILS_H

Bounce Taster;

class Utils
{
private:
    bool wStartStop = false;
    bool wNotAus = false;

    int StartStop = 0;
    int Buzzer = 0;

public:
    void SetNotAus(int TasterNotAus)
    {
        wNotAus = TasterNotAus;
    }

    uint8_t GetNotAus()
    {
        return wNotAus;
    }

    void SetStartStop(int TasterStartStop)
    {
        wStartStop = TasterStartStop;
    }

    uint8_t GetStartStop()
    {
        return wStartStop;
    }
    
    Utils()
    {
    }

    Utils(int StartStop, int Buzzer)
    {
        this->StartStop = StartStop;
        this->Buzzer = Buzzer;

        pinMode(this->StartStop, INPUT);

        Taster.attach(StartStop);
        Taster.interval(30);
    }

    void ActionsWrite()
    {
        Taster.update();
        if (Taster.rose())
        {
            wStartStop = !wStartStop;
        }
    }
    void ActionsRead()
    {
        if (wNotAus == true)
        {
            digitalWrite(Buzzer, HIGH);
        }
        else
        {
            digitalWrite(Buzzer, LOW);
        }
    }
};

#endif UTILS_H