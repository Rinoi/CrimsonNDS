#include <iostream>
#include <SFML/Graphics.hpp>

#include "SharedPal.hpp"
#include "ImageId.hpp"

int			main(int argc, char **argv)
{
  if (argc < 2)
    {
      std::cerr << argv[0] << " : img.png [...]" << std::endl;
      return (1);
    }

  SharedPal		sharedPal;
  for (int i = 1; i < argc; i += 1)
    {
      // sf::Image		img;
      std::string	name = std::string(argv[i]);
      
      // img.loadFromFile(name);

      // ImageId imgId(img, sharedPal);
      ImageId imgId(name, sharedPal);
      size_t lastindex = name.find_last_of(".");
      std::string rawname;

      if (lastindex != std::string::npos)
	rawname = name.substr(0, lastindex);
      else
	rawname = name;

      imgId.saveH();
      imgId.saveC();
    }
  sharedPal.saveH("pal.h");
  sharedPal.saveC("pal.c");
  return (0);
}
