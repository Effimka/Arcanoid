#pragma once
#include "Bonus.h"

class BonusHandler {
public:

    static BonusHandler& instance() {
        static BonusHandler* instance = new BonusHandler();
        return *instance;
    }

    void init();
    void update(float elapsed, std::vector<Ball>& balls, Carriage& car);
    void add_bonus(const Vect& pos, float radius, float init_speed);
    int get_size() const;
    std::vector<std::unique_ptr<Bonus>> bonuses;
    BonusHandler(BonusHandler& other) = delete;
    void operator=(const BonusHandler&) = delete;

private:
    BonusHandler() {}
    

};



