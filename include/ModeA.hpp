#pragma once

#include "IGraphicMode.hpp"

//MODE : A
//BG 0/1 => TILES MAP 256*256 X4
//BG 2 => consolle text (for printf)

class	ModeA : public IGraphicMode
{
public:
  ModeA() = default;
  ~ModeA() = default;

  bool	run()
  {
    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);
    
    vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
    vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
    vramSetBankC(VRAM_C_SUB_BG_0x06200000);
    vramSetBankD(VRAM_D_SUB_SPRITE);
    vramSetBankE(VRAM_E_BG_EXT_PALETTE);
    vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
    vramSetBankG(VRAM_G_LCD);
    vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
    vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);
    
    //MAIN
    videoSetMode(MODE_3_2D);

    bgInit(0, BgType_Text8bpp, BgSize_T_512x512, 7, 5);
    bgHide(0 + 0);
    
    bgInit(1, BgType_Text8bpp, BgSize_T_512x512, 3, 5);
    bgHide(0 + 1);
    
    consoleInit(&cMain, 2, BgType_Text4bpp, BgSize_T_256x256, 2, 0, true, true);
    // bgHide(0 + 2);
    
    bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 2, 0);
    bgHide(0 + 3);

    //SUB	
    bgInitSub(0, BgType_Text8bpp, BgSize_T_512x512, 7, 5);
    bgHide(4 + 0);

    bgInitSub(1, BgType_Text8bpp, BgSize_T_512x512, 3, 5);
    bgHide(4 + 1);

    consoleInit(&cSub, 2, BgType_Text4bpp, BgSize_T_256x256, 2, 0, false, true);
    // bgHide(4 + 2);

    bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 2, 0);
    bgHide(4 + 3);

    return (true);
  }

  void		startUpdate()
  {
    // consoleSelect(&this->cSub);
    // consoleClear();
  }

  void		endUpdate()
  {

  }
  
  PrintConsole	cMain;
  PrintConsole	cSub;
};
