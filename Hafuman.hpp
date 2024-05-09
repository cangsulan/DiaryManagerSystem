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

// ���������ڵ�
struct HuffmanNode {
    unsigned char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(unsigned char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
    HuffmanNode(unsigned char data) : data(data), left(nullptr), right(nullptr) {}
};

// �ȽϹ��������ڵ��Ƶ�ʣ��������ȶ���
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};


// ������������
inline HuffmanNode* buildHuffmanTree(const unordered_map<unsigned char, int>& freqMap);
// ���ɹ����������
inline void buildHuffmanCodes(HuffmanNode* root, const string& str,
    unordered_map<unsigned char, string>& huffmanCodes);
// ѹ������
inline string compressData(const vector<unsigned char>& data,
    const unordered_map<unsigned char, string>& huffmanCodes);
// ��ѹ����ı�����ת��Ϊ�ֽ�����
inline vector<unsigned char> bitStringToBytes(const string& bitString);
// ѹ�����洢���ݵ��ļ�
inline void compressAndStore(const string& inputFilename, const string& outputFilename);
// ��ѹ��������
inline string decompressData(const string& bitString, HuffmanNode* root);
// ��ѹ������������
inline void decompressAndLoad(const string& compressedFilename, const string& outputFilename);
// �ؽ���������
inline HuffmanNode* rebuildHuffmanTree(const unordered_map<unsigned char, string>& huffmanCodes);
// ���ֽ�����ת��Ϊ������
inline string MybytesToBitString(const vector<unsigned char>& bytes);




// ������������
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

// ���ɹ����������
void buildHuffmanCodes(HuffmanNode* root, const string& str,
    unordered_map<unsigned char, string>& huffmanCodes) {
    if (!root) return;

    if (root->data != '\0') {
        huffmanCodes[root->data] = str;
    }

    buildHuffmanCodes(root->left, str + "0", huffmanCodes);
    buildHuffmanCodes(root->right, str + "1", huffmanCodes);
}

// ѹ������
string compressData(const vector<unsigned char>& data,
    const unordered_map<unsigned char, string>& huffmanCodes) {
    string compressed;
    for (unsigned char ch : data) {
        auto it = huffmanCodes.find(ch);

        if (it != huffmanCodes.end()) {
            compressed += huffmanCodes.at(ch);
        }
        else {
            cerr << "��������: " << ch << endl; // �������ڣ������쳣���
        }
    }
    return compressed;
}

// ��ѹ����ı�����ת��Ϊ�ֽ�����
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

// ѹ�����洢���ݵ��ļ�
void compressAndStore(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary | ios::ate);
    if (!inputFile) {
        cerr << "�޷����ļ�: " << inputFilename << endl;
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
        buildHuffmanCodes(root, "", huffmanCodes); // ��� root �����ڣ�ȷ�������׳��쳣
    }
    catch (const std::exception& e) {
        cerr << "��������������쳣: " << e.what() << endl;
    }

    string compressedData = compressData(rawData, huffmanCodes);
    vector<unsigned char> compressedBytes = bitStringToBytes(compressedData);

    ofstream outputFile("HafumanCodes.dat", ios::binary);
    if (!outputFile) {
        cerr << "�޷����ļ�: " << outputFilename << endl;
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
        cerr << "�޷����ļ�: " << outputFilename << endl;
        return;
    }
    outputFile2.write(reinterpret_cast<const char*>(&compressedBytes[0]), compressedBytes.size());
    outputFile2.close();
}

// ���ֽ�����ת��Ϊ������
string MybytesToBitString(const vector<unsigned char>& bytes) {
    string bitString;

    for (unsigned char byte : bytes) {
        bitString += bitset<8>(byte).to_string();
    }
    return bitString;
}





// �ؽ���������
HuffmanNode* rebuildHuffmanTree(const unordered_map<unsigned char, string>& huffmanCodes) {
    HuffmanNode* root = new HuffmanNode('\0'); // ���ڵ�

    for (const auto& entry : huffmanCodes) {
        HuffmanNode* currentNode = root;
        const string& code = entry.second;

        for (char c : code) {
            if (c == '0') {
                if (!currentNode->left) {
                    currentNode->left = new HuffmanNode('\0'); // ȷ���ڵ����
                }
                currentNode = currentNode->left;
            }
            else if (c == '1') {
                if (!currentNode->right) {
                    currentNode->right = new HuffmanNode('\0'); // ȷ���ڵ����
                }
                currentNode = currentNode->right;
            }
        }

        currentNode->data = entry.first; // ȷ��Ҷ�ӽڵ���ȷ��ֵ
    }

    return root;
}



// ��ѹ��������
string decompressData(const string& bitString, HuffmanNode* root) {
    if (!root) {
        throw std::runtime_error("�����������ڵ�Ϊ��"); // ���� `NULL` ���ڵ�
    }

    string decompressed;
    HuffmanNode* currentNode = root;

    for (char bit : bitString) {
        if (bit == '0') {
            if (!currentNode->left) {
                throw std::runtime_error("��ѹ�������з����� `NULL` ��ڵ�"); // ���� `NULL` �ڵ�
            }
            currentNode = currentNode->left;
        }
        else if (bit == '1') {
            if (!currentNode->right) {
                throw std::runtime_error("��ѹ�������з����� `NULL` �ҽڵ�"); // ���� `NULL` �ڵ�
            }
            currentNode = currentNode->right;
        }

        if (!currentNode->left && !currentNode->right) { // Ҷ�ӽڵ�
            decompressed += currentNode->data;
            currentNode = root; // �ص����ڵ�
        }
    }

    return decompressed;
}


// ��ѹ������������
void decompressAndLoad(const string& compressedFilename, const string& outputFilename) {
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

    istringstream dataStream(string(reinterpret_cast<const char*>(rawData.data()), rawData.size()));
    
    
    ifstream inputFile2("HafumanCodes.dat", ios::binary | ios::ate);
    if (!inputFile2) {
        cerr << "�޷����ļ�: " << "HafumanCodes.dat" << endl;
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

        huffmanCodes[ch] = code; // ��ȷ��ȡ�����������
    }

    HuffmanNode* root = rebuildHuffmanTree(huffmanCodes); // ʹ�ñ�����ؽ���������

    // ʹ�ù�����������ѹ��
    /*vector<unsigned char> compressedData(rawData.begin() + dataStream.tellg(), rawData.end());*/
    string compressedBitString = MybytesToBitString(rawData);

    string decompressedData = decompressData(compressedBitString, root);

    ofstream outputFile(outputFilename, ios::binary);
    outputFile.write(decompressedData.c_str(), decompressedData.size());
    outputFile.close();
}
