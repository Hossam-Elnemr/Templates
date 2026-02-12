// Complexity O(3^n)
// Iterate over all submasks for every mask
for (int m = 0; m < (1<<n); ++m)
    for (int s = m; s; s = (s - 1) & m) // iterate over all submasks for a specific mask
