import pygame as pg
from pygame import Surface
from ui_element import *
from typing import Callable

class UISlider(UIElement):
    def __init__(self, 
                 pos_x, pos_y, width, height, 
                 value_setter: Callable, 
                 min_value: float = 0, max_value: float = 100, start_value: float = 0.5,
                 round_func: Callable = lambda x: round(x, 2), 
                 bar_color: tuple = (255,255,255), handle_color: tuple = (40, 40, 40),
                 handle_size: int = 10,
                 background_color: tuple | None = None, 
                 anchor: Anchor = Anchor.CENTER):
        super().__init__()
        self.x = pos_x
        self.y = pos_y

        self.width = width
        self.height = height
        self.handle_size = handle_size
        self.anchor = anchor

        self.min_value = min_value
        self.max_value = max_value
        self._floatValue = start_value 
        self.round_function = round_func

        self.value_setter = value_setter
        self.bar_color = bar_color
        self.handle_color = handle_color
        self.background_color = background_color

        self.surface = pg.Surface((width,height), pg.SRCALPHA)

        # mouse section
        self.mouse_down = False


    @property
    def dx(self):
        return self._floatValue * self.width

    @property
    def handle_rect(self):
        return pg.Rect(self._floatValue * self.width - self.handle_size//2,0, self.handle_size, self.height)
    
    def apply_value(self):
        self.value_setter(
            self.round_function(
                self.min_value + (self.max_value-self.min_value) * self._floatValue
                )
            )

    def update(self, events, mouse_pos):
        # parse events
        for e in events:
            if e.type == pg.MOUSEBUTTONDOWN and e.button == 1:
                self.mouse_down = True
            elif e.type == pg.MOUSEBUTTONUP and e.button == 1:
                self.mouse_down = False
        # if handle is draged
        if self.mouse_down and pg.Rect(0,0,self.width, self.height).collidepoint(*mouse_pos):
            # update self._floatValue
            self._floatValue = mouse_pos[0]/self.width
            # clamp float valu between <0,1>
            self._floatValue = max(0, min(self._floatValue, 1))
            # aply value to original variable
            self.apply_value()

    def draw(self, screen: Surface, displacement = (0,0)) -> None:
        self.surface.fill(self.background_color)

        # draw fill
        pg.draw.rect(self.surface, self.bar_color, (0,0, self.dx, self.height))

        # draw handle
        pg.draw.rect(self.surface,self.handle_color, self.handle_rect)
        screen.blit(self.surface, (self.x + displacement[0], self.y + displacement[1]))
