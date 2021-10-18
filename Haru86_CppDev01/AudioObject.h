#pragma once
#include "Object.h"
class AudioObject :
    public Object
{
public:
    AudioObject();
    ~AudioObject();
    bool Initialize();
    void PlayAudio();
private :
    class AudioSourceComponent* audioSource;
};

