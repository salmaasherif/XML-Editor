#include "graph.h"


class vertex {
public:
    int id;
    vertex* nextVertex;

public:
    vertex(int id)
    {
        this->id = id;
        this->nextVertex = nullptr;
    }

};



void Graph(std::ofstream& input,Node* root)
{
    vertex* listOfNodes[100];
    vertex* newVertex = nullptr;
    vertex* newfollower = nullptr;
    vertex* iterator = nullptr;
    int values;
    input << "digraph test{" << std::endl;


    for (int i = 0; i < root->children.size(); i++) {
        Node* r1 = root->children[i];
        for (int j = 0; j < r1->children.size(); j++)
        {
            //vertices
            if (r1->children[j]->Tag_Name == "id")
            {
                values = stoi(r1->children[j]->Tag_value);
                newVertex = new vertex(values);
                listOfNodes[values] = newVertex;
                std::cout << values << std::endl;
                //input << values <<" -> " ;

            }//followers
            if (r1->children[j]->Tag_Name == "followers")
            {
                Node* followers = r1->children[j];
                Node* follower = nullptr;
                for (int m = 0; m < followers->children.size(); m++)
                {
                    follower = followers->children[m];
                    newfollower = new vertex(stoi(follower->children[0]->Tag_value));
                    iterator = listOfNodes[values];
                    while (iterator->nextVertex != nullptr)
                    {
                        iterator = iterator->nextVertex;
                    }
                    iterator->nextVertex = newfollower;
                    std::cout << newfollower->id;
                    input << values << " -> " << newfollower->id << std::endl;
                }
               std:: cout << std::endl;

            }
        }
    }
    input << "}";
}
