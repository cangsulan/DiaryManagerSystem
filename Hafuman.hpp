#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <sstream>
#include <string>
const unsigned char NULL_MARKER = 255; // ʹ��һ����ȷ�ı��
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
inline void decompressAndLoad(const std::string& compressedFilename, const std::string& huffmanFilename, const std::string& outputFilename);
// �ؽ���������
inline HuffmanNode* rebuildHuffmanTree(const unordered_map<unsigned char, string>& huffmanCodes);
// ���ֽ�����ת��Ϊ������
inline string MybytesToBitString(const vector<unsigned char>& bytes);




inline void printHuffmanTree(HuffmanNode* root, const std::string& prefix = "") {
    if (!root) return;

    std::cout << prefix << "Node: " << static_cast<int>(root->data) << ", Freq: " << root->freq << std::endl;
    printHuffmanTree(root->left, prefix + "L-");
    printHuffmanTree(root->right, prefix + "R-");
}







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

        HuffmanNode* combined = new HuffmanNode(NULL_MARKER, left->freq + right->freq);
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

    if (root->data != NULL_MARKER) {
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
    ifstream inputFile(inputFilename, ios::in | ios::binary | ios::ate);
    if (!inputFile) {
        cerr << "�޷����ļ�: " << inputFilename << endl;
        return;
    }

    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, ios::beg);

    vector<unsigned char> rawData(fileSize);
    inputFile.read(reinterpret_cast<char*>(rawData.data()), fileSize);
    
    
    //// ���ԭʼ�����еĿհ��ַ�
    //int bainum = 0;
    //for (unsigned char ch : rawData) {
    //    if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
    //        // ԭʼ�����еĿհ��ַ�
    //        bainum++;
    //        
    //    }
    //}
    //std::cout << "�հ��ַ���" << bainum << std::endl;
    //std::cout << "�ļ�����:" << std::endl;
    //for (const auto& byte : rawData) {
    //    std::cout << std::hex << static_cast<int>(byte) << " "; // ��ӡΪʮ������
    //}
    //std::cout << std::endl;

    //char* testData = new char[fileSize];
    //for (int i = 0; i < fileSize; i++) {
    //    testData[i] = '1';
    //}
    //inputFile.seekg(0, ios::beg);
    //inputFile.read(testData, fileSize);
    //for (int i = 0; i < fileSize; i++) {
    //    cout << testData[i];
    //}
    //cout << endl;
    //cout << "--------------------------------------------------------" << endl;
    //cout << endl;
    //delete[] testData;
    //cout << rawData.size() << endl;
    //for (auto& ch2 : rawData) {
    //    cout << ch2;
    //}
    //cout << endl;
    //cout << "------------------------" << endl;


    inputFile.close();
    unordered_map<unsigned char, int> freqMap;
    //

    for (unsigned char ch : rawData) {

        freqMap[ch]++;
    }
    
    
    std::cout << "Ƶ��ͳ��:" << std::endl;
    for (const auto& entry : freqMap) {
        std::cout << "�ַ�: " << entry.first << ", Ƶ��: " << entry.second << std::endl;
    }
    
    
    
    HuffmanNode* root = buildHuffmanTree(freqMap);

    //test���ԣ�
    printHuffmanTree(root);
    cout << "----------------------------------------------" << endl;


    unordered_map<unsigned char, string> huffmanCodes;
    try {   
        buildHuffmanCodes(root, "", huffmanCodes); // ��� root �����ڣ�ȷ�������׳��쳣
    }
    catch (const std::exception& e) {
        cerr << "��������������쳣: " << e.what() << endl;
    }

    string compressedData = compressData(rawData, huffmanCodes);

    vector<unsigned char> compressedBytes = bitStringToBytes(compressedData);

    ////test��⣺
    cout << "ԭ���Ĺ����������Ϊ�� sizeΪ " <<huffmanCodes.size()<< endl;
    for (auto& entry2 : huffmanCodes) {
        cout << entry2.first << "  :  " << entry2.second << endl;
    }
    cout << "--------------------------" << endl;
    /*cout << "ѹ��������� Ϊ��" << oct<<compressData << endl;
    cout << "ѹ������ֽڣ�  sizeΪ " <<compressedBytes.size()<< endl;
    for (auto&  ch2 : compressedBytes) {
        printf_s("%c", ch2);
    }
    cout << endl;*/

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
    //�ȴ洢ѹ��ǰ�ļ���ԭ����С��
    outputFile2.write(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize)); // �洢ʵ�����ݳ���
    
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
        try {
            for (unsigned char c : code) {
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
        }catch(const std::exception& e){
            
        }
        
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
    try {
        for (unsigned char bit : bitString) {
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
    }catch(const std::exception& e){

    }

    return decompressed;
}




void decompressAndLoad(const std::string& compressedFilename, const std::string& huffmanFilename, const std::string& outputFilename) {
    // ��ѹ���ļ�
    std::ifstream compressedFile(compressedFilename, std::ios::binary | std::ios::ate);
    if (!compressedFile) {
        std::cerr << "�޷���ѹ���ļ�: " << compressedFilename << std::endl;
        return;
    }

    // ��ȡѹ���ļ�������
    std::streamsize compressedFileSize = compressedFile.tellg();
    compressedFile.seekg(0, std::ios::beg);

    size_t actualSize;
    compressedFile.read(reinterpret_cast<char*>(&actualSize), sizeof(actualSize)); // ��ȡʵ�����ݳ���


    std::vector<unsigned char> compressedData(compressedFileSize);
    compressedFile.read(reinterpret_cast<char*>(compressedData.data()), compressedFileSize);
    compressedFile.close();





    // �򿪹�����������ļ�
    std::ifstream huffmanFile(huffmanFilename, std::ios::binary);
    if (!huffmanFile) {
        std::cerr << "�޷��򿪹�����������ļ�: " << huffmanFilename << std::endl;
        return;
    }

    // ��ȡ�����������
    size_t huffmanTableSize;
    huffmanFile.read(reinterpret_cast<char*>(&huffmanTableSize), sizeof(huffmanTableSize));
    if (huffmanTableSize > 256) {
        std::cerr << "������С�쳣" << std::endl;
        return;
    }

    std::unordered_map<unsigned char, std::string> huffmanCodes;
    for (size_t i = 0; i < huffmanTableSize; i++) {
        
        unsigned char ch;
        huffmanFile.read(reinterpret_cast<char*>(&ch), 1); // ��ȡ�ַ�

        size_t codeLen;
        huffmanFile.read(reinterpret_cast<char*>(&codeLen), sizeof(codeLen)); // ��ȡ���볤��
        
        std::string code(codeLen, '\0');
        huffmanFile.read(&code[0], codeLen); // ��ȡ��������
        
        huffmanCodes[ch] = code; // ���浽�����������
    }

    huffmanFile.close();
    

    
    
    //////test��⣺
    //cout << "��ѹ��ʱ�Ĺ����������Ϊ�� sizeΪ " << huffmanCodes.size() << endl;
    //for (auto& entry2 : huffmanCodes) {
    //    cout << entry2.first << "  :  " << entry2.second << endl;
    //}
    //cout << "--------------------------" << endl;



    // ʹ�ù�����������ؽ���������
    HuffmanNode* root = rebuildHuffmanTree(huffmanCodes);


    ////test���ԣ�
    //printHuffmanTree(root);




    // ��ѹ������ֽ�ת��Ϊ������
    std::string compressedBitString;
    for (unsigned char byte : compressedData) {
        compressedBitString += std::bitset<8>(byte).to_string();
    }


    ////test���ԣ�
    //cout << "ѹ������ֽ�Ϊ" << endl;
    //cout << compressedBitString << endl;
    
    
    // ʹ�ù����������н�ѹ��
    std::string decompressedData = decompressData(compressedBitString, root);

    // ����ѹ���������д������ļ�
    std::ofstream outputFile(outputFilename, ios::out | ios::binary);
    if (!outputFile) {
        std::cerr << "�޷�������ļ�: " << outputFilename << std::endl;
        return;
    }


    //// ����ѹ���������
    //std::cout << "��ѹ���������:" << std::endl;
    //for (char c : decompressedData) {
    //    std::cout << std::hex << static_cast<int>(static_cast<unsigned char>(c)) << " "; // �������
    //}
    //std::cout << std::endl;
    
    
    // ��ȡʵ�����ݳ���
    std::string truncatedData = decompressedData.substr(0, actualSize); // ȷ����ѹ����ֻ����ʵ������


    outputFile.write(truncatedData.c_str(), truncatedData.size());
    outputFile.close();


    //std::ifstream checkFile(outputFilename, std::ios::binary | std::ios::ate);
    //if (!checkFile) {
    //    std::cerr << "�޷�������ļ�: " << outputFilename << std::endl;
    //    return;
    //}

    //size_t checkFileSize = checkFile.tellg(); // ��ȡ�ļ���С
    //checkFile.seekg(0, std::ios::beg);

    //std::vector<unsigned char> checkData(checkFileSize);
    //checkFile.read(reinterpret_cast<char*>(checkData.data()), checkFileSize);

    //checkFile.close();

    //// ��ӡ�ļ�����
    //std::cout << "д�����ļ�����:" << std::endl;
    //for (const auto& byte : checkData) {
    //    std::cout << std::hex << static_cast<int>(byte) << " "; // ��ʮ�����ƴ�ӡ
    //}
    //std::cout << std::endl;

}
