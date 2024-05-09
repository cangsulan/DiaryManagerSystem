#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <sstream>
#include <string>

using namespace std;

// 哈夫曼树节点
struct HuffmanNode {
    unsigned char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(unsigned char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
    HuffmanNode(unsigned char data) : data(data), left(nullptr), right(nullptr) {}
};

// 比较哈夫曼树节点的频率，用于优先队列
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};


// 构建哈夫曼树
inline HuffmanNode* buildHuffmanTree(const unordered_map<unsigned char, int>& freqMap);
// 生成哈夫曼编码表
inline void buildHuffmanCodes(HuffmanNode* root, const string& str,
    unordered_map<unsigned char, string>& huffmanCodes);
// 压缩数据
inline string compressData(const vector<unsigned char>& data,
    const unordered_map<unsigned char, string>& huffmanCodes);
// 将压缩后的比特流转换为字节数组
inline vector<unsigned char> bitStringToBytes(const string& bitString);
// 压缩并存储数据到文件
inline void compressAndStore(const string& inputFilename, const string& outputFilename);
// 解压缩比特流
inline string decompressData(const string& bitString, HuffmanNode* root);
// 解压缩并加载数据
inline void decompressAndLoad(const string& compressedFilename, const string& outputFilename);
// 重建哈夫曼树
inline HuffmanNode* rebuildHuffmanTree(const unordered_map<unsigned char, string>& huffmanCodes);
// 将字节数组转换为比特流
inline string MybytesToBitString(const vector<unsigned char>& bytes);




// 构建哈夫曼树
HuffmanNode* buildHuffmanTree(const unordered_map<unsigned char, int>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

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

    return minHeap.top();
}

// 生成哈夫曼编码表
void buildHuffmanCodes(HuffmanNode* root, const string& str,
    unordered_map<unsigned char, string>& huffmanCodes) {
    if (!root) return;

    if (root->data != '\0') {
        huffmanCodes[root->data] = str;
    }

    buildHuffmanCodes(root->left, str + "0", huffmanCodes);
    buildHuffmanCodes(root->right, str + "1", huffmanCodes);
}

// 压缩数据
string compressData(const vector<unsigned char>& data,
    const unordered_map<unsigned char, string>& huffmanCodes) {
    string compressed;
    for (unsigned char ch : data) {
        auto it = huffmanCodes.find(ch);

        if (it != huffmanCodes.end()) {
            compressed += huffmanCodes.at(ch);
        }
        else {
            cerr << "键不存在: " << ch << endl; // 键不存在，处理异常情况
        }
    }
    return compressed;
}

// 将压缩后的比特流转换为字节数组
vector<unsigned char> bitStringToBytes(const string& bitString) {
    vector<unsigned char> bytes;

    for (size_t i = 0; i < bitString.length(); i += 8) {
        string byteStr = bitString.substr(i, 8);
        if (byteStr.length() < 8) {
            byteStr.append(8 - byteStr.length(), '0');
        }

        unsigned char byte = static_cast<unsigned char>(bitset<8>(byteStr).to_ulong());
        bytes.push_back(byte);
    }

    return bytes;
}

// 压缩并存储数据到文件
void compressAndStore(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary | ios::ate);
    if (!inputFile) {
        cerr << "无法打开文件: " << inputFilename << endl;
        return;
    }

    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, ios::beg);

    vector<unsigned char> rawData(fileSize);
    inputFile.read(reinterpret_cast<char*>(rawData.data()), fileSize);
    inputFile.close();

    unordered_map<unsigned char, int> freqMap;
    //

    for (unsigned char ch : rawData) {

        freqMap[ch]++;
    }

    HuffmanNode* root = buildHuffmanTree(freqMap);
    unordered_map<unsigned char, string> huffmanCodes;
    try {   
        buildHuffmanCodes(root, "", huffmanCodes); // 如果 root 不存在，确保不会抛出异常
    }
    catch (const std::exception& e) {
        cerr << "哈夫曼编码表构建异常: " << e.what() << endl;
    }

    string compressedData = compressData(rawData, huffmanCodes);
    vector<unsigned char> compressedBytes = bitStringToBytes(compressedData);

    ofstream outputFile("HafumanCodes.dat", ios::binary);
    if (!outputFile) {
        cerr << "无法打开文件: " << outputFilename << endl;
        return;
    }

    size_t huffmanTableSize = huffmanCodes.size();
    outputFile.write(reinterpret_cast<const char*>(&huffmanTableSize), sizeof(huffmanTableSize));

    for (const auto& entry : huffmanCodes) {
        outputFile.write(reinterpret_cast<const char*>(&entry.first), 1);
        size_t codeLen = entry.second.length();
        outputFile.write(reinterpret_cast<const char*>(&codeLen), sizeof(codeLen));
        outputFile.write(entry.second.c_str(), codeLen);
    }
    outputFile.close();
    ofstream outputFile2(outputFilename, ios::binary);
    if (!outputFile) {
        cerr << "无法打开文件: " << outputFilename << endl;
        return;
    }
    outputFile2.write(reinterpret_cast<const char*>(&compressedBytes[0]), compressedBytes.size());
    outputFile2.close();
}

// 将字节数组转换为比特流
string MybytesToBitString(const vector<unsigned char>& bytes) {
    string bitString;

    for (unsigned char byte : bytes) {
        bitString += bitset<8>(byte).to_string();
    }
    return bitString;
}





// 重建哈夫曼树
HuffmanNode* rebuildHuffmanTree(const unordered_map<unsigned char, string>& huffmanCodes) {
    HuffmanNode* root = new HuffmanNode('\0'); // 根节点

    for (const auto& entry : huffmanCodes) {
        HuffmanNode* currentNode = root;
        const string& code = entry.second;

        for (char c : code) {
            if (c == '0') {
                if (!currentNode->left) {
                    currentNode->left = new HuffmanNode('\0'); // 确保节点存在
                }
                currentNode = currentNode->left;
            }
            else if (c == '1') {
                if (!currentNode->right) {
                    currentNode->right = new HuffmanNode('\0'); // 确保节点存在
                }
                currentNode = currentNode->right;
            }
        }

        currentNode->data = entry.first; // 确保叶子节点正确赋值
    }

    return root;
}



// 解压缩比特流
string decompressData(const string& bitString, HuffmanNode* root) {
    if (!root) {
        throw std::runtime_error("哈夫曼树根节点为空"); // 处理 `NULL` 根节点
    }

    string decompressed;
    HuffmanNode* currentNode = root;

    for (char bit : bitString) {
        if (bit == '0') {
            if (!currentNode->left) {
                throw std::runtime_error("解压缩过程中访问了 `NULL` 左节点"); // 处理 `NULL` 节点
            }
            currentNode = currentNode->left;
        }
        else if (bit == '1') {
            if (!currentNode->right) {
                throw std::runtime_error("解压缩过程中访问了 `NULL` 右节点"); // 处理 `NULL` 节点
            }
            currentNode = currentNode->right;
        }

        if (!currentNode->left && !currentNode->right) { // 叶子节点
            decompressed += currentNode->data;
            currentNode = root; // 回到根节点
        }
    }

    return decompressed;
}


// 解压缩并加载数据
void decompressAndLoad(const string& compressedFilename, const string& outputFilename) {
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

    istringstream dataStream(string(reinterpret_cast<const char*>(rawData.data()), rawData.size()));
    
    
    ifstream inputFile2("HafumanCodes.dat", ios::binary | ios::ate);
    if (!inputFile2) {
        cerr << "无法打开文件: " << "HafumanCodes.dat" << endl;
        return;
    }

    size_t fileSize2 = inputFile2.tellg();
    inputFile2.seekg(0, ios::beg);

    vector<unsigned char> rawData2(fileSize2);
    inputFile2.read(reinterpret_cast<char*>(rawData2.data()), fileSize2);
    inputFile2.close();

    istringstream dataStream2(string(reinterpret_cast<const char*>(rawData2.data()), rawData2.size()));


    size_t huffmanTableSize;
    dataStream2.read(reinterpret_cast<char*>(&huffmanTableSize), sizeof(huffmanTableSize));

    unordered_map<unsigned char, string> huffmanCodes;
    for (size_t i = 0; i < huffmanTableSize; i++) {
        unsigned char ch;
        dataStream2.read(reinterpret_cast<char*>(&ch), 1);

        size_t codeLen;
        dataStream2.read(reinterpret_cast<char*>(&codeLen), sizeof(codeLen));

        string code(codeLen, '\0');
        dataStream2.read(&code[0], codeLen);

        huffmanCodes[ch] = code; // 正确读取哈夫曼编码表
    }

    HuffmanNode* root = rebuildHuffmanTree(huffmanCodes); // 使用编码表重建哈夫曼树

    // 使用哈夫曼树来解压缩
    /*vector<unsigned char> compressedData(rawData.begin() + dataStream.tellg(), rawData.end());*/
    string compressedBitString = MybytesToBitString(rawData);

    string decompressedData = decompressData(compressedBitString, root);

    ofstream outputFile(outputFilename, ios::binary);
    outputFile.write(decompressedData.c_str(), decompressedData.size());
    outputFile.close();
}
