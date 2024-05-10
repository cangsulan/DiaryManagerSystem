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
inline void decompressAndLoad(const std::string& compressedFilename, const std::string& huffmanFilename, const std::string& outputFilename);
// 重建哈夫曼树
inline HuffmanNode* rebuildHuffmanTree(const unordered_map<unsigned char, string>& huffmanCodes);
// 将字节数组转换为比特流
inline string MybytesToBitString(const vector<unsigned char>& bytes);




inline void printHuffmanTree(HuffmanNode* root, const std::string& prefix = "") {
    if (!root) return;

    std::cout << prefix << "Node: " << static_cast<int>(root->data) << ", Freq: " << root->freq << std::endl;
    printHuffmanTree(root->left, prefix + "L-");
    printHuffmanTree(root->right, prefix + "R-");
}







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
    
    //// 检查原始数据中的空白字符
    //int bainum = 0;
    //for (unsigned char ch : rawData) {
    //    if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
    //        // 原始数据中的空白字符
    //        bainum++;
    //        
    //    }
    //}
    //std::cout << "空白字符：" << bainum << std::endl;
    
    cout << rawData.size() << endl;
    for (auto& ch2 : rawData) {
        cout << ch2;
    }
    cout << endl;
    cout << "------------------------" << endl;

    unordered_map<unsigned char, int> freqMap;
    //

    for (unsigned char ch : rawData) {

        freqMap[ch]++;
    }
    
    
    /*std::cout << "频率统计:" << std::endl;
    for (const auto& entry : freqMap) {
        std::cout << "字符: " << entry.first << ", 频率: " << entry.second << std::endl;
    }*/
    
    
    
    HuffmanNode* root = buildHuffmanTree(freqMap);

    ////test测试：
    //printHuffmanTree(root);
    //cout << "----------------------------------------------" << endl;


    unordered_map<unsigned char, string> huffmanCodes;
    try {   
        buildHuffmanCodes(root, "", huffmanCodes); // 如果 root 不存在，确保不会抛出异常
    }
    catch (const std::exception& e) {
        cerr << "哈夫曼编码表构建异常: " << e.what() << endl;
    }

    string compressedData = compressData(rawData, huffmanCodes);

    vector<unsigned char> compressedBytes = bitStringToBytes(compressedData);

    //////test检测：
    //cout << "原来的哈夫曼编码表为： size为 " <<huffmanCodes.size()<< endl;
    //for (auto& entry2 : huffmanCodes) {
    //    cout << entry2.first << "  :  " << entry2.second << endl;
    //}
    //cout << "--------------------------" << endl;
    //cout << "压缩后的数据 为：" << compressData << endl;
    //cout << "压缩后的字节：  size为 " <<compressedBytes.size()<< endl;
    //for (unsigned char ch2 : compressedBytes) {
    //    cout << ch2;
    //}
    //cout << endl;

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
        try {
            for (unsigned char c : code) {
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
        }catch(const std::exception& e){
            
        }
        
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
    try {
        for (unsigned char bit : bitString) {
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
    }catch(const std::exception& e){

    }

    return decompressed;
}


//// 解压缩并加载数据
//void decompressAndLoad(const string& compressedFilename, const string& outputFilename) {
//    ifstream inputFile(compressedFilename, ios::binary | ios::ate);
//    if (!inputFile) {
//        cerr << "无法打开文件: " << compressedFilename << endl;
//        return;
//    }
//
//    size_t fileSize = inputFile.tellg();
//    inputFile.seekg(0, ios::beg);
//
//    vector<unsigned char> rawData(fileSize);
//    inputFile.read(reinterpret_cast<char*>(rawData.data()), fileSize);
//    inputFile.close();
//
//    istringstream dataStream(string(reinterpret_cast<const char*>(rawData.data()), rawData.size()));
//    
//    
//    ifstream inputFile2("HafumanCodes.dat", ios::binary);
//    if (!inputFile2) {
//        cerr << "无法打开文件: " << "HafumanCodes.dat" << endl;
//        return;
//    }
//    size_t huffmanTableSize;
//    inputFile2.read(reinterpret_cast<char*>(&huffmanTableSize), sizeof(huffmanTableSize)); // 读取编码表大小
//
//    unordered_map<unsigned char, string> huffmanCodes;
//    for (size_t i = 0; i < huffmanTableSize; i++) {
//        unsigned char ch;
//        inputFile.read(reinterpret_cast<char*>(&ch), 1); // 读取字符
//
//        size_t codeLen;
//        inputFile.read(reinterpret_cast<char*>(&codeLen), sizeof(codeLen)); // 读取编码长度
//
//        string code(codeLen, '\0');
//        inputFile.read(&code[0], codeLen); // 读取编码内容
//
//        huffmanCodes[ch] = code; // 添加到哈夫曼编码表
//    }
//
//
//    //////test检测：
//    //cout << "解压缩时的哈夫曼编码表为： size为 " << huffmanCodes.size() << endl;
//    //for (auto& entry2 : huffmanCodes) {
//    //    cout << entry2.first << "  :  " << entry2.second << endl;
//    //}
//    //cout << "--------------------------" << endl;
//
//
//    HuffmanNode* root = rebuildHuffmanTree(huffmanCodes); // 使用编码表重建哈夫曼树
//
//    // 使用哈夫曼树来解压缩
//    /*vector<unsigned char> compressedData(rawData.begin() + dataStream.tellg(), rawData.end());*/
//    string compressedBitString = MybytesToBitString(rawData);
//
//    string decompressedData = decompressData(compressedBitString, root);
//
//    ofstream outputFile(outputFilename, ios::binary);
//    outputFile.write(decompressedData.c_str(), decompressedData.size());
//    outputFile.close();
//}

void decompressAndLoad(const std::string& compressedFilename, const std::string& huffmanFilename, const std::string& outputFilename) {
    // 打开压缩文件
    std::ifstream compressedFile(compressedFilename, std::ios::binary | std::ios::ate);
    if (!compressedFile) {
        std::cerr << "无法打开压缩文件: " << compressedFilename << std::endl;
        return;
    }

    // 读取压缩文件的内容
    std::streamsize compressedFileSize = compressedFile.tellg();
    compressedFile.seekg(0, std::ios::beg);

    std::vector<unsigned char> compressedData(compressedFileSize);
    compressedFile.read(reinterpret_cast<char*>(compressedData.data()), compressedFileSize);
    compressedFile.close();

    // 打开哈夫曼编码表文件
    std::ifstream huffmanFile(huffmanFilename, std::ios::binary);
    if (!huffmanFile) {
        std::cerr << "无法打开哈夫曼编码表文件: " << huffmanFilename << std::endl;
        return;
    }

    // 读取哈夫曼编码表
    size_t huffmanTableSize;
    huffmanFile.read(reinterpret_cast<char*>(&huffmanTableSize), sizeof(huffmanTableSize));
    if (huffmanTableSize > 256) {
        std::cerr << "编码表大小异常" << std::endl;
        return;
    }

    std::unordered_map<unsigned char, std::string> huffmanCodes;
    for (size_t i = 0; i < huffmanTableSize; i++) {
        
        unsigned char ch;
        huffmanFile.read(reinterpret_cast<char*>(&ch), 1); // 读取字符

        size_t codeLen;
        huffmanFile.read(reinterpret_cast<char*>(&codeLen), sizeof(codeLen)); // 读取编码长度
        
        std::string code(codeLen, '\0');
        huffmanFile.read(&code[0], codeLen); // 读取编码内容
        
        huffmanCodes[ch] = code; // 保存到哈夫曼编码表
    }

    huffmanFile.close();
    

    
    
    //////test检测：
    //cout << "解压缩时的哈夫曼编码表为： size为 " << huffmanCodes.size() << endl;
    //for (auto& entry2 : huffmanCodes) {
    //    cout << entry2.first << "  :  " << entry2.second << endl;
    //}
    //cout << "--------------------------" << endl;



    // 使用哈夫曼编码表重建哈夫曼树
    HuffmanNode* root = rebuildHuffmanTree(huffmanCodes);


    ////test测试：
    //printHuffmanTree(root);




    // 将压缩后的字节转换为比特流
    std::string compressedBitString;
    for (unsigned char byte : compressedData) {
        compressedBitString += std::bitset<8>(byte).to_string();
    }

    // 使用哈夫曼树进行解压缩
    std::string decompressedData = decompressData(compressedBitString, root);

    // 将解压缩后的数据写入输出文件
    std::ofstream outputFile(outputFilename, std::ios::binary);
    if (!outputFile) {
        std::cerr << "无法打开输出文件: " << outputFilename << std::endl;
        return;
    }


    cout << "--------------------" << endl;
    cout << decompressedData << endl;


    outputFile.write(decompressedData.c_str(), decompressedData.size());
    outputFile.close();
}
