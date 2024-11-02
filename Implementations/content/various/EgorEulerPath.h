/**
 * Description: Egor's find euler
 */
void find_euler(int v) {
    while (ptr[v] < g[v].size()) {
        find_euler(g[v][ptr[v]++]);  
    }
    euler.push_back(v);
}