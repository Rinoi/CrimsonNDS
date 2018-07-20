#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "SharedPal.hpp"

typedef unsigned int uint;

class SharedPal;

class ImageId
{
public:
  ImageId(const sf::Image &img, SharedPal &sharedPal)
  {
    this->data.reserve(img.getSize().x * img.getSize().y);
    this->action(img, sharedPal);
  }

  ImageId(const std::string &name, SharedPal &sharedPal)
  {
    sf::Image	img;
    
    img.loadFromFile(name);
    this->getRealName(name);
    
    this->data.reserve(img.getSize().x * img.getSize().y);
    this->action(img, sharedPal);
  }
  
  ~ImageId() = default;

private:

  std::string		getRealName(const std::string &name)
  {
    size_t		lastindex;

    this->name = name;
    lastindex = this->name.find_last_of(".");

    if (lastindex != std::string::npos)
      this->name = this->name.substr(0, lastindex);
    return (this->name);
  }
  
  void			action(const sf::Image &img, SharedPal &sharedPal)
  {
    const int		h = 2;
    const int		w = 2;

    //GRIT
    for (uint g_y = 0; g_y < img.getSize().y / (8 * h); g_y += 1)
      for (uint g_x = 0; g_x < img.getSize().x / (8 * w); g_x += 1)
	// each SQUARE OF 8
	for (uint s_y = 0; s_y < h; s_y += 1)
	  for (uint s_x = 0; s_x < w; s_x += 1)
	    // each pixel
	    for (uint p_y = 0; p_y < 8; p_y += 1)
	      for (uint p_x = 0; p_x < 8; p_x += 1)
		{
		  uint	x = g_x * 8 * w + s_x * 8 + p_x;
		  uint	y = g_y * 8 * h + s_y * 8 + p_y;
		  int	id = sharedPal.idOf(img.getPixel(x, y));

		  if (id != -1)
		    data.push_back(id);
		  else
		    data.push_back(sharedPal.nearId(img.getPixel(x, y)));
		}
  }

  // void			action(const sf::Image &img, SharedPal &sharedPal)
  // {
  //   const int		h = 16;
  //   const int		w = 16;
  //   int			i = 0;
  //   int			size = img.getSize().x * img.getSize().y;
    
  //   while (i < size)
  // 	{
  	  // int x = (i % w + w * (i / (w * h))) % img.getSize().x;
  	  // int y = (i / h) % w + h * (i / (img.getSize().x * h));
  // 	  int id = sharedPal.idOf(img.getPixel(x, y));

  // 	  // std::cout << i << " " << x << " " << y << std::endl;
  // 	  if (id != -1)
  // 	    data.push_back(id);
  // 	  else
  // 	    data.push_back(sharedPal.nearId(img.getPixel(x, y)));
  // 	  // std::cout << i << " " << this->data.size() << " " << data[i] << std::endl;
  // 	  i += 1;
  // 	}

  // }

  // void			action(const sf::Image &img, SharedPal &sharedPal)
  // {
  //   int			i = 0;

  //   std::fill(this->data.begin(), this->data.end(), -1);
  //   for (unsigned int	y = 0; y < img.getSize().y; y += 1)
  //     for (unsigned int	x = 0; x < img.getSize().x; x += 1)
  // 	{
  // 	  int id = sharedPal.idOf(img.getPixel(x, y));

  // 	  if (id != -1)
  // 	    data.push_back(id);
  // 	  else
  // 	    data.push_back(sharedPal.nearId(img.getPixel(x, y)));
  // 	  // std::cout << i << " " << this->data.size() << " " << data[i] << std::endl;
  // 	  i += 1;
  // 	}

  // }

public:

  void			saveH()
  {
    return (this->saveH(this->name + ".h"));
  }

  void			saveH(const std::string &name)
  {
    std::ofstream	file;

    file.open(name);
    file << "#pragma once" << std::endl;
    file << std::endl;
    file << "#define\t\t\t\t" << this->name << "TilesLen " << this->data.size() << std::endl;
    file << std::endl;
    file << "extern const unsigned char\t" << this->name << "Tiles" 
	 << '[' << this->data.size() << "];" << std::endl;
    file.close();
  }

  void			saveC()
  {
    return (this->saveC(this->name + ".c"));
  }

  void			saveC(const std::string &name)
  {
    std::ofstream	file;

    file.open(name);
    file << "const unsigned char " << this->name << "Tiles"
	 << '[' << this->data.size() << "] =" << std::endl;
    file << '{' << std::endl;
    for (int i : this->data)
      {
	file << "  " << i << "," << std::endl;
      }
    file << "};" << std::endl;
    file.close();
  }


  const std::string	getName() const
  {
    return (this->name);
  }
  
private:
  std::string		name;
  int			size;
  std::vector<int>	data;
};
