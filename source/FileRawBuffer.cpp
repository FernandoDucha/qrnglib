/* 
 * File:   RawBuffer.cpp
 * Author: fernando
 * 
 * Created on 27 de Abril de 2013, 13:36
 */

#include <assert.h>
#include "FileRawBuffer.h"
uint8_t * FileRawBuffer::reverseTable = 0;

FileRawBuffer::FileRawBuffer(char * filename, ulong s) : chrono(Cronometro::NANO_S), filestream(filename, ios::in | ios::binary) {
    if (filestream.is_open()) {
        initializeReverseTable();
        chrono.start();
        setupRNG();
        filestream.seekg(0, filestream.end);
        fsize = filestream.tellg();
        filestream.seekg(0, filestream.beg);
        rawBuffer = new uint8_t[s];
        filestream.read((char*) rawBuffer, s);
        filestream.seekg(0, filestream.beg);
        pos = 0;
        this->size = s;
        state = Fetch::PARTIAL;
    } else {
        cerr << "File does not exist. Leaving..." << endl;
    }
}

FileRawBuffer::FileRawBuffer(char * filename, Fetch mode) : chrono(Cronometro::NANO_S), filestream(filename, ios::in | ios::binary) {
    if (filestream.is_open()) {
        initializeReverseTable();
        chrono.start();
        setupRNG();
        filestream.seekg(0, filestream.end);
        fsize = filestream.tellg();
        filestream.seekg(0, filestream.beg);
        if (mode == Fetch::EVERYTHING) {
            size = fsize;
            rawBuffer = new uint8_t [size];
            filestream.read((char*) rawBuffer, size);
            filestream.close();
            filestream.seekg(0, filestream.beg);
            pos = 0;
            state = Fetch::EVERYTHING;
        } else {
            state = Fetch::NOTHING;
            size = fsize;
            rawBuffer = NULL;
            pos = 0;
        }
    } else {
        cerr << "File does not exist. Leaving..." << endl;
    }

}

void FileRawBuffer::setFilePosition(u_int64_t to) {
    if (filestream.is_open()) {
        filestream.seekg(to);
    }
}

void FileRawBuffer::setBufferPosition(u_int64_t to) {
    assert(to < size);
    pos = to;
}

FileRawBuffer::~FileRawBuffer() {
    if (rawBuffer) {
        delete [] rawBuffer;
    }
    if(reverseTable){
        delete [] reverseTable;
    }
    filestream.close();
}

unsigned long int FileRawBuffer::getSize() const {
    return size;
}

ulong FileRawBuffer::getFileSize() const {
    return fsize;
}

void FileRawBuffer::generateBufferComplete() {
    if (state) {
        delete [] rawBuffer;
    }
    filestream.seekg(0, filestream.beg);
    rawBuffer = new uint8_t[fsize];
    filestream.read((char*) rawBuffer, fsize);
    size = fsize;
    filestream.seekg(0, filestream.beg);
    state = Fetch::EVERYTHING;
}

void FileRawBuffer::generateBuffer(ulong n) {
    size = 0;
    if (rawBuffer) {
        delete [] rawBuffer;
    }
    if (n <= fsize) {

        uint64_t a = filestream.tellg();
        if ((size != 0)&&(n + a >= size)) {
            a = (n + a) % size;
        }
        rawBuffer = new uint8_t[n];
        filestream.read((char*) rawBuffer, n);
        filestream.seekg(a, ios::beg);
        a = filestream.tellg();
        pos = 0;
        size = n;
        state = Fetch::PARTIAL;
    }
}

uint8_t * FileRawBuffer::getBytesFromFile(ulong n) {
    ulong fpos = filestream.tellg();
    if ((fpos + n) <= fsize) {
        uint8_t * ret = new uint8_t[n];
        filestream.read((char*) ret, n);
        return ret;
    } else {
        return NULL;
    }
}

uint8_t * FileRawBuffer::getBytesFromFileRandom(ulong n) {
    ulong p = getRandomPos();
    p = (p + n <= size) ? p : ((p + n) % size);
    ulong temp = filestream.tellg();
    filestream.seekg(p);
    uint8_t * ret = new uint8_t[n];
    filestream.read((char*) ret, n);
    filestream.seekg(temp);
    return ret;
}

ulong FileRawBuffer::getRandomPos() {
    mpz_class ret, max(size);
    mpz_urandomm(ret.get_mpz_t(), rng, max.get_mpz_t());
    return ret.get_ui();
}

uint8_t * FileRawBuffer::getBytesFromBufferRandom(ulong n) {
    if (state) {
        ulong p = getRandomPos();
        p = (p + n <= size) ? p : ((p + n) % size);
        unsigned char * ret = new unsigned char[n];
        for (u_int64_t i = p, j = 0; i < p + n; i++, j++) {
            ret[j] = rawBuffer[i];
        }
        return ret;
    } else {
        return NULL;
    }
}

uint8_t * FileRawBuffer::getBytesFromBuffer(ulong n) {
    if (state) {
        if (n + pos <= size) {
            unsigned char * ret = new unsigned char[n];
            for (u_int64_t i = pos, j = 0; i < pos + n; i++, j++) {
                ret[j] = rawBuffer[i];
            }
            pos += n;
            return ret;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

void FileRawBuffer::resetInitialPos() {
    pos = 0;
    if (filestream.is_open()) {
        filestream.seekg(ios::beg);
    }
}

void FileRawBuffer::writeBuffer(char * filename) {
    ofstream file(filename, ios::out | ios::binary);
    file.write((char*) rawBuffer, size);
    file.close();
    pos = 0;
    this->size = size;
}

void FileRawBuffer::setupRNG() {
    gmp_randinit_mt(rng);
    gmp_randseed_ui(rng, chrono.elapsed());
}

void FileRawBuffer::reSeed() {
    gmp_randseed_ui(rng, chrono.elapsed());
}

void FileRawBuffer::initializeReverseTable() {
    if (reverseTable == NULL) {
        reverseTable = new uint8_t[256];
        for (int i = 0; i < 256; i++) {
            reverseTable[i] = reverse(i);
        }
    }
}