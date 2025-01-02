#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100  // Giới hạn số đỉnh tối đa

// Khai báo ma trận kề
int graph[MAX][MAX];
int visited[MAX];

// Hàm khởi tạo đồ thị
void initializeGraph(int V) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;  // Không có cạnh
        }
        visited[i] = 0;  // Chưa thăm đỉnh nào
    }
}

// Nhập đồ thị
void inputGraph(int V, int E) {
    int u, v, w;
    for (int i = 0; i < E; i++) {
        printf("Nhập cạnh %d (u v w): ", i + 1);
        if (scanf("%d %d %d", &u, &v, &w) != 3) {
            printf("Lỗi nhập cạnh! Vui lòng nhập lại.\n");
            i--;  // Lặp lại cạnh này
            continue;
        }

        // Kiểm tra chỉ số đỉnh hợp lệ
        if (u < 1 || u > V || v < 1 || v > V) {
            printf("Lỗi: Đỉnh %d hoặc %d vượt ngoài phạm vi (1, %d).\n", u, v, V);
            i--;  // Lặp lại cạnh này
            continue;
        }

        graph[u-1][v-1] = w;  // Trừ 1 vì mảng bắt đầu từ 0
        graph[v-1][u-1] = w;  // Đồ thị vô hướng
    }
}

// DFS - Duyệt theo chiều sâu
void DFS(int v, int V) {
    printf("%d ", v + 1);  // Cộng 1 để in ra đỉnh theo định dạng ban đầu
    visited[v] = 1;

    for (int i = 0; i < V; i++) {
        if (graph[v][i] != 0 && !visited[i]) {
            DFS(i, V);
        }
    }
}

// BFS - Duyệt theo chiều rộng
void BFS(int start, int V) {
    int queue[MAX], front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v + 1);  // Cộng 1 để in ra đỉnh theo định dạng ban đầu

        for (int i = 0; i < V; i++) {
            if (graph[v][i] != 0 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

// Reset trạng thái visited
void resetVisited(int V) {
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }
}

int main() {
    int V, E;

    // Nhập số đỉnh và số cạnh
    printf("Nhập số đỉnh: ");
    scanf("%d", &V);
    printf("Nhập số cạnh: ");
    scanf("%d", &E);

    // Khởi tạo đồ thị và nhập cạnh
    initializeGraph(V);
    inputGraph(V, E);

    // Duyệt đồ thị bằng DFS
    printf("\nDuyệt DFS từ đỉnh 1: ");
    DFS(0, V);  // DFS từ đỉnh 0 (đỉnh nhập là 1, thực tế là 0 trong mảng)

    // Reset visited để dùng cho BFS
    resetVisited(V);

    // Duyệt đồ thị bằng BFS
    printf("\nDuyệt BFS từ đỉnh 1: ");
    BFS(0, V);

    return 0;
}
