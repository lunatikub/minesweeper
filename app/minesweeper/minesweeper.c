#include <stdio.h>

#include <mock.h>

static inline void game_inputs(struct coord *to_play, enum action *action)
{
  char c;
  printf("[x] [y] [action] (flag:F, unflag:U, set empty: E) ?\n");
  scanf("%u %u %c", &to_play->x, &to_play->y, &c);
  switch (c) {
    case 'F':
      *action = FLAG;
      break;
    case 'U':
      *action = UNFLAG;
      break;
    case 'E':
    default:
      *action = SET_EMPTY;
  };
  printf("\n");
}

int main(void)
{
  struct coord to_play;
  enum action action;
  enum ret ret;

  game_t *game = mock_game_new(5, 5, 4);

  do {
    mock_game_dump(game);
    game_inputs(&to_play, &action);
    ret = mock_game_play(game, action, &to_play);
  } while (ret == OK);

  printf("!!!!!!!!!!!!\n!!! %s !!!\n!!!!!!!!!!!!\n", ret == WON ? "WON" : "LOST");
  mock_game_dump_solution(game);

  mock_game_destroy(game);
  return 0;
}
