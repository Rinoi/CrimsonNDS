#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#pragma once

#define RGB15(r,g,b)  ((r)|((g)<<5)|((b)<<10))

typedef unsigned short u16;
typedef unsigned char uchar;

class SharedPal
{
public:
  
public:
  SharedPal()
  {
    this->maxLen = 256;
    this->palLen = 0;
    // this->pal[0] = (u16)(-1);
    // this->palLen += 1;
  }
  ~SharedPal() = default;

  int			idOf(const sf::Color &color)
  {
    return (this->idOf(ColorToU16(color)));
  }
  
  int			idOf(unsigned short color)
  {
    int			i;
    
    for (i = 0; i < this->palLen; i += 1)
      if (color == this->pal[i])
	return (i);
    if (i < this->maxLen)
      {
	this->pal[i] = color;
	this->palLen += 1;
	return (i);
      }
    return (-1);
  }


  int			nearId(const sf::Color &color)
  {
    return (this->nearId(ColorToU16(color)));
  }

  int			nearId(u16 color)
  {
    u16			r = color << (5 * 0) >> (5 * 2 + 1);
    u16			g = color << (5 * 1) >> (5 * 1 + 1);
    u16			b = color << (5 * 2) >> (5 * 0 + 1);
    int			id = 0;
    int			diff = 1 << 31;
    
    for (int i = 0; i < this->palLen; i += 1)
      {
	int cdiff = abs(r - (this->pal[i] << (5 * 0) >> (5 * 2 + 1))) +
		    abs(g - (this->pal[i] << (5 * 1) >> (5 * 1 + 1))) +
		    abs(b - (this->pal[i] << (5 * 2) >> (5 * 0 + 1)));
	if (cdiff <= diff)
	  {
	    id = i;
	    diff = cdiff;
	  }
      }
    return (id);
  }
  
  void			saveH(const std::string &name)
  {
    std::ofstream	file;
    
    file.open(name);
    file << "#pragma once" << std::endl;
    file << std::endl;
    file << "#define palLen " << (this->palLen * 2) << std::endl;
    file << std::endl;
    file << "extern const unsigned short " << "pal"
	 << '[' << this->palLen << "];" << std::endl;
    file.close();
  }

  void			saveC(const std::string &name)
  {
    std::ofstream	file;
    
    file.open(name);
    file << "const unsigned short " << "pal"
	 << '[' << this->palLen << "] = "<<  std::endl;
    file << "{" << std::endl;
    for (int i = 0; i < this->palLen; i += 1)
      file << "  " << this->pal[i] << ',' << std::endl;
    file << "};" << std::endl;
    file.close();
  }

private:

  u16			ColorToU16(const sf::Color &color) const
  {
    u16			r, g, b;
    u16			c = 0;

    r = ((float)(color.r) / 255.) * 31.;
    g = ((float)(color.g) / 255.) * 31.;
    b = ((float)(color.b) / 255.) * 31.;

    // if ((color.r == 255 && r != 32) ||
    // 	(color.g == 255 && g != 32) ||
    // 	(color.b == 255 && b != 32))
    //   std::cout << "error" << std::endl;

    // if ((color.r == 0 && r != 0) ||
    // 	(color.g == 0 && g != 0) ||
    // 	(color.b == 0 && b != 0))
    //   std::cout << "error" << std::endl;
    // if (color.a > 0)
    //   c += 1;
    // c <<= 1;
    // c += (uchar)(b); c <<= 5;
    // c += (uchar)(g); c <<= 5;
    // c += (uchar)(r);
    return (RGB15(r, g, b));
  }
  
private:
  int			maxLen;
  int			palLen;
  u16			pal[256];
};
