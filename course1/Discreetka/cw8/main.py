import itertools
import tkinter as tk
from tkinter import simpledialog, messagebox
import matplotlib.pyplot as plt
import networkx as nx
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

def check_latin_property(sequence, graph):
    # Проверка свойства P: последовательность является путем
    for i in range(len(sequence) - 1):
        if sequence[i+1] not in graph[sequence[i]]:
            return False
    return True

def build_initial_matrices(graph, nodes):
    M1 = {node: [] for node in nodes}
    M1_prime = {node: [] for node in nodes}

    for node in nodes:
        for neighbor in graph.neighbors(node):
            M1[node].append(neighbor)
            M1_prime[neighbor].append(node)

    return M1, M1_prime

def compose_matrices(M1, M1_prime):
    M2 = {key: [] for key in M1.keys()}
    for key in M1:
        for value in M1[key]:
            M2[key].extend(M1_prime[value])
    return M2

def build_latin_compositions(graph, nodes):
    M1, M1_prime = build_initial_matrices(graph, nodes)
    compositions = [M1]

    for _ in range(2, len(nodes)):
        new_matrix = compose_matrices(compositions[-1], M1_prime)
        compositions.append(new_matrix)

    return compositions

def enumerate_paths_latin(graph, start, end):
    nodes = list(graph.nodes)
    compositions = build_latin_compositions(graph, nodes)
    paths = set()  # Используем множество для хранения путей

    def dfs(current_path):
        current_node = current_path[-1]
        if current_node == end:
            paths.add(tuple(current_path))  # Добавляем путь в виде кортежа, чтобы он был хешируемым
            return
        for length, comp in enumerate(compositions, start=1):
            for next_node in comp[current_node]:
                if next_node not in current_path and next_node in graph[current_node]:
                    new_path = current_path + [next_node]
                    if check_latin_property(new_path, graph):
                        dfs(new_path)

    dfs([start])
    return list(paths)  # Возвращаем пути в виде списка кортежей

# Обновление функции enumerate_paths для вывода результатов
def enumerate_paths(self):
    start_node = simpledialog.askstring('Начальная вершина', 'Введите номер начальной вершины')
    end_node = simpledialog.askstring('Конечная вершина', 'Введите номер конечной вершины')
    if start_node and end_node:
        try:
            start_node = int(start_node)
            end_node = int(end_node)
            all_paths = enumerate_paths_latin(self.graph.G, start_node, end_node)
            messagebox.showinfo('Перечисление путей',
                                f'Все пути из вершины {start_node} в вершину {end_node}: {all_paths}')
        except ValueError:
            messagebox.showerror('Ошибка', 'Введите корректные номера вершин')

class Graph:
    def __init__(self, G=None, from_edges=None):
        if G is not None:
            self.G = G
        elif from_edges is not None:
            self.G = nx.DiGraph()
            self.G.add_edges_from(from_edges)
        else:
            self.G = nx.DiGraph()
        self.pos = None

    def add_node(self, node):
        self.G.add_node(node)
        self.pos = nx.spring_layout(self.G)

    def add_edge(self, node1, node2):
        self.G.add_edge(node1, node2)
        self.pos = nx.spring_layout(self.G)

    def remove_node(self):
        self.G.remove_node(node)
        self.pos = nx.spring_layout(self.G)

    def remove_edge(self, node1, node2):
        self.G.remove_edge(node1, node2)
        self.pos = nx.spring_layout(self.G)

    def clear_graph(self):
        if nx.is_frozen(self.G):
            self.G = nx.DiGraph()
        else:
            self.G.clear()

    def planar_layout(self):
        return nx.planar_layout(self.G)

class App:
    def __init__(self):
        self.graph = Graph()
        self.root = tk.Tk()
        self.root.title('Ориентированный граф и латинская композиция')
        self._create_interface()
        self._setup_graph_canvas()

    def _create_interface(self):
        self.graph_frame = tk.Frame(self.root)
        self.graph_frame.pack(fill=tk.BOTH, expand=True)
        self._create_buttons()

    def _create_buttons(self):
        interaction_frame = tk.Frame(self.root, height=60)
        interaction_frame.pack(side=tk.BOTTOM, fill=tk.X)
        interaction_frame.pack_propagate(False)

        examples_frame = tk.Frame(self.root, height=60)
        examples_frame.pack(side=tk.BOTTOM, fill=tk.X)
        examples_frame.pack_propagate(False)

        interaction_buttons = [
            ('Добавить вершину', self.add_node),
            ('Добавить ребро', self.add_edge),
            ('Удалить вершину', self.remove_node),
            ('Удалить ребро', self.remove_edge),
            ('Перечислить пути', self.enumerate_paths),
            ('Очистить граф', self.clear_graph)
        ]

        for text, command in interaction_buttons:
            tk.Button(interaction_frame, text=text, command=command).pack(side=tk.LEFT, padx=5, pady=5)

    def _setup_graph_canvas(self):
        self.fig = plt.figure(figsize=(8, 6))
        self.canvas = FigureCanvasTkAgg(self.fig, master=self.graph_frame)
        self.canvas_widget = self.canvas.get_tk_widget()
        self.canvas_widget.pack(fill=tk.BOTH, expand=True)

    def draw_graph(self):
        self.fig.clf()
        pos = self.graph.pos if self.graph.pos else nx.spring_layout(self.graph.G)
        nx.draw(self.graph.G, pos, with_labels=True, node_size=700, node_color='skyblue', font_size=20,
                font_weight='bold')
        self.canvas.draw_idle()

    def add_node(self):
        node = simpledialog.askstring('Добавление вершины', 'Введите номер вершины')
        if node:
            self.graph.add_node(int(node))
            self.draw_graph()

    def add_edge(self):
        edge = simpledialog.askstring('Добавление ребра', 'Введите номера вершин через пробел')
        if edge:
            try:
                node1, node2 = map(int, edge.split())
                self.graph.add_edge(node1, node2)
                self.draw_graph()
            except ValueError:
                messagebox.showerror('Ошибка', 'Введите два числа, разделенные пробелом')

    def remove_node(self):
        node = simpledialog.askstring('Удаление вершины', 'Введите номер вершины')
        if node:
            self.graph.remove_node(int(node))
            self.draw_graph()

    def remove_edge(self):
        edge = simpledialog.askstring('Удаление ребра', 'Введите номера вершин через пробел')
        if edge:
            try:
                node1, node2 = map(int, edge.split())
                self.graph.remove_edge(node1, node2)
                self.draw_graph()
            except ValueError:
                messagebox.showerror('Ошибка', 'Введите два числа, разделенные пробелом')

    def clear_graph(self):
        self.graph.clear_graph()
        self.draw_graph()

    def enumerate_paths(self):
        start_node = simpledialog.askstring('Начальная вершина', 'Введите номер начальной вершины')
        end_node = simpledialog.askstring('Конечная вершина', 'Введите номер конечной вершины')
        if start_node and end_node:
            try:
                start_node = int(start_node)
                end_node = int(end_node)
                all_paths = enumerate_paths_latin(self.graph.G, start_node, end_node)
                messagebox.showinfo('Перечисление путей',
                                    f'Все пути из вершины {start_node} в вершину {end_node} (всего {len(all_paths)}:\n{all_paths}')
            except ValueError:
                messagebox.showerror('Ошибка', 'Введите корректные номера вершин')

if __name__ == "__main__":
    app = App()
    app.root.mainloop()
