#include "compression.h"

std::string buffer;

struct Node
{
    char data;
    int frequency;
    Node *left, *right;
};


Node* root ;
Node* NewNode(char d, int freq, Node* left, Node* right)//create new node
{
    Node* node = new Node();

    node->data = d;
    node->frequency = freq;
    node->left = left;
    node->right = right;

    return node;
}

struct compare
{
    bool operator()(Node* l, Node* r)
    {
        // high priority is low frequency
        return l->frequency > r->frequency;
    }
};


// traverse the Huffman Tree and store Huffman codes.
void compress(Node* root, std::string str,
        std::unordered_map<char, std::string> &huffman)
{
    if (!root)
        return;

    // if it is a leaf node
    if (!root->left && !root->right)
    {
        huffman[root->data] = str;
    }

    compress(root->left, str + "0", huffman);
    compress(root->right, str + "1", huffman);
}

// traverse the Huffman Tree and decode the encoded string
std::string decompress(Node* root, int &i, std::string str)
{
    std::string DecompressedOutput = "";
    if (!root) {//if equal null
        return DecompressedOutput;
    }

    // found a leaf node
    if (!root->left && !root->right)
    {
        std::cout<<root->data;
        DecompressedOutput+=root->data;
        return DecompressedOutput;

    }

    i++;

    if (str[i] =='0')
        DecompressedOutput+=decompress(root->left, i, str);
    else
        DecompressedOutput+=decompress(root->right, i, str);
}

// Builds Huffman Tree and compress input into string of zeros and ones
std::string Compress(std::string text)
{
    buffer="";
    std::string OutputCompressed;
    int j=0;
    int bits=0;
    // calculate the frequency of each character in the input string and store it in a map
    std::unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }

    // Create a priority queue to store live nodes of Huffman tree;
    std::priority_queue<Node*, std::vector<Node*>, compare> pq;

    // Create a leaf node for each character and add it to the priority queue.
    for (auto pair: freq) {
        pq.push(NewNode(pair.first, pair.second, nullptr, nullptr));
    }

    // do till there is more than one node in the queue
    while (pq.size() != 1)
    {
        // Remove the two nodes of highest priority
        // (lowest frequency) from the queue
        Node *l = pq.top();
        pq.pop();
        Node *r = pq.top();
        pq.pop();

        /* Create a new internal node with these two nodes as children and with frequency equal to the sum of the two nodes' frequencies.
         * Add the new node to the priority queue.*/
        int sum = l->frequency + r->frequency;
        pq.push(NewNode('\0', sum, l, r));
    }

    //stores pointer to root of Huffman Tree
    root = pq.top();

    // traverse the Huffman Tree and store Huffman Codes in a map. Also prints them
    std::unordered_map<char, std::string> huffman;
    compress(root, "", huffman);

    std::cout << "Huffman codes are :\n" << '\n';
    for (auto pair: huffman)
    {
        std::cout << pair.first << " " << pair.second << '\n';
    }


    std::string str = "";
    for (char ch: text)
    {
        str += huffman[ch];
    }

    //std::cout<<str<<"\n";

    unsigned long long remainder = (str.length() ) % 8;//remainder of zeros and ones that doesn't complete 8 bits in the end of file
    //we have to handle remainder to prevent data loss
    for (int i=0; i<str.length()-remainder; i++){//dealing with the whole file without remainder first
            /*if (j==0){
                bits<<1;
            }*/
            bits=bits<<1;//to make place for new bit
            if (str[i]=='1')
            {
                bits=bits|1;
            }

            j ++;// increament counter with every bit in the string
            if (j==8)//reached 7 bits, store one char in the compressed XML file
            {
                OutputCompressed+=bits;//store encoded character
                bits=0;//clear char
                j=0;//clear counter

            }
        }
    OutputCompressed+="%%";//special character to indicate the end of the string without the remainder
        for (int i=str.length()-remainder;i<str.length();i++){//adding the remainder
            OutputCompressed+=str[i];
        }


    buffer=OutputCompressed;
    return OutputCompressed;
}
//decode the string
std::string Decompress(){

    //now the string of characters compressed is in buffer
    //change the buffer string of characters into zeros and ones to decode
    std::string strr;
    for (int i=0; i<buffer.length(); i++)
    {
        if (buffer[i]=='%'&&buffer[i+1]=='%'){//then after %% there is the remainder of zeros and ones
                    i=i+2;
                    while(i<buffer.length())
                    {
                        strr+=buffer[i];
                        i++;
                    }
                }
                else
                {
                    int z=0;//counter for 8 bits
                    while (z!=8)
                    {
                        if((buffer[i]&0x80)==0x80)//if the MSB in char is 1 then put one in string
                        {
                            strr+='1';
                        }
                        else//otherwise it is a zero
                            strr+='0';
                        buffer[i]<<=1;//shift to get the new bit as the MSB
                        z++;//increment counter
                        //cout<<"string compressed"<<stringcompressed;
                    }
                }
    }

    // traverse the Huffman Tree and decode the encoded string
    int index = -1;

    std::string DecompressedOutput="";
    while (index < (int)strr.size() - 2)
    {
        DecompressedOutput+=decompress(root, index, strr);
    }

    return DecompressedOutput;
}
//function to return the size of each file given the file as a string
int size_of_file(std::string x){
    int i=0;
    for ( i=0;i<x.length();i++){

    }
    return i;
}
