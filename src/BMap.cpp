#include "BMap.hpp"
#include <cstdio>

BMap::BMap(const vec2 &blockSize, const vec2 &size, bool alloc)
{
  this->blockSize = blockSize;
  this->size = size;
  this->alloc = alloc;
  this->data = NULL;
  if (alloc == true)
    this->data = newData();
}

BMap::BMap(const vec2 &blockSize, const vec2 &size, u16 *data)
{
  this->blockSize = blockSize;
  this->size = size;
  this->alloc = false;
  this->data = data;
}

BMap::~BMap()
{
  if (this->alloc == true)
    delete[] this->data;
}

//get

u16		BMap::get(int x, int y, int bMap) const
{
  return (this->data[this->getIdx(x, y, bMap)]);
}

u16		BMap::get(const vec2 &vec, int bMap) const
{
  return (this->get(vec.x, vec.y, bMap));
}

u16		BMap::get(int x, int y) const
{
  return (this->data[this->getIdx(x, y)]);
}

u16		BMap::get(const vec2 &vec) const
{
  return (this->get(vec.x, vec.y));
}

BMap::d_map	BMap::getMap(int bMap) const
{
  BMap::d_map	map(this->blockSize, this->data +
		    (bMap * this->blockSize.x * this->blockSize.y));

  return (map);
}

BMap::d_map	BMap::getMap(int x, int y) const
{
  int		bMap = y * this->size.x + x;

  return (this->getMap(bMap));
}

BMap::d_map	BMap::getMap(const vec2 &vec) const
{
  return (this->getMap(vec.x, vec.y));
}


BMap::d_map	*BMap::newMap(u16 *data)
{
  if (data == NULL)
    return (new BMap::d_map(this->blockSize));
  else
    return (new BMap::d_map(this->blockSize, data));    

}

void		BMap::setMap(int bMap, u16 *data)
{
  dmaCopy(data,
	  this->data + (bMap * this->blockSize.x * this->blockSize.y),
	  this->blockSize.x * this->blockSize.y * sizeof(u16));
}

void		BMap::copyMap(int from, int to)
{
  dmaCopy(this->data + (from * this->blockSize.x * this->blockSize.y),
	  this->data + (to * this->blockSize.x * this->blockSize.y),
	  this->blockSize.x * this->blockSize.y * sizeof(u16));  
}

void		BMap::swapMap(int from, int to)
{
  d_map		*tmp = this->newMap();

  //copy tmp
  dmaCopy(this->data + (to * this->blockSize.x * this->blockSize.y),
	  tmp->data,
	  this->blockSize.x * this->blockSize.y * sizeof(u16));  


  //erase
  dmaCopy(this->data + (from * this->blockSize.x * this->blockSize.y),
	  this->data + (to * this->blockSize.x * this->blockSize.y),
	  this->blockSize.x * this->blockSize.y * sizeof(u16));  
  //get tmp
  dmaCopy(tmp->data,
	  this->data + (from * this->blockSize.x * this->blockSize.y),
	  this->blockSize.x * this->blockSize.y * sizeof(u16));  

  delete tmp;
}

//set

void		BMap::set(int x, int y, u16 v, int bMap)
{
  this->data[this->getIdx(x, y, bMap)] = v;
}

void		BMap::set(int x, int y, u16 v)
{
  this->data[this->getIdx(x, y)] = v;
}

void		BMap::init(u16 v)
{
  dmaFillHalfWords(v, this->data,
		   (this->blockSize.x * this->blockSize.y)
		   * (this->size.x * this->size.y)
		   * sizeof(u16));
}

void		BMap::init(u16 v, int bMap)
{
  dmaFillHalfWords(v,
		   this->data
		   + bMap * this->blockSize.x * this->blockSize.y,
		   (this->blockSize.x * this->blockSize.y)
		   * sizeof(u16));

}

int		BMap::getIdx(int x, int y) const
{
  x %= this->blockSize.x * this->size.x;
  y %= this->blockSize.y * this->size.y;
  
  int		bX = x / this->blockSize.x;
  int		bY = y / this->blockSize.y;
  int		bMap = bY * this->size.x + bX;
  
  x = x % this->blockSize.x;
  y = y % this->blockSize.y;
  // printf("%p %d\n", this, this->blockSize.y);
  return (this->getIdx(x, y, bMap));
}

int		BMap::getIdx(int x, int y, int bMap) const
{
  x %= this->blockSize.x * this->size.x;
  y %= this->blockSize.y * this->size.y;
  int		i = y * this->blockSize.x + x;

  i += bMap * this->blockSize.x * this->blockSize.y;
  // printf("%d\n", bMap);
  // printf("%d %d i = %d\n", x, y, i);
  return (i);
}

u16		*BMap::newData() const
{
  u16		*data;

  data = new u16[(this->blockSize.x * this->blockSize.y) *
		 (this->size.x * this->size.y)];
  return (data);
}
