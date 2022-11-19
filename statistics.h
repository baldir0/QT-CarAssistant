#ifndef STATISTICS_H
#define STATISTICS_H


class Statistics
{
    public:
        Statistics();

        double calculateAvgConsumption();
        double calculateAvgDistance();
    private:
        double usedFuel;
        double fuel;
};

#endif // STATISTICS_H
