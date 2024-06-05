#include "BonusHandler.h"

void BonusHandler::init()
{
    bonuses.clear();
}

void BonusHandler::update(float elapsed, std::vector<Ball>& balls, Carriage& car)
{
    int sz = bonuses.size();
    for (int i = 0; i < sz; ++i)
    {
        bonuses[i]->update(elapsed);

        if (bonuses[i]->can_use)
            bonuses[i]->bonus->execute(balls, car);


        if (bonuses[i]->dead)
        {
            auto it = bonuses.begin() + i;
            bonuses.erase(it);
            --i;
            sz = bonuses.size();
        }

    }
}

void BonusHandler::add_bonus(const Vect& pos, float radius, float init_speed)
{
    bonuses.push_back(std::make_unique<Bonus>(pos, radius, init_speed));
}

int BonusHandler::get_size() const
{
    return bonuses.size();
}
