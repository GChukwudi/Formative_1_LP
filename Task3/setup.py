from setuptools import setup, Extension

module = Extension('systemmonitor',
                   sources=['systemmonitor.c'])

setup(name='SystemMonitor',
      version='1.0',
      description='System Monitoring Extension',
      ext_modules=[module])