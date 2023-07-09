import pygame as pg
from pygame import Surface
from ui_element import *
from typing import Callable

class UILabel(UIElement):
    def __init__(self, \
                 pos_x, pos_y, width, height, \
                 text: Callable| str, \
                 text_color = (255,255,255), background_color: tuple | None = None, \
                 font_name = FONT_NAME,
                 anchor: Anchor = Anchor.CENTER):
        super().__init__()
        self.x = pos_x
        self.y = pos_y

        self.width = width
        self.height = height

        self.text = text
        self.font_name = font_name
        self.anchor = anchor
        self.text_color = text_color
        self.background_color = background_color
        
        self.surface: pg.Surface

        self._generate_surface()
        self.rect = self.surface.get_rect()
    

    def _generate_surface(self):
        _text = str(self.text() if callable(self.text) else self.text)

        font_size = find_font_size(_text, self.width, self.height, self.font_name)
        self.surface = render_surface_text(_text, self.width, self.height, font_size,
                                                   self.text_color, self.background_color, font_name= self.font_name)
        
    def update(self, events, mouse_pos):
        if callable(self.text):
            self._generate_surface()

        

    def draw(self, screen: Surface, displacement = (0,0)) -> None:
        screen.blit(self.surface, (self.x + displacement[0], self.y + displacement[1]))
