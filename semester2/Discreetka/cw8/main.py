import tkinter as tk
from tkinter import simpledialog, messagebox
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import math


def calc_petersen_graph_pos():
    r = 2
    R = 2 * r
    pos = {}
    delta = 2 * math.pi / 5
    curRadius = math.pi / 2
    for i in range(5):
        pos[i] = (R * math.cos(curRadius), R * math.sin(curRadius))
        pos[i + 5] = (r * math.cos(curRadius), r * math.sin(curRadius))
        curRadius += delta
    return pos


class GraphApp:
    """Приложение для работы с графами и проверки на планарность.

    Атрибуты:
        root (tk.Tk): Главное окно приложения.
        G (networkx.Graph): Объект графа для работы.
    """

    def __init__(self):
        """Инициализация приложения."""
        self.G = nx.DiGraph()
        self.root = tk.Tk()
        self.root.title('Графы и планарность')

        # Создание интерфейса
        self._create_interface()

    def _create_interface(self):
        """Создание пользовательского интерфейса приложения."""
        self.graph_frame = tk.Frame(self.root)
        self.graph_frame.pack(fill=tk.BOTH, expand=True)

        # Первый ряд кнопок для взаимодействия с графом
        interaction_frame = tk.Frame(self.root, height=60)
        interaction_frame.pack(side=tk.BOTTOM, fill=tk.X)
        interaction_frame.pack_propagate(False)

        # Второй ряд кнопок для примеров графов
        examples_frame = tk.Frame(self.root, height=60)
        examples_frame.pack(side=tk.BOTTOM, fill=tk.X)
        examples_frame.pack_propagate(False)

        # Создание кнопок взаимодействия с графом
        interaction_buttons = [
            ('Добавить вершину', self.add_node),
            ('Добавить ребро', self.add_edge),
            ('Удалить вершину', self.remove_node),
            ('Удалить ребро', self.remove_edge),
            ('Проверить планарность', self.check_planarity),
            ('Очистить граф', self.clear_graph)
        ]

        # Создание кнопок для примеров графов
        example_buttons = [
            ('Граф Петерсена', self.create_petersen),  # Будет непланарным
            ('Граф К5', self.create_k5),  # Будет непланарным
            ('Граф П4', self.create_p4)  # Будет планарным
        ]

        for text, command in interaction_buttons:
            tk.Button(interaction_frame, text=text, command=command).pack(side=tk.LEFT, padx=5, pady=5)

        for text, command in example_buttons:
            tk.Button(examples_frame, text=text, command=command).pack(side=tk.LEFT, padx=5, pady=5)

        # Настройка места для графики
        self._setup_graph_canvas()

    def add_node(self):
        """Запрашивает имя узла и добавляет его в граф."""
        node = simpledialog.askstring('Add Node', 'Enter Node')
        if node:
            self.G.add_node(int(node))
            self.draw_graph()

    def add_edge(self):
        """Запрашивает пару узлов и добавляет ребро между ними в граф."""
        edge = simpledialog.askstring('Add Edge', 'Enter Edge (node1 node2)')
        if edge:
            node1, node2 = map(int, edge.split())
            self.G.add_edge(node1, node2)
            self.draw_graph()

    def remove_node(self):
        """Запрашивает имя узла и удаляет его из графа."""
        node = simpledialog.askstring('Remove Node', 'Enter Node')
        if node:
            self.G.remove_node(int(node))
            self.draw_graph()

    def remove_edge(self):
        """Запрашивает пару узлов и удаляет ребро между ними из графа."""
        edge = simpledialog.askstring('Remove Edge', 'Enter Edge (node1, node2)')
        if edge:
            node1, node2 = edge.split(',')
            self.G.remove_edge(node1, node2)
            self.draw_graph()

    def create_petersen(self):
        """Создает граф Петерсена и отображает его."""
        self.G.clear()
        self.G = nx.petersen_graph()
        pos = calc_petersen_graph_pos()
        self.draw_graph(pos)

    def clear_graph(self):
        """Очищает текущий граф."""
        self.G.clear()
        self.draw_graph()

    def draw_graph(self, pos=None):
        """Отрисовывает текущий граф.

        Args:
            pos (dict, optional): Позиции узлов. Если None, будет использован spring_layout.
        """
        print(self.G.nodes)
        self.fig.clf()  # Очистка фигуры перед созданием нового графа
        if pos is None:
            pos = nx.spring_layout(self.G)
        nx.draw(self.G, pos, with_labels=True, node_size=700, node_color='skyblue', font_size=20, font_weight='bold')
        self.canvas.draw_idle()

    def check_planarity(self):
        """Проверяет граф на планарность."""
        check = nx.check_planarity(self.G, counterexample=True)
        if check[0]:
            messagebox.showinfo('Планарность', 'Граф планарный')
        else:
            messagebox.showinfo('Планарность', 'Граф не планарный')
            # Отображение контрпримера
            self.show_counterexample(check[1])

    def show_counterexample(self, counterexample):
        """Отображает контрпример непланарного графа в новом окне."""
        new_window = tk.Toplevel(self.root)
        new_window.title('Контрпример')
        new_window.geometry('800x600')

        # Создание новой фигуры для контрпримера
        new_fig = plt.Figure(figsize=(8, 6))
        new_canvas = FigureCanvasTkAgg(new_fig, master=new_window)
        new_canvas_widget = new_canvas.get_tk_widget()
        new_canvas_widget.pack(fill=tk.BOTH, expand=True)

        ax = new_fig.add_subplot(111)
        pos = nx.spring_layout(counterexample)
        nx.draw(counterexample, pos, with_labels=True, node_size=700, node_color='red', font_size=20,
                font_weight='bold', ax=ax)
        new_canvas.draw_idle()

    def create_k5(self):
        """Создает полный граф K5 и отображает его."""
        self.G.clear()
        self.G = nx.complete_graph(5)
        self.draw_graph()

    def create_p4(self):
        """Создает путь граф P4 и отображает его."""
        self.G.clear()
        self.G = nx.path_graph(4)
        self.draw_graph()

    def _setup_graph_canvas(self):
        """Настройка области для отображения графа."""
        self.fig = plt.figure(figsize=(8, 6))
        self.canvas = FigureCanvasTkAgg(self.fig, master=self.graph_frame)
        self.canvas_widget = self.canvas.get_tk_widget()
        self.canvas_widget.pack(fill=tk.BOTH, expand=True)


if __name__ == "__main__":
    app = GraphApp()
    app.root.mainloop()

