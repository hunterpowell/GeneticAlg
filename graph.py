import matplotlib.pyplot as plt

avg_x = []
avg_y = []
for line in open('build/Debug/averages.txt', 'r'):
    lines = line.split()
    avg_x.append(int(lines[0]))
    avg_y.append(int(lines[1]))

best_x = []
best_y = []
for line in open('build/Debug/best.txt', 'r'):
    lines = line.split()
    best_x.append(int(lines[0]))
    best_y.append(int(lines[1]))

fig, ax = plt.subplots(2)

ax[0].plot(avg_x, avg_y, color='xkcd:indigo', lw=2)
ax[0].set_title("Average")
ax[0].set_facecolor('xkcd:light blue grey')
ax[0].grid()

ax[1].plot(best_x, best_y, color='xkcd:indigo', lw=2)
ax[1].set_title("Best Performer")
ax[1].set_facecolor('xkcd:light blue grey')
ax[1].grid()

plt.tight_layout()
plt.show()
