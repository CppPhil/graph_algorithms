#include "heuristic.hpp"
#include <cstddef>       // std::size_t
#include <cstdint>       // SIZE_MAX
#include <unordered_map> // std::unordered_map

namespace gp {
namespace romania {
const std::unordered_map<City, std::size_t> straightLineToBucharestMap(
    {{City::Arad, 366},    {City::Bucharest, 0},   {City::Craiova, 160},
     {City::Dobreta, 242}, {City::Eforie, 161},    {City::Fagaras, 176},
     {City::Giurgiu, 77},  {City::Hirsova, 151},   {City::Iasi, 226},
     {City::Lugoj, 244},   {City::Mehadia, 241},   {City::Neamt, 234},
     {City::Oradea, 380},  {City::Pitesti, 100},   {City::RimnicuVilcea, 193},
     {City::Sibiu, 253},   {City::Timisoara, 329}, {City::Urziceni, 80},
     {City::Vaslui, 199},  {City::Zerind, 374}});

std::size_t heuristic(City city)
{
    const auto it{straightLineToBucharestMap.find(city)};

    if (it == straightLineToBucharestMap.end()) { return SIZE_MAX; }

    return it->second;
}
} // namespace romania
} // namespace gp
