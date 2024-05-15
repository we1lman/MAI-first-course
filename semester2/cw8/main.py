import tkinter as tk
from tkinter import simpledialog
import networkx as nx
import matplotlib.pyplot as plt

def enumerate_paths(graph, start, end, path=[]):
    path = path + [start]
    if start == end:
        return [path]
    if start not in graph:
        return []
    paths = []
    for node in graph[start]:
        if node not in path:
            newpaths = enumerate_paths(graph, node, end, path)
            for newpath in newpaths:
                paths.append(newpath)
    return paths

def visualize_graph(graph, pos):
    nx.draw(graph, pos, with_labels=True, node_color='lightblue', node_size=500, font_size=10, font_weight='bold')
    plt.show()

def run_algorithm():
    start_node = int(simpledialog.askstring("Input", "Enter the start node:"))
    end_node = int(simpledialog.askstring("Input", "Enter the end node:"))
    all_paths = enumerate_paths(graph_dict, start_node, end_node)
    result.set(f"All paths from node {start_node} to node {end_node}: {all_paths}")

graph_dict = {1: [2, 3], 2: [3, 4], 3: [4], 4: []}
G = nx.DiGraph(graph_dict)
pos = nx.spring_layout(G)

root = tk.Tk()
root.title("Graph Path Enumeration")

result = tk.StringVar()
result_label = tk.Label(root, textvariable=result, wraplength=400)
result_label.pack()

run_button = tk.Button(root, text="Run Algorithm", command=run_algorithm)
run_button.pack()

visualize_button = tk.Button(root, text="Visualize Graph", command=lambda: visualize_graph(G, pos))
visualize_button.pack()

root.mainloop()
