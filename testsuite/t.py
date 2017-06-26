#!/usr/bin/python

import pygame
from pygame.locals import *
import time

white = (255, 255, 255)
blue = (0, 100, 255)

font_size = 48

pygame.init ()
screen = pygame.display.set_mode ((500,500))

font = pygame.font.Font (None, font_size)
text = font.render ("hello", True, white)
textpos = text.get_rect ()
textpos.top = screen.get_rect().top
textpos.left = screen.get_rect().left

screen.blit (text, textpos)

pygame.draw.circle (screen, blue, (100, 100), 100, 0)
pygame.display.flip()


print "setting timer for 3 seconds"
time.sleep (3)
print "goodbye"
