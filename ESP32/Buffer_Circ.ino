
#define BUFSIZE 10
typedef struct
{
  char* topic;
  char* msg;
}mensaje;
typedef struct{
  char* buffer[BUFSIZE];
  int bufIN, bufOUT, cont;
  SemaphoreHandle_t mutex = xSemaphoreCreateBinary();
}buffer_circular;

int get_item(char* item, buffer_circular *b)
{
  if(xSemaphoreTake(buffer_circular->mutex,0))
  {
    if(b->cont < 0)
    {
      xSemaphoreGive(buffer_circular->mutex);
      return -1;
    }
    *item = b-> buffer[b->bufOUT % BUFSIZE];
    b->cont = b->cont - 1; 
    b->bufOUT = b->bufOUT + 1;
  }
  xSemaphoreGive(buffer_circular->mutex);
  return 0;
}

int put_item(char item, buffer_circular *b)
{
    if(xSemaphoreTake(buffer_circular->mutex,0))
  {
    if(b->cont >= BUFSIZE)
    {
     xSemaphoreGive(buffer_circular->mutex);
      return -1;
    }
    b-> buffer[b->bufIN % BUFSIZE] = item;
    b->cont = b->cont + 1; 
    b->bufIN = b->bufIN + 1;
  }
  xSemaphoreGive(buffer_circular->mutex);
  return 0;
}
