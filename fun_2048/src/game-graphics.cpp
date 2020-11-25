#include "game-graphics.hpp"
#include <sstream>


namespace Game
{
    namespace Graphics
    {
        std::string asciiArt2048() {
            // TODO: this give a good title card
            constexpr auto title_card_2048 = R"(2048)";
            std::ostringstream title_card_richtext;
            // TODO: add the color and fonts
            title_card_richtext << title_card_2048;
            title_card_richtext << "\n\n\n";
            // convert to string class
            return title_card_richtext.str();
        }
    } // namespace Graphics
    
} // namespace Game
