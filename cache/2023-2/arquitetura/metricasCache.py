import numpy as np
import matplotlib.pyplot as plt

# Parameters
cache_hits = np.arange(0, 101, 1)  # Vary the cache hits from 0 to 100%
time_cache_access = 10  # Cache access time (example)
time_main_memory_access = 100  # Time required to access main memory (example)

# Formula 1: Average Memory Access Time
def average_memory_access_time(hit_ratio, time_cache_access, time_main_memory_access):
    return hit_ratio * time_cache_access + (1 - hit_ratio) * time_main_memory_access

# Formula 2: Hit Ratio
def hit_ratio(cache_hits, cache_misses):
    return (cache_hits / (cache_hits + cache_misses)) * 100

# Calculating values
cache_misses = 100 - cache_hits
time_access = [average_memory_access_time(hit_ratio/100, time_cache_access, time_main_memory_access) for hit_ratio in cache_hits]
hit_rates = [hit_ratio(hit, miss) for hit, miss in zip(cache_hits, cache_misses)]

# Plotting the graphs
plt.figure(figsize=(12, 6))

# Graph for Formula 1
plt.subplot(1, 2, 1)
plt.plot(cache_hits, time_access, label="Average Memory Access Time")
plt.xlabel("Hit Ratio (%)")
plt.ylabel("Average Memory Access Time")
plt.legend()

# Graph for Formula 2
plt.subplot(1, 2, 2)
plt.plot(cache_hits, hit_rates, label="Hit Ratio")
plt.xlabel("Cache Hits (%)")
plt.ylabel("Hit Ratio (%)")
plt.legend()

plt.tight_layout()
plt.ion()
#plt.show()
