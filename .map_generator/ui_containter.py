import pygame as pg
from pygame import Surface
from ui_element import *

class UIContainer(UIElement):
    def __init__(self, \
                 pos_x, pos_y, width, height, \
                 padding: tuple[int,int] = (10,10), background_color = (0,0,0,0),
                 anchor: Anchor = Anchor.CENTER,
                 content: list[UIElement] = []): 
        super().__init__()
        self.x = pos_x
        self.y = pos_y

        self.width = width
        self.height  = height
        
        self.actual_height = sum([obj.height for obj in content]) + padding[1]
        self.padding = padding
        self.background_color = background_color
        self.anchor = anchor

        self.dy = 0
        self.max_dx = abs(self.actual_height - self.height)

        self.content = content

        self.visible_surface: pg.Surface

        self._generate_surface()
    

    def _generate_surface(self):
        # create curface
        self.visible_surface = pg.Surface((self.width, self.height))

        # set proper ui elements positions
        y = self.padding[1]
        for obj in self.content:
            if obj.anchor == Anchor.CENTER:
                obj.x = (self.width - obj.width)//2
            elif obj.anchor == Anchor.LEFT:
                obj.x = self.padding[0]

            obj.y = y

            y += obj.height + self.padding[1]

    def update(self, events, mouse_pos):
        # update objects
        for obj in self.content:
            obj.update(events, (mouse_pos[0] - self.x - obj.x, mouse_pos[1] - self.y - self.dy-obj.y))

        # check collision with ui
        return super().update(events, mouse_pos)

    def draw(self, screen: Surface):
        # draw surface again (with updated ui)
        self.visible_surface.fill(self.background_color)

        for obj in self.content:
            obj.draw(self.visible_surface, (0, self.dy))

        screen.blit(self.visible_surface, (self.x, self.y))
