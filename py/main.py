#!/usr/bin/env python3
import sys
import time
import pickle

import pygame

from Displayer import *
from GLOBALS import *


class GoL(object):
    def __init__(self):
        self.displayer = Displayer()
        self.map = []
        self.init_map()
        self.is_running = False

    def launch(self):
        clock = pygame.time.Clock()
        while 42:
            clock.tick(60)
            for event in pygame.event.get():
                if event.type == QUIT:
                    pygame.quit()
                    sys.exit()
            self.displayer.prepare_draw()
            # Handle pause / play
            keys = pygame.key.get_pressed()
            if keys[K_RETURN]:
                self.is_running = not self.is_running
            # Handle cells drawing
            mouse_pos, mouse_event = self.displayer.get_mouse_events()
            if not self.is_oob(mouse_pos):
                self.displayer.draw_mouse_square(mouse_pos)
                if mouse_event is not None:
                    self.map[mouse_pos.y][mouse_pos.x] = mouse_event
            # Update if needed
            if self.is_running:
                self.update_map()
            # Finish drawing
            self.displayer.draw_map(self.map)
            self.displayer.end_draw()

    def update_map(self):
        tmp_map = []
        # Create working copy
        for line in range(self.displayer.tiles_nbr.y):
            tmp_map.append([False] * self.displayer.tiles_nbr.x)

        for y_idx, line in enumerate(self.map):
            for x_idx, tile in enumerate(line):
                pos = Position(y=y_idx, x=x_idx)
                alive_neighbors_count = self.get_alive_neighbors_count(pos)
                if alive_neighbors_count == 3:  # Born
                    tmp_map[pos.y][pos.x] = True
                elif alive_neighbors_count == 4:  # Do nothing
                    tmp_map[pos.y][pos.x] = tile
                else:
                    tmp_map[pos.y][pos.x] = False
        self.map = tmp_map

    def get_alive_neighbors_count(self, pos):
        count = 0
        for y_idx in range(pos.y - 1, pos.y + 2):
            for x_idx in range(pos.x - 1, pos.x + 2):
                tmp_pos = Position(y=y_idx, x=x_idx)
                if not self.is_oob(tmp_pos) and self.map[tmp_pos.y][tmp_pos.x]:
                    count += 1
        return count

    def init_map(self):
        for line in range(self.displayer.tiles_nbr.y):
            self.map.append([False] * self.displayer.tiles_nbr.x)

    def is_oob(self, pos):
        return pos < Position(0, 0) or pos.x > self.displayer.tiles_nbr.x - 1 or pos.y > self.displayer.tiles_nbr.y - 1


if __name__ == '__main__':
    app = GoL()
    app.launch()
