import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from matplotlib.patches import Patch

def read_grid(filename):
    grid = []
    for line in open(filename, 'r'):
        grid.append([int(x) for x in line.split()])
    return np.array(grid)

avg_x = []
avg_y = []
for line in open('averages.txt', 'r'):
    lines = line.split()
    avg_x.append(int(lines[0]))
    avg_y.append(int(lines[1]))

best_x = []
best_y = []
for line in open('best.txt', 'r'):
    lines = line.split()
    best_x.append(int(lines[0]))
    best_y.append(int(lines[1]))

best_grid = read_grid('best_map.txt')
rand_grid = read_grid('rand_map.txt')

# 0=empty, 1=battery, 2=wall, 3=visited, 7=the guy
cmap = ListedColormap(["#828282", "#414141", "#000000", "#A663EA", "#D70000"])  # empty, wall, robot

fig, ax = plt.subplots(2, 2, figsize=(12, 8))

ax[0][0].plot(avg_x, avg_y, color='xkcd:indigo', lw=2)
ax[0][0].set_title("Average Fitness")
ax[0][0].set_facecolor('xkcd:light blue grey')
ax[0][0].grid()

ax[0][1].plot(best_x, best_y, color='xkcd:indigo', lw=2)
ax[0][1].set_title("Best Fitness")
ax[0][1].set_facecolor('xkcd:light blue grey')
ax[0][1].grid()

ax[1][0].imshow(rand_grid, cmap=cmap, vmin=0, vmax=4)
ax[1][0].set_title("Random Bot Map")
ax[1][0].axis('off')

ax[1][1].imshow(best_grid, cmap=cmap, vmin=0, vmax=4)
ax[1][1].set_title("Best Performer Map")
ax[1][1].axis('off')

legend_elements = [
    Patch(facecolor='#000000', label='Wall'),
    Patch(facecolor='#414141', label='Battery'),
    Patch(facecolor='#828282', label='Empty'),
    Patch(facecolor='#A663EA', label='Visited'),
    Patch(facecolor='#D70000', label='Robot')
]

fig.legend(handles=legend_elements, loc='lower center', ncol=1, bbox_to_anchor=(0.5, 0))


plt.tight_layout()
plt.show()
