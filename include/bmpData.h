#ifndef __BMB__
#define __BMB__

typedef struct s_bmp
{
  unsigned char header[54];
  unsigned int  dataPos;
  unsigned int  width;
  unsigned int  height;
  unsigned int  imageSize;
  unsigned char *data;
} t_bmp;

#endif 
