import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"

import pygame as pg

from math import sqrt

from wall import *
from settings import *

from ui_element import *
from ui_button import *
from ui_label import *
from ui_containter import *
from ui_slider import *


font_arial20: pg.font.Font

class Application:
    def __init__(self, screen) -> None:

        self.wall_collection: list[Wall] = []
        self.ui_elements : list[UIElement] = []
        self.selected_vert_index = None

        self.ui_elements = [
            UIButton(0, 0, 100, 20,'Create wall', background_color = (255,0,0)),
            ]

        self.screen: pg.Surface = screen

        self.map_displacement: tuple[float, float] = (50, 50) # px units
        
        self.selected_wall_ui_index: None | int = None
        self.selected_wall_index: None | int = None

        # create background grid
        self.grid_background = pg.Surface((WND_WIDTH + GRID_CELL_UNIT_SIZE * MAP_SCALE * 2, WND_HEIGHT + GRID_CELL_UNIT_SIZE * MAP_SCALE*2))
        self.grid_background.fill(BACKGROUND_COLOR)

        for x in range(0,WND_WIDTH + GRID_CELL_PX_SIZE * 2 + 1 , GRID_CELL_PX_SIZE):
            for y in range(0, WND_HEIGHT + GRID_CELL_PX_SIZE * 2 + 1 , GRID_CELL_PX_SIZE):
                pg.draw.circle(self.grid_background, GRID_COLOR, (x, y), GRID_DOT_RADIUS_PX)

        # store mouse state
        self.prev_mouse_x = 0
        self.prev_mouse_y = 0
        self.mouse_delta_x = 0 
        self.mouse_delta_y = 0

        self.mouse_moving = False
        self.mouse1_clicked =  False
        self.mouse1_down = False


        # TEST VARS
        self.test_variable = 0
    
    @property
    def is_wall_selected(self) -> bool:
        return self.selected_wall_index != None

    @property
    def is_cursor_on_ui(self) -> bool:
        mx, my = pg.mouse.get_pos()

        is_on_ui = False
        for obj in self.ui_elements:
            is_on_ui = is_on_ui | pg.Rect(obj.x, obj.y, obj.width, obj.height).collidepoint(mx, my)

            if is_on_ui:
                break
        return is_on_ui
       
    def load_data(self, path = './map.data') -> None:
        '''Loads data from file to `wall_collection`. Beware that `wall_collection` is cleared before.'''

        # check if file exists
        if not os.path.exists(path) or not os.path.isfile(path):
            print(f'File "{path} does not exists!"')
            return -1 

        # open file
        with open(path, 'r', encoding = 'utf-8') as file:
            # read line by line
            for line in file.readlines():

                # pass by endlines
                if line == '\n':
                    continue

                ax, ay, bx, by, color = line.split(' ')

                # convert numbers to flaot
                ax, ay, bx, by = map(float, (ax, ay, bx, by))

                # parse color
                color = color[2:]
                color = int(color, 16)

                red = (color >> 24) & 0xFF
                green = (color >> 16) & 0xFF
                blue = (color >> 8) & 0xFF
                alpha = color & 0xFF

                color = (red, green, blue, alpha)
                self.wall_collection.append(Wall((ax, ay), (bx, by), color))

    def save_data(self, path = './map.data') -> None:

        # open file
        with open(path, 'w', encoding = 'utf-8') as file:
            # write each wall to file 
            for wall in self.wall_collection:
                ax, ay = wall.a.x, wall.a.y
                bx, by = wall.b.x, wall.b.y
                rgba_value = (wall.color[0] << 24) | (wall.color[1] << 16) | (wall.color[2] << 8) | wall.color[3]

                file.write(f'{ax} {ay} {bx} {by} 0x{rgba_value:08X}\n')

    def units_to_pixels(self, point: tuple[float, float]) -> tuple[float, float]:
        return (point[0] * MAP_SCALE + self.map_displacement[0],  
                (WND_HEIGHT - point[1] * MAP_SCALE) - self.map_displacement[1])

    def pixels_to_units(self, point: tuple[float, float]) -> tuple[float, float]:
        return ((-self.map_displacement[0] + point[0]) / MAP_SCALE,
                (WND_HEIGHT - point[1] - self.map_displacement[1]) / MAP_SCALE)

    def draw_walls(self) -> None:
        # draw each wall
        for wall in self.wall_collection:
            if not self.wall_collection.index(wall) == self.selected_wall_index:
                pg.draw.line(self.screen,
                            wall.color,
                            self.units_to_pixels(wall.a), 
                            self.units_to_pixels(wall.b), 
                            1)
            else: # draw selected wall
                pg.draw.line(self.screen,
                            wall.color,
                            self.units_to_pixels(wall.a), 
                            self.units_to_pixels(wall.b), 
                            SELECTED_WALL_WIDTH)
                
                # draw enpoints
                for point in [wall.a, wall.b]:
                    pg.draw.circle(self.screen,
                               wall.color,
                               self.units_to_pixels(point),
                               SELECTED_POINT_R_PX)
                
                # draw border of selected point
                if self.selected_vert_index != None:
                    
                    p = [wall.a, wall.b][self.selected_vert_index]

                    pg.draw.circle(self.screen,
                               (255,255,255),
                               self.units_to_pixels(p),
                               SELECTED_POINT_R_PX+1,
                               width = 1)
                
    def get_intersected_wall_index(self) -> None | int:
        mouse_px, mouse_py = pg.mouse.get_pos()
        mouse_ux, mouse_uy = self.pixels_to_units((mouse_px, mouse_py))
        
        # find wall that collides with mouse radius
        for wall in self.wall_collection:

            A, B, C = wall.get_equation()
            # calculate distance from line
            d = abs(A * mouse_ux + B * mouse_uy + C)\
                    / sqrt(A ** 2 + B ** 2)
            
            # calculate distance from section center
            c_d = sqrt((mouse_ux - wall.S[0])**2 + (mouse_uy - wall.S[1])**2 )

            # if its collision
            if d < CURSOR_RADIUS_UNITS and c_d < wall.length/2+CURSOR_RADIUS_UNITS:
                return self.wall_collection.index(wall)
            
        return None

    def select_wall(self, index) -> None:

        # if some wall is already selected unselect it
        if self.is_wall_selected:
            self.unselect_wall()
        self.selected_wall_index = index
        # getters
        def color_getter():
            return f'color: {self.wall_collection[index].color}'

        # setters
        def r_setter(x):
            t = self.wall_collection[index].color
            self.wall_collection[index].color = (x, t[1], t[2])

        def g_setter(x):
            t = self.wall_collection[index].color
            self.wall_collection[index].color = (t[0], x, t[2])

        def b_setter(x):
            t = self.wall_collection[index].color
            self.wall_collection[index].color = (t[0], t[1], x)

        # create info ui
        W, H = 100, 300
        PADDING = 20

        SLIDER_H = 10
        SLIDER_HANDLE_SIZE = 10

        ui_element = UIContainer(WND_WIDTH-W-PADDING, PADDING, W,H, background_color = (60,60,60),padding=(5,10), content=[
            UILabel(0,0,W/2, 20, f'ID: {self.selected_wall_index}',background_color = None, anchor=Anchor.CENTER),
            UILabel(0, 0, W-10, 20, color_getter, anchor = Anchor.LEFT),
            # r
            UISlider(0, 0, W-10, SLIDER_H, 
                     value_setter = r_setter,
                     min_value = 0,
                     max_value = 255,
                     start_value = self.wall_collection[index].color[0]/255,
                     handle_size = SLIDER_HANDLE_SIZE,
                     background_color = (20,20,20),
                     round_func= lambda x: int(x)),
            # g
            UISlider(0, 0, W-10, SLIDER_H, 
                     value_setter = g_setter,
                     min_value = 0,
                     max_value = 255,
                     start_value = self.wall_collection[index].color[1]/255,
                     handle_size = SLIDER_HANDLE_SIZE,
                     background_color = (20,20,20),
                     round_func= lambda x: int(x)),
            # b
            UISlider(0, 0, W-10, SLIDER_H, 
                     value_setter = b_setter,
                     min_value = 0,
                     max_value = 255,
                     start_value = self.wall_collection[index].color[2]/255,
                     handle_size = SLIDER_HANDLE_SIZE,
                     background_color = (20,20,20),
                     round_func= lambda x: int(x)),
        ])

        self.ui_elements.append(ui_element)
        self.selected_wall_ui_index = self.ui_elements.index(ui_element)

    def unselect_wall(self) -> None:
        self.ui_elements.pop(self.selected_wall_ui_index)
        
        self.selected_wall_index = None
        self.selected_wall_ui_index = None

        self.selected_vert_index: int | None = None

    def update(self, events):
        mouse_pos = pg.mouse.get_pos()
        
        # reset mouse temp states
        self.mouse1_clicked = False
        self.mouse_moving = False

        #region INPUT
        # Get the current mouse position
        current_mouse_x, current_mouse_y = pg.mouse.get_pos()

        # Calculate the mouse delta
        self.mouse_delta_x = current_mouse_x - self.prev_mouse_x
        self.mouse_delta_y = current_mouse_y - self.prev_mouse_y

        # Update the previous mouse position
        self.prev_mouse_x = current_mouse_x
        self.prev_mouse_y = current_mouse_y
        
        self.mouse_moving = True

        for e in events:
            if e.type == pg.MOUSEBUTTONDOWN and e.button == 1:
                self.mouse1_down = True
                self.mouse1_clicked = True

            elif e.type == pg.MOUSEBUTTONUP and e.button == 1:
                self.mouse1_down = False

        # reset delta mouse if not moving
        if not self.mouse_moving:
            self.mouse_delta_x, self.mouse_delta_y = 0, 0

        #endregion

        # handle mouse1 click
        if self.mouse1_clicked:

            # on map clicked
            if not self.is_cursor_on_ui:
                # cleck for wall click
                i = self.get_intersected_wall_index()            
                
                if i != None:
                    # dont select same wall one again
                    if i != self.selected_wall_index:
                        self.select_wall(i)
                    # select point
                    else: 
                        # point a
                        a = self.wall_collection[self.selected_wall_index].a
                        b = self.wall_collection[self.selected_wall_index].b
                        mx, my = self.pixels_to_units(pg.mouse.get_pos())

                        if sqrt((a[0] - mx)**2 + (a[1]- my)**2) < SELECTED_POINT_R_UNITS:
                            self.selected_vert_index = 0
                        elif sqrt((b[0] - mx)**2 + (b[1]- my)**2) < SELECTED_POINT_R_UNITS:
                            self.selected_vert_index = 1

                elif self.is_wall_selected:
                    self.unselect_wall()

        # if is drag movement
        if self.mouse1_down and not self.is_cursor_on_ui:
            # if point selected
            if self.selected_vert_index!=None:
                d = (self.mouse_delta_x/MAP_SCALE, -self.mouse_delta_y/MAP_SCALE)

                if self.selected_vert_index == 0: 
                    t = self.wall_collection[self.selected_wall_index].a
                    self.wall_collection[self.selected_wall_index].a = (t[0]+d[0], t[1]+d[1])
                elif self.selected_vert_index == 1:
                    t = self.wall_collection[self.selected_wall_index].b
                    self.wall_collection[self.selected_wall_index].b = (t[0]+d[0], t[1]+d[1])
                
                # recalculate wall params
                self.wall_collection[self.selected_wall_index].calc_equation()
            else:
                # move map
                self.map_displacement = (self.mouse_delta_x + self.map_displacement[0],
                                     self.map_displacement[1] - self.mouse_delta_y)

        # update each object
        for obj in self.ui_elements:
            obj.update(events, mouse_pos)
        
        #

    def draw_cursor_positsion(self) -> None:
        mouse_projected = self.pixels_to_units(pg.mouse.get_pos())
        render = font_arial20.render(f'mouse: {mouse_projected}', True, (255, 255, 255))

        text_width, text_height = render.get_size()
        screen.blit(render, (WND_WIDTH - text_width, WND_HEIGHT - text_height))
        pg.draw.circle(screen, (255,0,0), pg.mouse.get_pos(), CURSOR_RADIUS_PX, 1)

    def draw_ui(self) -> None:
        # draw each one
        for obj in self.ui_elements:
            obj.draw(self.screen)

    def draw(self) -> None:
        # reset background
        screen.blit(self.grid_background, (-GRID_CELL_PX_SIZE+self.map_displacement[0]%GRID_CELL_PX_SIZE,
                                        -GRID_CELL_PX_SIZE-self.map_displacement[1]%GRID_CELL_PX_SIZE))
        
        # draw everything
        self.draw_walls()
        self.draw_cursor_positsion()
        self.draw_ui()
        

if __name__ == "__main__":

    # init pygame
    pg.init()
    screen = pg.display.set_mode((WND_WIDTH, WND_HEIGHT))
    clock = pg.time.Clock()

    # init fonts
    font_arial20 = pg.font.SysFont('Arial', 20)

    # init app
    app = Application(screen)
    app.load_data()

    while True:
        events = pg.event.get()
        for event in events:
            if event.type == pg.QUIT:
                pg.quit()
                exit()

        # upadte app
        app.update(events)
        app.draw()

        pg.display.update()
        clock.tick(60)
        pg.display.set_caption(f"{round(clock.get_fps(),1)} FPS")
