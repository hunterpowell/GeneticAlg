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
        "empty" : "#222648",
        "battery" : "#37b6cf",
        "wall" : "#282830",
        "visited" : "#fea3b4",
        "robot" : "#ff3d60"
        }

cmap = ListedColormap(colors.values())

fig, axes = plt.subplots(2, 2, figsize=(12, 10))
fig.patch.set_facecolor('#1a1a2e')

for ax in axes.flat:
    ax.set_facecolor('#16213e')
    ax.tick_params(colors='#cccccc')
    ax.xaxis.label.set_color('#cccccc')
    ax.yaxis.label.set_color('#cccccc')
    ax.title.set_color('#ffffff')
    for spine in ax.spines.values():
        spine.set_edgecolor('#444466')

axes[0][0].plot(avg_x, avg_y, color='xkcd:coral', lw=2)
axes[0][0].set_title("Average Fitness per Gen")
axes[0][0].grid()

axes[0][1].plot(best_x, best_y, color='xkcd:coral', lw=2)
axes[0][1].set_title("Best Fitness per Gen")
axes[0][1].grid()

def add_grid_lines(ax, grid):
    rows, cols = grid.shape
    ax.set_xticks(np.arange(-0.5, cols, 1), minor=True)
    ax.set_yticks(np.arange(-0.5, rows, 1), minor=True)
    ax.set_xticks([])  # hide major ticks
    ax.set_yticks([])
    ax.grid(which='minor', color="#7a7a7a", linewidth=.8)
    ax.tick_params(which='minor', length=0)

axes[1][0].imshow(rand_grid, cmap=cmap, vmin=0, vmax=4)
axes[1][0].set_title("Random Gen 1 Bot on a New Map")
# axis('off') removed
add_grid_lines(axes[1][0], rand_grid)

axes[1][1].imshow(best_grid, cmap=cmap, vmin=0, vmax=4)
axes[1][1].set_title("Best Performer From Any Gen on a New Map")
# axis('off') removed
add_grid_lines(axes[1][1], best_grid)

legend_elements = [
    Patch(facecolor=colors["wall"], label='Wall'),
    Patch(facecolor=colors["battery"], label='Battery'),
    Patch(facecolor=colors["empty"], label='Empty'),
    Patch(facecolor=colors["visited"], label='Visited'),
    Patch(facecolor=colors["robot"], label='Robot')
]

fig.legend(handles=legend_elements, loc='lower center', ncol=1, bbox_to_anchor=(0.515, 0.05))
plt.tight_layout()
plt.show()
