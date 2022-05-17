import os
import ycm_core

flags = [
  '-std=c17',
  '-x','c',
  '-I', 'include',
  '-nostdinc',
  '-isystem', '/home/ecte/compilers/c64/oscar64/include',
  '-isystem', '/home/ecte/compilers/c64/oscar64/include/c64',
  '-isystem', '/home/ecte/compilers/c64/oscar64/include/gfx',
  '-isystem', '/home/ecte/compilers/c64/oscar64/include/audio',
  ]

SOURCE_EXTENSIONS = [ '.c', ]

def Settings( **kwargs ):
  return {
  'flags': flags,
  'do_cache': True
  }
