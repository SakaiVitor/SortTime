import pandas as pd
import matplotlib.pyplot as plt

# Read CSV file
data = pd.read_csv("output/sorting_times.csv")

# Generate graph
plt.figure(figsize=(10, 6))
plt.plot(data["Size"], data["Bubble Sort Time (s)"], label="Bubble Sort")
plt.plot(data["Size"], data["Quick Sort Time (s)"], label="Quick Sort")
plt.plot(data["Size"], data["Merge Sort Time (s)"], label="Merge Sort")

plt.xlabel("Input Size")
plt.ylabel("Time (seconds)")
plt.title("Sorting Algorithm Performance")
plt.legend()
plt.grid(True)

# Show graph
plt.show()
