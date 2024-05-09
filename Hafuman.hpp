#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <sstream>
#include <string>

// ���������ڵ�
struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
    HuffmanNode(char data) : data(data), left(nullptr), right(nullptr) {}
};

// �ȽϹ��������ڵ��Ƶ�ʣ��������ȶ���
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

inline HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freqMap);// ������������

inline void buildHuffmanCodes(HuffmanNode* root, const string& str,
    unordered_map<char, string>& huffmanCodes);// ���ɹ����������

inline string compressData(const string& data, const unordered_map<char, string>& huffmanCodes);// ѹ������

inline vector<unsigned char> bitStringToBytes(const string& bitString);// ��ѹ����ı�����ת��Ϊ�ֽ�����

inline string MybytesToBitString(const vector<unsigned char>& bytes);// ���ֽ�����ת��Ϊ������

//***
inline void compressAndStore(const string& inputFilename, const string& outputFilename);// ѹ�����洢���ݵ��ļ�



//�����ǽ�ѹ���ĺ�����

// �ؽ���������
inline HuffmanNode* rebuildHuffmanTree(const unordered_map<char, string>& huffmanCodes);

// ��ѹ��������
inline string decompressData(const string& bitString, HuffmanNode* root);

// ��ѹ������������
inline void decompressAndLoad(const string& compressedFilename, const string& outputFilename);


using namespace std;

// ������������
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    // ��ʼ����С��
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

    return minHeap.top(); // ���յĹ����������ڵ�
}

// ���ɹ����������
void buildHuffmanCodes(HuffmanNode* root, const string& str,
    unordered_map<char, string>& huffmanCodes) {
    if (!root) {
        return;
    }

    if (root->data != '\0') { // Ҷ�ӽڵ�
        huffmanCodes[root->data] = str;
    }

    buildHuffmanCodes(root->left, str + "0", huffmanCodes);
    buildHuffmanCodes(root->right, str + "1", huffmanCodes);
}

// ѹ������
string compressData(const string& data, const unordered_map<char, string>& huffmanCodes) {
    string compressed;
    for (char ch : data) {
        compressed += huffmanCodes.at(ch);
    }
    return compressed;
}

// ��ѹ����ı�����ת��Ϊ�ֽ�����
vector<unsigned char> bitStringToBytes(const string& bitString) {
    vector<unsigned char> bytes;

    // ÿ8λת��Ϊһ���ֽ�
    for (size_t i = 0; i < bitString.length(); i += 8) {
        string byteStr = bitString.substr(i, 8);
        if (byteStr.length() < 8) {
            byteStr.append(8 - byteStr.length(), '0'); // ����8λ�Ĳ�����0
        }

        unsigned char byte = static_cast<unsigned char>(bitset<8>(byteStr).to_ulong());
        bytes.push_back(byte);
    }

    return bytes;
}

// ���ֽ�����ת��Ϊ������
string MybytesToBitString(const vector<unsigned char>& bytes) {
    string bitString;

    for (unsigned char byte : bytes) {
        bitString += bitset<8>(byte).to_string();
    }

    return bitString;
}

// ѹ�����洢���ݵ��ļ�
void compressAndStore(const string& inputFilename, const string& outputFilename) {
    // ��ȡԭʼ����
    ifstream inputFile(inputFilename, ios::binary | ios::ate);
    if (!inputFile) {
        cerr << "�޷����ļ�: " << inputFilename << endl;
        return;
    }

    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, ios::beg);

    vector<char> rawData(fileSize);
    inputFile.read(rawData.data(), fileSize);
    inputFile.close();

    string rawDataStr(rawData.begin(), rawData.end());

    // ͳ���ַ�Ƶ��
    unordered_map<char, int> freqMap;
    for (char ch : rawDataStr) {
        freqMap[ch]++;
    }

    // ������������
    HuffmanNode* root = buildHuffmanTree(freqMap);

    // ���ɹ����������
    unordered_map<char, string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);

    // ѹ������
    string compressedData = compressData(rawDataStr, huffmanCodes);
    vector<unsigned char> compressedBytes = bitStringToBytes(compressedData);

    // �洢ѹ�����ݺ͹����������
    ofstream outputFile(outputFilename, ios::binary);
    if (!outputFile) {
        cerr << "�޷����ļ�: " << outputFilename << endl;
        return;
    }

    // �洢�����������Ĵ�С
    size_t huffmanTableSize = huffmanCodes.size();
    outputFile.write(reinterpret_cast<const char*>(&huffmanTableSize), sizeof(huffmanTableSize));

    // �洢�����������
    for (const auto& entry : huffmanCodes) {
        outputFile.write(&entry.first, 1); // �洢�ַ�
        string code = entry.second;
        size_t codeLen = code.length();
        outputFile.write(reinterpret_cast<const char*>(&codeLen), sizeof(codeLen)); // �洢���볤��
        outputFile.write(code.c_str(), codeLen); // �洢����
    }

    // �洢ѹ������ֽ�����
    outputFile.write(reinterpret_cast<const char*>(&compressedBytes[0]), compressedBytes.size());
    outputFile.close();
}







// �ؽ���������
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

        currentNode->data = entry.first;  // Ҷ�ӽڵ㱣���ַ�
    }

    return root;
}

// ��ѹ��������
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

        if (!currentNode->left && !currentNode->right) {  // Ҷ�ӽڵ�
            decompressed += currentNode->data;
            currentNode = root;  // �ص����ڵ�
        }
    }

    return decompressed;
}


// ��ѹ������������
void decompressAndLoad(const string& compressedFilename, const string& outputFilename) {
    // ��ȡѹ���ļ�
    ifstream inputFile(compressedFilename, ios::binary | ios::ate);
    if (!inputFile) {
        cerr << "�޷����ļ�: " << compressedFilename << endl;
        return;
    }

    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, ios::beg);

    vector<unsigned char> rawData(fileSize);
    inputFile.read(reinterpret_cast<char*>(rawData.data()), fileSize);
    inputFile.close();

    // �ؽ������������
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

    // �ؽ���������
    HuffmanNode* root = rebuildHuffmanTree(huffmanCodes);

    // ��ѹ��������
    vector<unsigned char> compressedData(rawData.begin() + dataStream.tellg(), rawData.end());
    string compressedBitString = MybytesToBitString(compressedData);

    string decompressedData = decompressData(compressedBitString, root);

    // ����ѹ���������д���ļ�
    ofstream outputFile(outputFilename, ios::binary);
    outputFile.write(decompressedData.c_str(), decompressedData.size());
    outputFile.close();
}