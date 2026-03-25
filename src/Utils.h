#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <Bounce2.h>

class Utils
{
private:
    bool wStartStop = false;
    bool wNotAus = false;
    int StartStop = 0;
    int Buzzer = 0;
    Bounce Taster;

public:
    Utils() {}

    Utils(int StartStop, int Buzzer)
    {
        this->StartStop = StartStop;
        this->Buzzer = Buzzer;
    }

    // FIX: Hardware setup moved here
    void begin() 
    {
        pinMode(this->StartStop, INPUT); // Expects external pulldown resistor
        pinMode(this->Buzzer, OUTPUT);

        Taster.attach(this->StartStop);
        Taster.interval(30);
    }

    void SetNotAus(int TasterNotAus) { wNotAus = TasterNotAus; }
    uint8_t GetNotAus() { return wNotAus; }

    void SetStartStop(int TasterStartStop) { wStartStop = TasterStartStop; }
    uint8_t GetStartStop() { return wStartStop; }

    void ActionsWrite()
    {
        Taster.update();
        if (Taster.rose()) // Toggle when button is pressed
        {
            wStartStop = !wStartStop;
        }
    }

    void ActionsRead()
    {
        if (wNotAus) {
            tone(Buzzer, 100);
        } else {
            noTone(Buzzer);
        }
    }
};

#endif // UTILS_H