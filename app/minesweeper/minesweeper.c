#include <mock.h>

int main(void)
{
  game_t *game = mock_game_new(3, 3, 2);

  mock_game_dump(game);

  mock_game_destroy(game);
  return 0;
}
