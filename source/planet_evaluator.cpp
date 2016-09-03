#include "planet_evaluator.h"

void PlanetEvaluator::Evaluate(const GeodesicSphere& sphere, const WorldBuilder& builder)
{
    float total_water = 0;
    float total_grass = 0;
    float total_sand = 0;
    float total_vegetation = 0;

    for (size_t i = 0; i < sphere.diffuse().size(); i += 3)
    {
        auto object = sphere.diffuse().at(i);

        if (object == glm::vec3(0.45f, 0.73f, 0.98))
            total_water++;

        if (object == glm::vec3(0.2f, 0.5f, 0.0f))
            total_grass++;

        if (object == glm::vec3(0.93f, 0.86f, 0.43f))
            total_sand++;
    }

    float total = (float)sphere.diffuse().size() / 3;

    this->grass_percentage_ = (total_grass * 100) / total;
    this->water_percentage_ = (total_water * 100) / total;
    this->sand_percentage_ = (total_sand * 100) / total;
    this->vegetation_percentage_ = (builder.occupied_faces().size() * 100) / total;
}

bool PlanetEvaluator::Succeeds(const Challenge& challenge) const
{
    return abs(this->grass_percentage_ - challenge.grass_percentage_) <= challenge.tolerable_error_ &&
           abs(this->water_percentage_ - challenge.water_percentage_) <= challenge.tolerable_error_ &&
           abs(this->sand_percentage_ - challenge.sand_percentage_) <= challenge.tolerable_error_ &&
           abs(this->vegetation_percentage_ - challenge.vegetation_percentage_) <= challenge.tolerable_error_;
}

const float& PlanetEvaluator::grass_percentage() const { return this->grass_percentage_; }
const float& PlanetEvaluator::water_percentage() const { return this->water_percentage_; }
const float& PlanetEvaluator::sand_percentage() const { return this->sand_percentage_; }
const float& PlanetEvaluator::vegetation_percentage() const { return this->vegetation_percentage_; }