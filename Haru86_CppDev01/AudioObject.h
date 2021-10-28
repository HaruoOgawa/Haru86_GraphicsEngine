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
    friend class Game;
    friend class UIComponent;
private :
    class AudioSourceComponent* audioSource;
};

