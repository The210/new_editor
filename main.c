#include "doom.h"

int main(int argc, char **argv)
{
  t_map map;
  t_wind wind;

  if (argc != 2)
    return (0);
  map = read_values(argv[1]);
  wind = init_wind(wind);
  while(1)
  {
    if (check_key_pres(wind, &ctrl, msbutton) == 0)
      return(0);
    else if (wind.event.type == SDL_MOUSE_BUTTONDOWN)
    {
      if (wind,event.key.keysym.sym == SDL_BUTTON_LEFT)
        mouse_up_left();
    }
    
  }
}
