#pragma once

#include <nds.h>
#include "SpriteSheet.hpp"
#include "TBackground.hpp"
#include "BMap.hpp"

class TBackground2 : public TBackground{
    private:

     u16 *maps[];

    public:

    TBackground2(const Type &type, BgSize size, SpriteSheet *spriteSheet, int depth = 0, u16 *maps[] = nullptr);
    virtual ~TBackground2();

    public:
    void changeMap(int &bmap);
}