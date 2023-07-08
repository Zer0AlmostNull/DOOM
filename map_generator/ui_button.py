import pygame as pg
from pygame import Surface
from ui_element import *


    

class UIButton(UIElement):
    def __init__(self, \
                 pos_x, pos_y, width, height, \
                 text, \
                 text_color = (255,255,255), background_color = (40,40,40), \
                 text_color_highlighted = (200,200,200), background_color_highlighted = (60,60,60), \
                 font_name = FONT_NAME,
                 onclick = None,\
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

        self.text_color_h = text_color_highlighted
        self.background_color_h = background_color_highlighted

        self.onclick = onclick
        
        self.normal_surface = None
        self.highlighted_surface = None
        self.normal_rect = None
        self.highlighted_rect = None


        self.mouse_over = False

        self._generate_surfaces()
    
    @property
    def image(self):
        return self.highlighted_surface if self.mouse_over else self.normal_surface
    
    @property
    def rect(self):
        return self.highlighted_rect if self.mouse_over else self.normal_rect

    def _generate_surfaces(self):
        font_size = find_font_size(self.text, self.width, self.height, self.font_name)
        
        self.normal_surface = render_surface_text(self.text, self.width, self.height, font_size,
                                                   self.text_color, self.background_color, font_name= self.font_name)
        
        self.highlighted_surface = render_surface_text(self.text, self.width, self.height, font_size, 
                                                   self.text_color_h, self.background_color_h, font_name= self.font_name)

        self.normal_rect = self.normal_surface.get_rect()
        self.highlighted_rect = self.highlighted_surface.get_rect()

    def update(self, events, mouse_pos):
        # check if mouse is over
        if self.rect.collidepoint(mouse_pos):
            self.mouse_over = True

            # if is over 
            # search for mouse up - button was clicked
            mouse_up = False
            for e in events:
                if e.type == pg.MOUSEBUTTONUP and e.button == 1:
                    mouse_up = True
                    break
            # then perform the action
            if mouse_up and self.onclick != None:
                self.onclick()

        else:
            self.mouse_over = False
            
        return self.mouse_over

    def draw(self, screen: Surface, displacement = (0,0)):
        screen.blit(self.image, (self.x + displacement[0], self.y+ displacement[1]))
