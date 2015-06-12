#!/bin/bash

gnome-terminal -x ./build/debug/generator_app/generator_app 10000 10001 simulation.json
gnome-terminal -x ./build/debug/filter_app/filter_app localhost 10000 10002
gnome-terminal -x ./build/debug/comparator_app/comparator_app localhost 10001 localhost 10002
gnome-terminal -x ./src/vis_app/vis_app.py


