#pragma once

#ifndef VERTEXBUFFEROBJECT_H_
#define VERTEXBUFFEROBJECT_H_

class VertexBufferObject
{
public:
    void createVBO(size_t reserveSizeBytes = 0);
    void bindVBO(GLenum bufferType = GL_ARRAY_BUFFER);
    void addRawData(const void* ptrData, size_t dataSizeBytes, size_t repeat = 1);
    template<typename T>
    void addData(const T& ptrObj, size_t repeat = 1)
    {
        addRawData(&ptrObj, static_cast<size_t>(sizeof(T)), repeat);
    }
    void* getRawDataPointer();
    void uploadDataToGPU(GLenum usageHint);
    void* mapBufferToMemory(GLenum usageHint) const;
    void* mapSubBufferToMemory(GLenum usageHint, size_t offset, size_t length) const;
    void unmapBuffer() const;
    GLuint getBufferID() const;
    size_t getBufferSize();
    void deleteVBO();

private:
    GLuint bufferID_{ 0 };
    GLenum bufferType_{ 0 };

    vector<unsigned char> rawData_;
    size_t bytesAdded_{ 0 };
    size_t uploadedDataSize_{ 0 };

    bool isBufferCreated() const;
    bool isDataUploaded() const;

};

#endif // !VERTEXBUFFEROBJECT_H_
