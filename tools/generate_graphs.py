#!/usr/bin/env python3
import os
import random
from collections import deque

# For random numbers to be deterministic.
random.seed(42)

OUTPUT_DIR_GRAPHS = os.path.join("tests", "graphs")
OUTPUT_DIR_ANSWERS = os.path.join("tests", "answers")

# Create directories if they don't exist.
if not os.path.exists(OUTPUT_DIR_GRAPHS):
    os.makedirs(OUTPUT_DIR_GRAPHS)
if not os.path.exists(OUTPUT_DIR_ANSWERS):
    os.makedirs(OUTPUT_DIR_ANSWERS)

def bfs(n, graph, start):
    distances = [-1] * n
    distances[start] = 0
    queue = deque([start])
    while queue:
        u = queue.popleft()
        for v in graph[u]:
            if distances[v] == -1:
                distances[v] = distances[u] + 1
                queue.append(v)
    return distances

def write_graph(filename, n, edges, start):
    with open(filename, "w") as f:
        f.write(f"{n}\n")
        f.write(f"{len(edges)}\n")
        for u, v in edges:
            f.write(f"{u} {v}\n")
        f.write(f"{start}\n")

def write_answer(filename, distances):
    with open(filename, "w") as f:
        for d in distances:
            f.write(f"{d}\n")

def generate_star(n):
    # Random center.
    center = random.randint(0, n-1)
    return [(center, v) for v in range(n) if v != center]

def generate_cycle(n):
    # Randomize the vertices and loop them together.
    perm = list(range(n))
    random.shuffle(perm)
    return [(perm[i], perm[(i+1)%n]) for i in range(n)]

def generate_complete(n):
    # All pairs of vertices, then mix up the order of edges.
    edges = [(i, j) for i in range(n) for j in range(i+1, n)]
    random.shuffle(edges)
    return edges

def generate_chain(n):
    # A random permutation to produce a random chain.
    perm = list(range(n))
    random.shuffle(perm)
    return [(perm[i], perm[i+1]) for i in range(n-1)]

def generate_tree(n):
    # Random tree.
    vertices = list(range(n))
    random.shuffle(vertices)
    edges = []
    for i in range(1, n):
        u = vertices[i]
        v = random.choice(vertices[:i])
        if u > v:
            u, v = v, u
        edges.append((u, v))
    return edges

def generate_graphs():
    types = ["star", "cycle", "complete", "chain", "tree"]
    for n in range(2, 51):
        if n == 2:
            applicable_types = ["star"]
            instances = 1
        else:
            applicable_types = types
            instances = 3
        for t in applicable_types:
            for inst in range(instances):
                if t == "star":
                    edges = generate_star(n)
                elif t == "cycle":
                    edges = generate_cycle(n)
                elif t == "complete":
                    edges = generate_complete(n)
                elif t == "chain":
                    edges = generate_chain(n)
                elif t == "tree":
                    edges = generate_tree(n)
                else:
                    continue

                # Build an adjacency list. 
                graph = [[] for _ in range(n)]
                for u, v in edges:
                    graph[u].append(v)
                    graph[v].append(u)
                start = 0  # select start vertex 0
                distances = bfs(n, graph, start)
                base_name = f"{t}_{n}_{inst}"
                graph_file = os.path.join(OUTPUT_DIR_GRAPHS, f"graph_{base_name}.txt")
                answer_file = os.path.join(OUTPUT_DIR_ANSWERS, f"answer_{base_name}.txt")
                write_graph(graph_file, n, edges, start)
                write_answer(answer_file, distances)
                print(f"Generated {graph_file} and {answer_file}")

if __name__ == "__main__":
    generate_graphs()
