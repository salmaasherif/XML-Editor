/****************salma sherif's part *****************/


#include <bits/stdc++.h>
#include "xmltree.h"
#include "format.h"

std::string Minify2(std::ifstream& input, std::ofstream& output) {
    std::string buffer;
    char x, z; int i = 0;
    if (!input) { std::cout << "No file chosen."; return "Error."; }
    while (input.good()) {
        x = input.get();
        z = input.peek();
        if (x == '>')
        {
            buffer += x;
            while (z == '\n' || z == '\t' || z == ' ' || z == '\r\t') {
                z = input.get();
                z = input.peek();
            }
        }
        else if (z == '<' && (x == '\n' || x == '\t' || x == ' ' || x == '\r\t')) {
            x = input.get();
            buffer += z;
        }
        else if ((x == '\n' || x == '\t' || x == ' ') && (z == '\t' || z == ' ')) { x = input.get(); }
        else { if (input.good()) buffer += x; }
    }
    return buffer;
}



std::string Parser(std::ifstream& inputFile, std::ofstream& outputFile) {
    std::string buffer;
    std::string line;
    std::string parsedResult;
    int start, end;



    while (getline(inputFile, line)) {
        for (int v = 0; v < line.length(); v++)
        {
            if (line[v] == '<')
            {
                start = v;
                for (v; v < line.length(); v++)
                {
                    if (line[v] == '>')
                    {
                        end = v;
                        break;
                    }
                    if (v == line.length() - 1)
                    {
                        end = v;
                    }
                }
            }
            else
            {
                start = v;
                for (v; v < line.length(); v++)
                {
                    if (line[v] == '<')
                    {
                        end = v - 1;
                        v--;
                        break;
                    }
                    else
                    {
                        end = v;
                    }
                }
            }
            parsedResult = line.substr(start, (end - start + 1));
            if (parsedResult[0] != '<')
                for (int i = 0; i < parsedResult.length(); i++)
                {
                    if (parsedResult[i] == '"')
                        parsedResult.replace(i, 1, " ");
                }
            if (parsedResult[0] != ' ' || parsedResult[1] != ' ' || parsedResult[2] != ' ')
            {
                outputFile << parsedResult << std::endl; buffer += parsedResult + '\n';
            }
        }
    }
    return buffer;
    inputFile.close();
    outputFile.close();
}



std::string Format(XML_tree* tree, std::ifstream& input, std::ofstream& output) {
    std::string b;
    std::string line;
    bool begin_tag = false;
    Node* newNode = nullptr;
    std::stack<Node*> stk;
    int indent = 0, nextindent = 0;



    while (getline(input, line)) {



        if (line[0] == '<' && (line[1] == '!' || line[1] == '?')) {
            continue;
        }
        else if (line[0] == '<' && line[1] != '/')
        {
            indent = nextindent++;
            int end = 0;
            for (int i = 1; i < line.length(); i++)
            {
                end = i;
                if (line[i] == '\n') {
                    break;
                }
            }
            std::string tag_Name = line.substr(1, end - 1);
            newNode = new Node(tag_Name);
            if (stk.size() == 0)
            {
                tree->add_root(newNode);
            }
            else {
                tree->add_child(stk.top(), newNode);
            }
            stk.push(newNode);



            for (int i = 0; i < indent; i++)
            {
                b += '\t';
            }
            b += '<' + newNode->Tag_Name + '>';
        }
        else if (line[0] == '<' && line[1] == '/')
        {
            std::string top = stk.top()->Tag_Name;
            indent = nextindent--;



            for (int i = 0; i < indent - 1; i++)
            {
                b += '\t';
            }

            b += "</" + top + '>';
            stk.pop();
        }
        else {
            indent = nextindent;
            std::string txt = "";
            int end = 0;
            for (int i = 0; i < line.length(); i++)
            {
                end = i;
                txt += txt;
                if (line[i] == '\n') {
                    break;
                }
            }
            std::string data = line.substr(0, end + 1);
            tree->add_data(newNode, data);

            for (int i = 0; i < indent; i++)
            {
                b += '\t';
            }
            b += newNode->Tag_value;
            b += '\n';
        }
        if (line[line.size() - 1] == '>') { b += '\n'; }
    }
    return b;
}
