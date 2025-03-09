import systemmonitor
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time
import numpy as np

# Initialize data lists
cpu_data = []
mem_data = []
net_data = []
time_data = []

# Create figure and subplots
fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(10, 8))
fig.suptitle('System Resource Monitor')

# Configure subplots
ax1.set_ylabel('CPU Usage (%)')
ax1.set_ylim(0, 100)
line1, = ax1.plot([], [], 'r-', label='CPU')

ax2.set_ylabel('Memory Usage (%)')
ax2.set_ylim(0, 100)
line2, = ax2.plot([], [], 'g-', label='Memory')

ax3.set_ylabel('Network Usage (bytes/s)')
ax3.set_xlabel('Time (s)')
line3, = ax3.plot([], [], 'b-', label='Network')

ax1.legend()
ax2.legend()
ax3.legend()

# Initialize start time
start_time = time.time()
max_points = 30  # Maximum number of points to display

# Animation update function
def update(frame):
    current_time = time.time() - start_time
    time_data.append(current_time)
    
    # Get data from C extension
    try:
        cpu_usage = systemmonitor.get_cpu_usage()
        mem_usage = systemmonitor.get_memory_usage()
        net_usage = systemmonitor.get_network_usage()
    except Exception as e:
        print(f"Error getting data: {e}")
        return line1, line2, line3
    
    # Append data
    cpu_data.append(cpu_usage)
    mem_data.append(mem_usage)
    net_data.append(net_usage)
    
    # Keep only the last max_points
    if len(time_data) > max_points:
        time_data.pop(0)
        cpu_data.pop(0)
        mem_data.pop(0)
        net_data.pop(0)
    
    # Update line data
    line1.set_data(time_data, cpu_data)
    line2.set_data(time_data, mem_data)
    line3.set_data(time_data, net_data)
    
    # Adjust axes limits if needed
    for ax in [ax1, ax2, ax3]:
        ax.relim()
        ax.autoscale_view(scalex=True, scaley=True)
    
    # Adjust network axis based on data
    if net_data:
        ax3.set_ylim(0, max(net_data) * 1.1)
    
    return line1, line2, line3

# Create animation
ani = animation.FuncAnimation(fig, update, frames=None, interval=2000, blit=True)

plt.tight_layout()
plt.subplots_adjust(top=0.9)
plt.show()

if __name__ == "__main__":
    try:
        plt.show()
    except KeyboardInterrupt:
        print("Monitoring stopped.")