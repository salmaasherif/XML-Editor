#ifndef XMLTOJSON_H
#define XMLTOJSON_H
#include <bits/stdc++.h>
#include "xmltree.h"
/***************************************************************
******************Function Prototypes ************************
****************************************************************/


void tree(XML_tree* tree, std::ifstream& input);

std::string Minify2(std::ifstream& input, std::ofstream& output);

std::string Parser(std::ifstream& inputFile, std::ofstream& outputFile);

bool Node_list(Node* node);

void indentation(int level);

std::string XML_to_json(Node* root);



#endif // XMLTOJSON_H
