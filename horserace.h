#ifndef HORSERACE_H
#define HORSERACE_H

class HorseRace
{
public:
    HorseRace();
    void RunHorseRace();

private:
    int RandomHorseWinner();
    void race();
    void instructions();
    void wager();
    void HorseRaceSelection();
};

#endif