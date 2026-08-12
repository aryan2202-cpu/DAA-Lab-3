import numpy as np
import matplotlib.pyplot as plt

n = np.linspace(10, 10000, 500)
# Worst case comparisons: Binary ~ 2*log2(n), Ternary ~ 4*log3(n)
binary_comps = 2 * np.log2(n)
ternary_comps = 4 * (np.log(n) / np.log(3))

plt.figure(figsize=(8, 5))
plt.plot(n, binary_comps, label='Binary Search (~2 log2 n)', color='blue')
plt.plot(n, ternary_comps, label='Ternary Search (~4 log3 n)', color='red')

plt.xlabel('Array Size (n)')
plt.ylabel('Number of Comparisons (Worst Case)')
plt.title('Binary vs Ternary Search Comparisons')
plt.legend()
plt.grid(True)
plt.savefig('search_comparison.png')
plt.show()