#include "xmltojson.h"

void tree(XML_tree* tree, std::ifstream& input) {

    int Node_level = 1;
    std::string line;

    bool begin_tag = false;

    Node* newNode = nullptr;
    std::stack<Node*> stk;

    while (getline(input, line)) {

        if (line[0] == '<' && (line[1] == '!' || line[1] == '?')) {
            continue;
        }
        else if (line[0] == '<' && line[1] != '/')
        {
            int end;
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
                tree->add_level(newNode,Node_level);
                Node_level++;
            }
            else {
                tree->add_child(stk.top(), newNode);
                tree->add_level(newNode, Node_level);
                Node_level++;
            }
            stk.push(newNode);
        }
        else if (line[0] == '<' && line[1] == '/')
        {
            //string top = stk.top()->Tag_Name;
            stk.pop();
            Node_level--;
            //cout << "pop" << top << endl;
        }
        else {
            //string txt="";
            int end = 0;
            for (int i = 0; i < line.length(); i++)
            {
                end = i;
                //txt += txt;
                if (line[i] == '\n') {
                    break;
                }
            }
            std::string data = line.substr(0, end+1);
            tree->add_data(newNode, data);
            //Node_level++;
            //cout << tree->get_data(newNode)<<endl;
        }

    }

}






//true if this node is part of a list
bool Node_list(Node* node) {
    bool equal=true;
    if (node->children.size() == 1)
    {
        return false;
    }
    if (node->children.size() != 0)
    {
        for (int i = 0; i < node->children.size() - 1; i++) {
            if (node->children[i]->Tag_Name != node->children[i + 1]->Tag_Name) {
                equal = false;
            }
        }
        return equal;
    }
    else {
        return false;
    }


}

std::string output5;

//std::ofstream output("json.txt");
void indentation(int level)
{
    for (int i = 0; i < level; i++) {
        output5 += "    ";
    }
}



std::stack<Node*> stack_for_list;
std::stack<int> index;

std::string  XML_to_json(Node* root) {
    //Not List and have children
    if (!Node_list(root->parent) && root->children.size() != 0) {

        indentation(root->level);
        output5 += "\"";
        output5 += root->Tag_Name ;
        output5 +="\":" ;
        output5 +="{" ;
        output5 +="\r\n";
        for (int i = 0; i < root->children.size(); i++) {
            XML_to_json(root->children[i]);
            if (i < root->children.size() - 1) {
                output5 += ',' ;
                output5 += "\r\n";
            }
        }
        output5 +="\r\n";
        indentation(root->level);
        output5 += "}" ;

    }//Not list and leaf Node
    else if (!Node_list(root->parent) && root->children.size() == 0) {
        indentation(root->level);
        output5 += "\"" ;
                output5 +=root->Tag_Name ;
                output5 +="\":";
        if (isdigit(root->Tag_value[0])) {
            output5+= root->Tag_value ;
        }
        else {
            output5 += "\"" ;
                    output5 +=root->Tag_value ;
                    output5 +="\"";
        }
    }//List and have children
    else if (Node_list(root->parent) && root->children.size() != 0) {
        int size_of_list = root->parent->children.size();

            if (stack_for_list.empty()) {
                indentation(root->level);
                output5 += "\"" ;
                output5 +=root->Tag_Name;
                output5 += "\":" ;
                output5 +="[" ;
                output5 += "\r\n";
                indentation(root->level);
                output5 += "{" ;
                output5 += "\r\n";

                stack_for_list.push(root);
                index.push(1);
                int index2 = index.top();
                index2++;
                index.pop();
                index.push(index2);
                for (int i = 0; i < root->children.size(); i++) {
                    XML_to_json(root->children[i]);
                    if (i < root->children.size() - 1) {
                        output5 += ',' ;
                        output5 += "\r\n";
                    }
                }
                output5 += "\r\n";
                indentation(root->level);
                output5+= "}";

            }
            else if (stack_for_list.top()->Tag_Name != root->Tag_Name) {
                indentation(root->level);
                output5 += "\"" ;
                output5 +=root->Tag_Name ;
                output5 +="\":" ;
                output5 +="[" ;
                output5 +="\r\n";
                indentation(root->level);
                output5 += "{" ;
                output5 += "\r\n";

                stack_for_list.push(root);
                index.push(1);
                int index2 = index.top();
                index2++;
                index.pop();
                index.push(index2);
                for (int i = 0; i < root->children.size(); i++) {
                    XML_to_json(root->children[i]);
                    if (i < root->children.size() - 1) {
                        output5 += ',' ;
                        output5 +="\r\n";
                    }
                }
                output5 += "\r\n";
                indentation(root->level);
                output5+= "}";
                //XML_to_json(root->children[i]);/
            }
            else if (index.top() == size_of_list) {
                indentation(root->level);
                output5 += "{" ;
                output5 += "\r\n";
                stack_for_list.pop();

                index.pop();
                for (int i = 0; i < root->children.size(); i++) {
                    XML_to_json(root->children[i]);
                    if (i < root->children.size() - 1) {
                        output5 += ',' ;
                        output5 += "\r\n";
                    }
                }
                //XML_to_json(root->children[i]);/

                output5 += "\r\n";
                indentation(root->level);
                output5+= "}";
                output5 += "\r\n";
                indentation(root->level-1);
                output5 += "  ";
                output5+= "]";
            }
            else {
                indentation(root->level);
                output5 += "{" ;
                output5 += "\r\n";
                int index2 = index.top();
                index2++;
                index.pop();
                index.push(index2);
                for (int i = 0; i < root->children.size(); i++) {
                    XML_to_json(root->children[i]);
                    if (i < root->children.size() - 1) {
                        output5 += ',' ;
                        output5 += "\r\n";
                    }
                }
                output5 += "\r\n";
                indentation(root->level);
                output5+= "}";
                //XML_to_json(root->children[i]);/
            }


    }//List and don't have children
    else {
        int size_of_list = root->parent->children.size();

        //index Calculation


            if (stack_for_list.empty()) {
                indentation(root->level);
                output5 += "\"" ;
                        output5 +=root->Tag_Name ;
                        output5 +="\":" ;
                output5 +="[" ;
                          output5 +="\r\n";
                if (isdigit(root->Tag_value[0])) {
                    indentation(root->level+1);

                    output5 += root->Tag_value ;
                }
                else {
                    indentation(root->level+1);

                    output5 += "\"" ;
                    output5 +=root->Tag_value ;
                    output5 +="\"" ;
                }


                stack_for_list.push(root);
                index.push(1);
                int index2 = index.top();
                index2++;
                index.pop();
                index.push(index2);
            }
            else if(stack_for_list.top()->Tag_Name != root->Tag_Name) {
                indentation(root->level);
                output5 += "\"" ;
                output5 +=root->Tag_Name ;
                output5 +="\":" ;
                output5 +="[" ;
                output5 +="\r\n";
                if (isdigit(root->Tag_value[0])) {
                    indentation(root->level+1);
                    output5 += root->Tag_value ;
                }
                else {
                    indentation(root->level+1);
                    output5 += "\"" ;
                            output5 +=root->Tag_value;
                            output5 += "\"" ;
                }


                stack_for_list.push(root);
                index.push(1);
                int index2 = index.top();
                index2++;
                index.pop();
                index.push(index2);
            }
            else if (index.top() == size_of_list) {
                if (isdigit(root->Tag_value[0])) {
                    indentation(root->level+1);
                    output5 += root->Tag_value ;
                }
                else {
                    indentation(root->level+1);
                    output5 += "\"" ;
                    output5 +=root->Tag_value ;
                    output5 +="\"" ;
                }

                stack_for_list.pop();
                index.pop();
                output5 += "\r\n";
                indentation(root->level);
                output5+= "]";
            }
            else {
                if (isdigit(root->Tag_value[0])) {
                    indentation(root->level+1);
                    output5 += root->Tag_value ;
                }
                else {
                    indentation(root->level+1);
                    output5 += "\"" ;
                    output5 +=root->Tag_value;
                    output5 += "\"" ;
                }

            }

        }
return output5;
    }
