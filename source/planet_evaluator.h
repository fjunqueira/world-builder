#ifndef WORLD_BUILDER_PLANET_EVALUATOR_H
#define WORLD_BUILDER_PLANET_EVALUATOR_H

#include "challenge.h"
#include "geodesic_sphere.h"
#include "world_builder.h"

class PlanetEvaluator
{
  public:
    void Evaluate(const GeodesicSphere& sphere, const WorldBuilder& builder);

    bool Succeeds(const Challenge& challenge) const;

    const float& grass_percentage() const;
    const float& water_percentage() const;
    const float& sand_percentage() const;
    const float& vegetation_percentage() const;

  private:
    float grass_percentage_;
    float water_percentage_;
    float sand_percentage_;
    float vegetation_percentage_;
};

#endif // WORLD_BUILDER_PLANET_EVALUATOR_H