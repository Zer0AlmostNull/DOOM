import pygame as pg
from enum import Enum

class Anchor(Enum):
    CENTER = 0
    LEFT = 1

FONT_NAME = "Arial"

# no need to set max size of it (or I hope so)
_fontsize_cache = {}
def find_font_size(text, width, height, font_name: str = FONT_NAME):
    
    # cache section
    cache_tag = str(len(text)) + str(width) + str(height) + font_name

    if cache_tag in _fontsize_cache:
        return _fontsize_cache[cache_tag]


    # calculation
    font_size = 1
    font = pg.font.SysFont(font_name, font_size)
    text_width, text_height = font.size(text)

    while text_width < width and text_height < height:
        font_size += 1
        font = pg.font.SysFont(font_name, font_size)
        text_width, text_height = font.size(text)

    font_size -= 1

    _fontsize_cache[cache_tag] = font_size
    return font_size

    

def render_surface_text(text, width, height, \
                        font_size, text_color, background_color:tuple|None, \
                        font_name = FONT_NAME, bold: bool = False) -> pg.Surface:
        # create surface with background color
        surface = pg.Surface((width, height),pg.SRCALPHA,)
        
        if background_color!= None:
            surface.fill(background_color)

        font = pg.font.SysFont(font_name, font_size)
        text_surface = font.render(text, True, text_color)

        text_x = (width - text_surface.get_width()) // 2
        text_y = (height - text_surface.get_height()) // 2

        # blit text into created surface
        surface.blit(text_surface, (text_x, text_y))

        return surface

class UIElement:
    x: float
    y: float
    height: float
    width: float
    anchor: Anchor

    def get_rect(self)->pg.Rect:
        return pg.Rect(self.x,self.y, self.width, self.height)

    def rerender_internal():
        pass

    def draw(self, screen: pg.Surface, displacement=(0, 0)):
        """
        Draws the UI element on the given screen surface.

        Args:
            screen (pg.Surface): The surface on which the UI element will be drawn.
            displacement (tuple, optional): The displacement of the UI element from its original position. Defaults to (0, 0).
        """

        pass

    def update(self, events, mouse_pos=(-1, -1)):
        pass