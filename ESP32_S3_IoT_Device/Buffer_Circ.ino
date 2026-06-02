

int get_item(mensaje *item, buffer_circular *b)
{
  if(xSemaphoreTake(b->mutex,0))
  {
    if(b->cont == 0)
    {
      xSemaphoreGive(b->mutex);
      return -1;
    }
    *item = b-> buffer[b->bufOUT % BUFSIZE];
    b->cont = b->cont - 1; 
    b->bufOUT = b->bufOUT + 1;
  }
  xSemaphoreGive(b->mutex);
  return 0;
}

int put_item(mensaje item, buffer_circular *b)
{
    if(xSemaphoreTake(b->mutex,0))
  {
    if(b->cont >= BUFSIZE)
    {
     xSemaphoreGive(b->mutex);
      return -1;
    }
    b-> buffer[b->bufIN % BUFSIZE] = item;
    b->cont = b->cont + 1; 
    b->bufIN = b->bufIN + 1;
  }
  xSemaphoreGive(b->mutex);
  return 0;
}
