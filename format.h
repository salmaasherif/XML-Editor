/****************salma sherif's part *****************/


#ifndef FORMAT_H
#define FORMAT_H
#include <bits/stdc++.h>
#include"xmltree.h"

std::string Minify2(std::ifstream& input, std::ofstream& output);
std::string Parser(std::ifstream& inputFile, std::ofstream& outputFile);
std::string Format(XML_tree* tree, std::ifstream& input, std::ofstream& output);
#endif // FORMAT_H
