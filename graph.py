from __future__ import annotations

from dataclasses import dataclass, field
from typing import Optional

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from matplotlib.patches import Patch

@dataclass
class PlotConfig:
    max_fitness: int = 800

    colors: dict = field(default_factory=lambda: {
        "empty":   "#222648",
        "battery": "#37b6cf",
        "wall":    "#000000",
        "visited": "#fea3b4",
        "robot":   "#ff3d60",
    })

    @property
    def y_max(self) -> float:
        return self.max_fitness * 1.05

    @property
    def cmap(self) -> ListedColormap:
        return ListedColormap(list(self.colors.values()))

def read_grid(filename: str) -> np.ndarray:
    with open(filename) as f:
        return np.array([[int(x) for x in line.split()] for line in f])


def read_fitness_file(filename: str) -> tuple[list[int], list[int], Optional[int]]:
    """Return (x_values, y_values, max_fitness_or_None).

    If the file contains a header line starting with -1, the second value on
    that line is treated as half of max_fitness (i.e. max_fitness = value * 2).
    """
    x, y = [], []
    max_fitness = None
    with open(filename) as f:
        for line in f:
            parts = line.split()
            if not parts:
                continue
            if parts[0] == "-1":
                max_fitness = int(parts[1]) * 2
            else:
                x.append(int(parts[0]))
                y.append(int(parts[1]))
    return x, y, max_fitness


def load_data(
    averages_file: str = "averages.txt",
    best_file: str = "best.txt",
    best_map_file: str = "best_map.txt",
    rand_map_file: str = "rand_map.txt",
) -> tuple[dict, PlotConfig]:
    avg_x, avg_y, max_fitness = read_fitness_file(averages_file)
    best_x, best_y, _ = read_fitness_file(best_file)
    best_grid = read_grid(best_map_file)
    rand_grid = read_grid(rand_map_file)

    cfg = PlotConfig()
    if max_fitness is not None:
        cfg.max_fitness = max_fitness

    data = {
        "avg_x": avg_x, "avg_y": avg_y,
        "best_x": best_x, "best_y": best_y,
        "best_grid": best_grid, "rand_grid": rand_grid,
    }
    return data, cfg


# ---------------------------------------------------------------------------
# Styling helpers
# ---------------------------------------------------------------------------

def apply_dark_style(ax: plt.Axes) -> None:
    ax.set_facecolor("#16213e")
    ax.tick_params(colors="#cccccc")
    ax.xaxis.label.set_color("#cccccc")
    ax.yaxis.label.set_color("#cccccc")
    ax.title.set_color("#ffffff")
    for spine in ax.spines.values():
        spine.set_edgecolor("#444466")


def build_figure() -> tuple[plt.Figure, np.ndarray]:
    fig, axes = plt.subplots(2, 2, figsize=(12, 10))
    fig.patch.set_facecolor("#1a1a2e")
    for ax in axes.flat:
        apply_dark_style(ax)
    return fig, axes


# ---------------------------------------------------------------------------
# Plot helpers
# ---------------------------------------------------------------------------

def plot_fitness(ax: plt.Axes, x: list, y: list, title: str, cfg: PlotConfig) -> None:
    ax.plot(x, y, color="xkcd:coral", lw=2)
    ax.set_title(title)
    ax.set_ylabel("Fitness (absolute)", color="#cccccc")
    ax.set_ylim(0, cfg.y_max)
    ax.set_xlim(left=0)
    ax.yaxis.set_major_formatter(plt.FuncFormatter(lambda v, _: f"{v:.0f}"))
    ax.grid(color="#444466", linestyle="--", linewidth=0.5)

    ax2 = ax.twinx()
    ax2.set_ylim(0, cfg.y_max)
    ax2.set_facecolor("#16213e")
    ax2.tick_params(colors="#cccccc")
    ax2.yaxis.label.set_color("#cccccc")
    for spine in ax2.spines.values():
        spine.set_edgecolor("#444466")
    ax2.set_ylabel(f"% of Max ({cfg.max_fitness})", color="#cccccc")
    ax2.yaxis.set_major_formatter(
        plt.FuncFormatter(lambda v, _: f"{v / cfg.max_fitness * 100:.0f}%")
    )


def add_grid_lines(ax: plt.Axes, grid: np.ndarray) -> None:
    rows, cols = grid.shape
    ax.set_xticks(np.arange(-0.5, cols, 1), minor=True)
    ax.set_yticks(np.arange(-0.5, rows, 1), minor=True)
    ax.set_xticks([])
    ax.set_yticks([])
    ax.grid(which="minor", color="#7a7a7a", linewidth=0.8)
    ax.tick_params(which="minor", length=0)


def plot_grid(ax: plt.Axes, grid: np.ndarray, title: str, cfg: PlotConfig) -> None:
    ax.imshow(grid, cmap=cfg.cmap, vmin=0, vmax=4)
    ax.set_title(title)
    add_grid_lines(ax, grid)


def add_legend(fig: plt.Figure, cfg: PlotConfig) -> None:
    legend_elements = [
        Patch(facecolor=cfg.colors[key], label=key.capitalize())
        for key in ("wall", "battery", "empty", "visited", "robot")
    ]
    fig.legend(
        handles=legend_elements,
        loc="lower center",
        ncol=1,
        bbox_to_anchor=(0.495, 0.25),
    )

def main() -> None:
    data, cfg = load_data()

    fig, axes = build_figure()

    plot_fitness(axes[0][0], data["avg_x"],  data["avg_y"],  "Average Fitness per Gen",              cfg)
    plot_fitness(axes[0][1], data["best_x"], data["best_y"], "Best Fitness per Gen",                 cfg)
    plot_grid(axes[1][0], data["rand_grid"], "Random Gen 1 Bot on a New Map",                        cfg)
    plot_grid(axes[1][1], data["best_grid"], "Best Performer From Any Gen on a New Map",             cfg)

    add_legend(fig, cfg)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
