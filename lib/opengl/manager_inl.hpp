template <class ContainerType>
buffer_t GLManager::createArrayBuffer(const ContainerType& data, DrawMethod d)
{
    buffer_t b = createBuffer();
    bufferArrayData(b, data, d);
    return b;
}

template <typename T>
buffer_t GLManager::createArrayBuffer(const T data[], size_t size, DrawMethod d)
{
    buffer_t b = createBuffer();
    bufferArrayData(b, data, size, d);
    return b;
}

template <class ContainerType>
buffer_t GLManager::createElementBuffer(const ContainerType& data, DrawMethod d)
{
    buffer_t b = createBuffer();
    bufferElementData(b, data, d);
    return b;
}

template <typename T>
buffer_t GLManager::createElementBuffer(const T data[], size_t size, DrawMethod d)
{
    buffer_t b = createBuffer();
    bufferElementData(b, data, size, d);
    return b;
}

template <class ContainerType>
void GLManager::bufferArrayData(buffer_t buffer, const ContainerType& data,
                                DrawMethod d)
{
    bufferArrayData(buffer, data.data(), data.size() * sizeof(data.front()), d);
}

template <typename T>
void GLManager::bufferArrayData(buffer_t buffer, const T data[], size_t size,
                                DrawMethod d)
{
    bindArrayBuffer(buffer);
    bufferData(data, size, BufferType::Array, d);
    unbindArrayBuffer();
}

template <class ContainerType>
void GLManager::bufferElementData(buffer_t buffer, const ContainerType& data,
                                  DrawMethod d)
{
    bufferElementData(buffer, data.data(), data.size() * sizeof(data.front()), d);
}

template <typename T>
void GLManager::bufferElementData(buffer_t buffer, const T data[], size_t size,
                                  DrawMethod d)
{
    bindElementBuffer(buffer);
    bufferData(data, size, BufferType::Element, d);
    unbindElementBuffer();
}
