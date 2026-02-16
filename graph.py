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

colors = {
        "empty" : "#6B6B6B",
        "battery" : "#800D0D",
        "wall" : "#000000",
        "visited" : "#B281E3",
        "robot" : "#4800FF"
        }

cmap = ListedColormap(colors.values())

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
    Patch(facecolor=colors["wall"], label='Wall'),
    Patch(facecolor=colors["battery"], label='Battery'),
    Patch(facecolor=colors["empty"], label='Empty'),
    Patch(facecolor=colors["visited"], label='Visited'),
    Patch(facecolor=colors["robot"], label='Robot')
]

fig.legend(handles=legend_elements, loc='lower center', ncol=1, bbox_to_anchor=(0.5, 0))

plt.tight_layout()
plt.show()
