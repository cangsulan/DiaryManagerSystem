#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <sstream>
#include <string>

// 哈夫曼树节点
struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
    HuffmanNode(char data) : data(data), left(nullptr), right(nullptr) {}
};

// 比较哈夫曼树节点的频率，用于优先队列
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

inline HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freqMap);// 构建哈夫曼树

inline void buildHuffmanCodes(HuffmanNode* root, const string& str,
    unordered_map<char, string>& huffmanCodes);// 生成哈夫曼编码表

inline string compressData(const string& data, const unordered_map<char, string>& huffmanCodes);// 压缩数据

inline vector<unsigned char> bitStringToBytes(const string& bitString);// 将压缩后的比特流转换为字节数组

inline string MybytesToBitString(const vector<unsigned char>& bytes);// 将字节数组转换为比特流

//***
inline void compressAndStore(const string& inputFilename, const string& outputFilename);// 压缩并存储数据到文件



//下面是解压缩的函数：

// 重建哈夫曼树
inline HuffmanNode* rebuildHuffmanTree(const unordered_map<char, string>& huffmanCodes);

// 解压缩比特流
inline string decompressData(const string& bitString, HuffmanNode* root);

// 解压缩并加载数据
inline void decompressAndLoad(const string& compressedFilename, const string& outputFilename);


using namespace std;

// 构建哈夫曼树
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    // 初始化最小堆
    for (const auto& entry : freqMap) {
        minHeap.push(new HuffmanNode(entry.first, entry.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* combined = new HuffmanNode('\0', left->freq + right->freq);
        combined->left = left;
        combined->right = right;

        minHeap.push(combined);
    }

    return minHeap.top(); // 最终的哈夫曼树根节点
}

// 生成哈夫曼编码表
void buildHuffmanCodes(HuffmanNode* root, const string& str,
    unordered_map<char, string>& huffmanCodes) {
    if (!root) {
        return;
    }

    if (root->data != '\0') { // 叶子节点
        huffmanCodes[root->data] = str;
    }

    buildHuffmanCodes(root->left, str + "0", huffmanCodes);
    buildHuffmanCodes(root->right, str + "1", huffmanCodes);
}

// 压缩数据
string compressData(const string& data, const unordered_map<char, string>& huffmanCodes) {
    string compressed;
    for (char ch : data) {
        compressed += huffmanCodes.at(ch);
    }
    return compressed;
}

// 将压缩后的比特流转换为字节数组
vector<unsigned char> bitStringToBytes(const string& bitString) {
    vector<unsigned char> bytes;

    // 每8位转换为一个字节
    for (size_t i = 0; i < bitString.length(); i += 8) {
        string byteStr = bitString.substr(i, 8);
        if (byteStr.length() < 8) {
            byteStr.append(8 - byteStr.length(), '0'); // 不足8位的部分填0
        }

        unsigned char byte = static_cast<unsigned char>(bitset<8>(byteStr).to_ulong());
        bytes.push_back(byte);
    }

    return bytes;
}

// 将字节数组转换为比特流
string MybytesToBitString(const vector<unsigned char>& bytes) {
    string bitString;

    for (unsigned char byte : bytes) {
        bitString += bitset<8>(byte).to_string();
    }

    return bitString;
}

// 压缩并存储数据到文件
void compressAndStore(const string& inputFilename, const string& outputFilename) {
    // 读取原始数据
    ifstream inputFile(inputFilename, ios::binary | ios::ate);
    if (!inputFile) {
        cerr << "无法打开文件: " << inputFilename << endl;
        return;
    }

    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, ios::beg);

    vector<char> rawData(fileSize);
    inputFile.read(rawData.data(), fileSize);
    inputFile.close();

    string rawDataStr(rawData.begin(), rawData.end());

    // 统计字符频率
    unordered_map<char, int> freqMap;
    for (char ch : rawDataStr) {
        freqMap[ch]++;
    }

    // 构建哈夫曼树
    HuffmanNode* root = buildHuffmanTree(freqMap);

    // 生成哈夫曼编码表
    unordered_map<char, string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);

    // 压缩数据
    string compressedData = compressData(rawDataStr, huffmanCodes);
    vector<unsigned char> compressedBytes = bitStringToBytes(compressedData);

    // 存储压缩数据和哈夫曼编码表
    ofstream outputFile(outputFilename, ios::binary);
    if (!outputFile) {
        cerr << "无法打开文件: " << outputFilename << endl;
        return;
    }

    // 存储哈夫曼编码表的大小
    size_t huffmanTableSize = huffmanCodes.size();
    outputFile.write(reinterpret_cast<const char*>(&huffmanTableSize), sizeof(huffmanTableSize));

    // 存储哈夫曼编码表
    for (const auto& entry : huffmanCodes) {
        outputFile.write(&entry.first, 1); // 存储字符
        string code = entry.second;
        size_t codeLen = code.length();
        outputFile.write(reinterpret_cast<const char*>(&codeLen), sizeof(codeLen)); // 存储编码长度
        outputFile.write(code.c_str(), codeLen); // 存储编码
    }

    // 存储压缩后的字节数据
    outputFile.write(reinterpret_cast<const char*>(&compressedBytes[0]), compressedBytes.size());
    outputFile.close();
}







// 重建哈夫曼树
HuffmanNode* rebuildHuffmanTree(const unordered_map<char, string>& huffmanCodes) {
    HuffmanNode* root = new HuffmanNode('\0');

    for (const auto& entry : huffmanCodes) {
        HuffmanNode* currentNode = root;
        const string& code = entry.second;

        for (char c : code) {
            if (c == '0') {
                if (!currentNode->left) {
                    currentNode->left = new HuffmanNode('\0');
                }
                currentNode = currentNode->left;
            }
            else if (c == '1') {
                if (!currentNode->right) {
                    currentNode->right = new HuffmanNode('\0');
                }
                currentNode = currentNode->right;
            }
        }

        currentNode->data = entry.first;  // 叶子节点保存字符
    }

    return root;
}

// 解压缩比特流
string decompressData(const string& bitString, HuffmanNode* root) {
    string decompressed;
    HuffmanNode* currentNode = root;

    for (char bit : bitString) {
        if (bit == '0') {
            currentNode = currentNode->left;
        }
        else {
            currentNode = currentNode->right;
        }

        if (!currentNode->left && !currentNode->right) {  // 叶子节点
            decompressed += currentNode->data;
            currentNode = root;  // 回到根节点
        }
    }

    return decompressed;
}


// 解压缩并加载数据
void decompressAndLoad(const string& compressedFilename, const string& outputFilename) {
    // 读取压缩文件
    ifstream inputFile(compressedFilename, ios::binary | ios::ate);
    if (!inputFile) {
        cerr << "无法打开文件: " << compressedFilename << endl;
        return;
    }

    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, ios::beg);

    vector<unsigned char> rawData(fileSize);
    inputFile.read(reinterpret_cast<char*>(rawData.data()), fileSize);
    inputFile.close();

    // 重建哈夫曼编码表
    istringstream dataStream(string(reinterpret_cast<const char*>(rawData.data()), rawData.size()));
    size_t huffmanTableSize;
    dataStream.read(reinterpret_cast<char*>(&huffmanTableSize), sizeof(huffmanTableSize));

    unordered_map<char, string> huffmanCodes;
    for (size_t i = 0; i < huffmanTableSize; i++) {
        char ch;
        size_t codeLen;
        dataStream.read(&ch, 1);
        dataStream.read(reinterpret_cast<char*>(&codeLen), sizeof(codeLen));

        string code(codeLen, '\0');
        dataStream.read(&code[0], codeLen);

        huffmanCodes[ch] = code;
    }

    // 重建哈夫曼树
    HuffmanNode* root = rebuildHuffmanTree(huffmanCodes);

    // 解压缩比特流
    vector<unsigned char> compressedData(rawData.begin() + dataStream.tellg(), rawData.end());
    string compressedBitString = MybytesToBitString(compressedData);

    string decompressedData = decompressData(compressedBitString, root);

    // 将解压缩后的数据写回文件
    ofstream outputFile(outputFilename, ios::binary);
    outputFile.write(decompressedData.c_str(), decompressedData.size());
    outputFile.close();
}