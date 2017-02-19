template <typename T>
bool Buffer::initialize(const std::vector<T>& data,
                        BufferType type,
                        BufferMode mode)
{
    bool ret = initialize();
    if (ret)
        bufferData<T>(data, type, mode);
    return ret;
}

template <typename T>
uint32_t Buffer::bufferData(const std::vector<T>& data,
                            BufferType t, BufferMode m)
{
    if (identifier == 0)
        return 0;

    if (t == ArrayBuffer)
        type = GL_ARRAY_BUFFER;
    else
        type = GL_ELEMENT_BUFFER;
    if (m == Static)
        mode = GL_STATIC_DRAW;
    else if (m == Dynamic)
        mode = GL_DYNAMIC_DRAW;
    // else
        // mode = GL_STREAM_DRAW;
    else
        return 0;

    glBindBuffer(type, identifier);
    glBufferData(type, VECTOR_ARRAY_SIZE(data), &data.front(), mode);
    glBindBuffer(type, 0);

    return identifier;
}
