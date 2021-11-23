#pragma once
#include "../BaseApp/BaseApp.h"
#include "../../Graphics/VertexArray.h"
#include <vector>
class KuraArtApp :
    public BaseApp
{
public:
    KuraArtApp();
    ~KuraArtApp();
    void Start()  override;
    void Update()  override;
    void Timeline(class TimelineObject* timelineObj)  override;
};

