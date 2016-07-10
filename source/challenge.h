#ifndef WORLD_BUILDER_CHALLENGE_H
#define WORLD_BUILDER_CHALLENGE_H

#include <string>

struct Challenge
{
    Challenge() {}
    Challenge(const std::string& description, const float& grass_percentage, const float& water_percentage,
              const float& sand_percentage, const float& vegetation_percentage, const float& tolerable_error)
        : description_(description), grass_percentage_(grass_percentage), water_percentage_(water_percentage),
          sand_percentage_(sand_percentage), vegetation_percentage_(vegetation_percentage),
          tolerable_error_(tolerable_error)
    {
    }

    std::string description_;
    float grass_percentage_;
    float water_percentage_;
    float sand_percentage_;
    float vegetation_percentage_;
    float tolerable_error_;
};

#endif // WORLD_BUILDER_CHALLENGE_H