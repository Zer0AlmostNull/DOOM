from math import sqrt

class Wall:
    def __init__(self, a: tuple = (0,0), b: tuple = (0,0), color: tuple = (255, 255, 255, 255)):
        self.a = a
        self.b = b
        self.color = color

        self.eq_A = None
        self.eq_B = None
        self.eq_C = None


        self.length = sqrt((a[0] - b[0]) ** 2 + (a[1] - b[1])**2)
        self.S = ((a[0] + b[0])/2, (a[1] + b[1])/2)

        self.calc_equation()
    
    @property
    def is_vertical(self):
        return self.a[0] == self.b[0]
    
    def get_equation(self):
        if self.eq_A != None and self.eq_B != None and self.eq_C != None:
            return self.eq_A, self.eq_B, self.eq_C
        
        return self.calc_equation()

    def calc_equation(self):
        '''Calculates line equation.'''


        self.length = sqrt((self.a[0] - self.b[0]) ** 2 + (self.a[1] - self.b[1])**2)
        self.S = ((self.a[0] + self.b[0])/2, (self.a[1] + self.b[1])/2)

        # if its vertical
        if self.is_vertical:
            self.eq_A = 1
            self.eq_B = 0
            self.eq_C = -self.a[0]

        else:
            # calculate equation
            m = (self.b[1]-self.a[1])/(self.b[0]-self.a[0])
            n = -m * self.a[0] + self.a[1]

            # 
            self.eq_A = -m
            self.eq_B = 1 
            self.eq_C = -n

        return self.eq_A, self.eq_B, self.eq_C
     
  