#include "colors.h"
#include <vector>
const Color darkGrey = {40, 45, 55, 255};  // Slightly lighter
const Color green = {80, 255, 80, 255};   // Brighter green
const Color red = {255, 50, 50, 255};     // Brighter red
const Color orange = {255, 165, 50, 255}; // Brighter orange
const Color yellow = {255, 255, 80, 255}; // Brighter yellow
const Color purple = {190, 50, 255, 255}; // More vibrant purple
const Color cyan = {50, 255, 255, 255};   // More vibrant cyan
const Color blue = {50, 90, 255, 255};    // More vibrant blue



std:: vector<Color> Getceilcolor() {
    return {darkGrey , green , red , orange , yellow , purple , cyan , blue} ;
}