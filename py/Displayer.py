from os import walk

import pygame
from pygame.locals import *

from GLOBALS import *
from utils import *


class Displayer(object):
    def __init__(self):
        pygame.init()
        pygame.display.set_caption('Game of life')
        # Make screen size a multiple of the tile size
        self.tiles_nbr = Position(WINDOW_WIDTH, WINDOW_HEIGHT) // TILE_SIZE
        self.screen_size = (self.tiles_nbr * TILE_SIZE) + 1
        # Create display
        self.d = pygame.display.set_mode(self.screen_size.get_xy())

    def prepare_draw(self):
        self.d.fill(BLACK)

    def end_draw(self):
        self.draw_grid()
        pygame.display.update()

    def highlight_pos(self, pos):
        pygame.draw.rect(
            self.d, RED,
            pygame.Rect(
                (pos * TILE_SIZE - 0.5 * TILE_SIZE).get_xy(),
                (TILE_SIZE - 1, TILE_SIZE - 1)
            )
        )

    def draw_mouse_square(self, top_left_inter):
        pygame.draw.rect(
            self.d, GREY,
            pygame.Rect(
                ((top_left_inter * TILE_SIZE + 1).get_xy()),
                (TILE_SIZE - 1, TILE_SIZE - 1)
            )
        )
        return top_left_inter

    def get_mouse_events(self):
        pos = Position(*pygame.mouse.get_pos())
        top_left_inter = pos // TILE_SIZE
        # Drawing with mouse
        pressed_mouse_buttons =  pygame.mouse.get_pressed()
        if pressed_mouse_buttons[0]:
            return (top_left_inter, True)
        elif pressed_mouse_buttons[2]:
            return (top_left_inter, False)
        return (top_left_inter, None)

    def draw_map(self, map):
        for y_idx, line in enumerate(map):
            for x_idx, tile in enumerate(line):
                if not tile: continue
                pygame.draw.rect(
                    self.d, WHITE,
                    pygame.Rect(
                        ((Position(x=x_idx, y=y_idx) * TILE_SIZE + 1).get_xy()),
                        (TILE_SIZE - 1, TILE_SIZE - 1)
                    )
                )

    def draw_grid(self):
        for y in range(0, self.screen_size.y, TILE_SIZE):
            pygame.draw.line(self.d, DARK_GREY, (0, y), (self.screen_size.x, y), 1)
        for x in range(0, self.screen_size.x, TILE_SIZE):
            pygame.draw.line(self.d, DARK_GREY, (x, 0), (x, self.screen_size.y), 1)
