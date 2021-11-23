#pragma once
#include "Object.h"
#include <string>

class AudioObject :
    public Object
{
public:
    AudioObject();
    AudioObject(std::string audioSourcePath);
    ~AudioObject();
    bool Initialize();
    void PlayAudio();
    friend class Game;
    friend class BaseApp;
    friend class UIComponent;
    class AudioSourceComponent* audioSource;
};

