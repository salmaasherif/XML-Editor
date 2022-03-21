/****************salma sherif's part *****************/

#include "minify.h"

std::string Minify(std::ifstream& input) {
    std::string output;
    std::string buffer;
    char x,z;
    if (!input) { std::cout << "No file chosen."; return output; }
    while (input.good()) {
        x = input.get();
        z = input.peek();
        if (x == '>')
        {
            output += x;
            while (z == '\n' || z == '\t' || z == ' ' || z == '\r\t') {
                z = input.get();
                z = input.peek();
            }
        }
        else if (z == '<' && (x == '\n' || x == '\t' || x == ' ' || x == '\r\t')) {
            x = input.get();
            output += z;
        }
        else if ((x == '\n' || x == '\t' || x == ' ') && (z == '\t' || z == ' ')) { x = input.get(); }
        else { if (input.good()) output += x; }
    }
}
